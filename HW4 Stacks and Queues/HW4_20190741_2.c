#define _CRT_SECURE_NO_WARNINGS
#define MAX_STACK_SIZE 100
#define MAX_EXPR_SIZE 20
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { lparen, rparen, plus, minus, times, divide, mod, eos, unaryminus, operand } precedence;
precedence getToken(char *symbol, char *expr, int *n);
void eval(char *expr);
void pushInt(int item, int *top, int stack[]);
int popInt(int* top, int stack[]);
void pushPre(precedence item, int *top, precedence stack[]);
precedence popPre(int* top, precedence stack[]);
void stackFull();
void postfix(char *expr, char *post);
char convertToken(precedence token);
void printPost(char post[]);

void main() {
	char str[100000];
	char post[100000];
	int len;
	printf("Input : ");
	scanf("%s", str);
	len = strlen(str);
	if (len > MAX_EXPR_SIZE || len < 1) {
		fprintf(stderr, "Input string size is out of bound. Program terminates.\n");
		exit(1);
	}

	postfix(str, post);
	printPost(post);
	eval(post);
}

precedence getToken(char *symbol, char *expr, int *n) {
	*symbol = expr[(*n)++];
	switch (*symbol) {
	case '(': return lparen;
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '#': return unaryminus;
	case '/': return divide;
	case '*': return times;
	case '%': return mod;
	case '\0': return eos;
	default: return operand; /* no error checking, default is operand */
	}
}

void eval(char *expr) {
	/* evaluate a postfix expression and print the calculated result*/
	int top = -1, op1, op2, n = 0;
	int stack[MAX_STACK_SIZE];
	precedence token;
	char symbol;
	
	token = getToken(&symbol, expr, &n);

	while (token != eos) {
		if (token == operand) {
			pushInt(symbol - '0', &top, stack);
		}
		else if (token == unaryminus) {
			op1 = popInt(&top, stack);
			pushInt(-op1, &top, stack);
		}
		else {
			op2 = popInt(&top, stack);
			op1 = popInt(&top, stack);
			switch (token) {
			case plus: pushInt(op1 + op2, &top, stack); break;
			case minus: pushInt(op1 - op2, &top, stack); break;
			case times: pushInt(op1 * op2, &top, stack); break;
			case divide: pushInt(op1 / op2, &top, stack); break;
			case mod: pushInt(op1 % op2, &top, stack); break;
			}
		}
		token = getToken(&symbol, expr, &n);
	}
	printf("Result : %d\n", popInt(&top, stack));
}

void postfix(char* expr, char* post) {
	/* output the postfix of the given expression */
	char symbol;
	int n = 0, top = -1, count = 0;
	int isp[] = {0, 19, 12, 12, 13, 13, 13, 0, 15};
	int icp[] = { 20, 19, 12, 12, 13, 13, 13, 0, 15};
	precedence stack[MAX_STACK_SIZE];
	precedence token;
	stack[++top] = eos;

	for (token = getToken(&symbol, expr, &n); token != eos; token = getToken(&symbol, expr, &n)) {
		
		if (token == minus && n < 2) {
			token = unaryminus;
		}
		else if (token == minus && !(expr[n - 2] >= 48 && expr[n - 2] <= 57) && expr[n-2] != ')') {
			token = unaryminus;
		}

		if (token == operand) {
			post[count++] = symbol;
		}
		else if (token == rparen) {
			while (stack[top] != lparen) {
				post[count++] = convertToken(popPre(&top, stack));
			}
			popPre(&top, stack);
		}
		else {
			while (isp[stack[top]] >= icp[token]) {
				post[count++] = convertToken(popPre(&top, stack));
			}
			pushPre(token, &top, stack);
		}
	}
	while ((token = popPre(&top, stack)) != eos) post[count++] = convertToken(token);
	post[count] = '\0';
}

void pushInt(int item, int* top, int stack[]) {
	if (*top >= MAX_STACK_SIZE - 1) {
		stackFull();
	}
	stack[++(*top)] = item;
}

int popInt(int* top, int stack[]) {
	if (*top == -1) {
		fprintf(stderr, "Stack is empty. Cannot remove element.\n");
		exit(1);
	}
	return stack[(*top)--];
}

void stackFull() {
	fprintf(stderr, "Stack is full. Cannot add element.\n");
	exit(EXIT_FAILURE);
}


char convertToken(precedence token) {
	switch (token) {
	case plus: return '+'; 
	case minus: return '-'; 
	case unaryminus: return '#'; 
	case divide: return '/'; 
	case times: return '*';
	case mod: return '%';
	}
}

void pushPre(precedence item, int* top, precedence stack[]) {
	if (*top >= MAX_STACK_SIZE - 1) {
		stackFull();
	}
	stack[++(*top)] = item;
}

precedence popPre(int* top, precedence stack[]) {
	if (*top == -1) {
		fprintf(stderr, "Stack is empty. Cannot remove element.\n");
		exit(1);
	}
	return stack[(*top)--];
}

void printPost(char post[]) {
	int i = 0;
	printf("Postfix : ");
	while (post[i] != '\0') {
		printf("%c", post[i]);
		i++;
	}
	printf("\n");
}