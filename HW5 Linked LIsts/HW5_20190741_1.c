#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct list_node *list_pointer;
typedef struct list_node {
	int key;
	list_pointer link;
};

int main() {
	FILE *input, *output;
	
	int i, num, item; 
	int data[3];
	list_pointer temp, head, curr, trail;

	input = fopen("input_1.txt", "r");
	if (input == NULL) {
		printf("File open error");
		exit(1);
	}
	
	output = fopen("output_1.txt", "w");
	if (output == NULL) {
		printf("File open error");
		exit(1);
	}

	head = (list_pointer)malloc(sizeof(struct list_node));
	if (!head) {
		fprintf(stderr, "Memory allocation error! Program terminates");
		exit(1);
	}
	head->link = NULL;

	fscanf(input, "%d\n", &num);
	for (i = 0; i < num; i++) {
		temp = (list_pointer)malloc(sizeof(struct list_node));
		/*malloc function error handling*/
		if (!temp) {
			fprintf(stderr, "Memory allocation error! Program terminates");
			exit(1);
		}

		fscanf(input, "%d", &item);
		temp->key = item;
		temp->link = NULL;
		if (!(head->link)) {
			head->link = temp;
		}
		else {
			/*searching its correct position based on the size of the key*/
			curr = head->link;
			trail = head;
			while (1) {
				if (!curr) {
					/*no number left to compare. input number's position is at the last*/
					trail->link = temp;
					break;
				}
				
				if (temp->key > curr->key) {
					trail = curr;
					curr = curr->link;
				}
				else if (temp->key <= curr->key) {
					trail->link = temp;
					temp->link = curr;
					break;
				}
			}
		}
	}
	
	curr = head->link;
	while (curr) {
		fprintf(output, "%d ", curr->key);
		curr = curr->link;
	}
	fclose(input);
	fclose(output);
	
	return 0;
}