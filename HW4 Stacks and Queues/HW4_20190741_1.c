#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 500
#define MAX_ROW 20
#define MAX_COL 20
#define TRUE 1
#define FALSE 0

int maze[MAX_ROW+2][MAX_COL+2];
int mark[MAX_ROW+2][MAX_COL+2];

typedef struct {
	short int vert;
	short int horiz;
}offset;
offset move[8];

typedef struct {
	short int row;
	short int col;
	short int dir;
}element;
element stack[MAX_STACK_SIZE];

int top;

void push(element);
element pop();
void stackFull();
element stackEmpty();

void main() {
    int i, j, row, col, nextRow, nextCol, dir, found = FALSE, item;
    int exitRow, exitCol;
    element position;
    
    //maze input 
    printf("Input number of Rows(1<=Rows<=20): ");
    scanf("%d", &row);
    if (row > 20 || row < 1) {
        fprintf(stderr, "Input number of Rows is out of bound. Program terminates.\n");
        exit(1);
    }

    printf("Input number of Columns(1<=Columns<=20): ");
    scanf("%d", &col);
    if (col > 20 || col < 1) {
        fprintf(stderr, "Input number of Columns is out of bound. Program terminates.\n");
        exit(1);
    }
    exitRow = row;
    exitCol = col;

    printf("Input each rows of maze by 0 and 1.\n");
    for (i = 1; i <= row; i++) {
        for (j = 1; j <= col; j++) {
            scanf("%d", &item);
            if (item == 0 || item == 1) {
                maze[i][j] = item;
                mark[i][j] = 0;
            }
            else {
                fprintf(stderr, "Input maze element is out of bound(0 or 1). Program terminates.\n");
                exit(1);
            }
        }
    }

    /* initialize border of maze */
    for (i = 0; i < row+2; i++) {
        maze[i][0] = 1;
        maze[i][col + 1] = 1;
    }
    for (j = 0; j < col + 2; j++) {
        maze[0][j] = 1;
        maze[row+1][j] = 1;
    }

    /* more greedy version of move */
    move[0].vert = 0; move[0].horiz = 1;    // East
    move[1].vert = 1; move[1].horiz = 1;    // SE
    move[2].vert = 1; move[2].horiz = 0;    // South
    move[3].vert = 1; move[3].horiz = -1;    // SW
    move[4].vert = 0; move[4].horiz = -1;    // West
    move[5].vert = -1; move[5].horiz = -1;    // NW
    move[6].vert = -1; move[6].horiz = 0;    // North
    move[7].vert = -1; move[7].horiz = 1;    // NE

    mark[1][1] = 1; top = 0;
    stack[0].row = 1; stack[0].col = 1; stack[0].dir = 0;

    // exceptional case. maze entrance is the destination. 
    if (row == 1 && col == 1 && maze[1][1] == 0) {
        printf("The path is: \n");
        printf("row col\n");
        printf("%2d%5d\n", row, col);
        exit(1);
    }
    
    while (top > -1 && !found) {
        position = pop();
        row = position.row; col = position.col; dir = position.dir;
        while (dir < 8 && !found) {
            /* move in direction dir */
            nextRow = row + move[dir].vert;
            nextCol = col + move[dir].horiz;
            if (nextRow == exitRow && nextCol == exitCol && !maze[nextRow][nextCol])
                found = TRUE;
            else if (!maze[nextRow][nextCol] && !mark[nextRow][nextCol]) {
                mark[nextRow][nextCol] = 1;
                position.row = row; position.col = col;
                position.dir = ++dir;
                push(position);
                row = nextRow; col = nextCol; dir = 0;
            }
            else ++dir;
        }
    }

    if (found && !maze[1][1]) {
        printf("The path is: \n");
        printf("row col\n");
        for (i = 0; i <= top; i++)
            printf("%2d%5d\n", stack[i].row, stack[i].col);
        printf("%2d%5d\n", row, col);
        printf("%2d%5d\n", exitRow, exitCol);
    }
    else printf("The maze does not have a path.\n");
}

void stackFull() {
    fprintf(stderr, "Stack is full.\n");
    exit(EXIT_FAILURE);
}

void push(element item) {
	if (top >= MAX_STACK_SIZE - 1)
		stackFull();
	stack[++top] = item;
}

element pop() {
	if (top == -1)
		return stackEmpty();  /* error handle */
	return stack[top--];
}

element stackEmpty() {
	element empty;
    empty.row = -1; empty.col = -1; empty.dir = -1;
	return empty;
}