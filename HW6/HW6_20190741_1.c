#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node *tree_pointer;
typedef struct node {
	int data;
	tree_pointer left_child;
	tree_pointer right_child;
};

int equal(tree_pointer first, tree_pointer second);
void insert(tree_pointer *node, int num);
tree_pointer modified_search(tree_pointer node, int num);

int main() {
	FILE* input1, * input2;
	tree_pointer tree1, tree2;
	int i, num, item, ans;

	tree1 = NULL;
	tree2 = NULL;

	input1 = fopen("input1.txt", "r");
	if (input1 == NULL) {
		printf("File open error. Program terminates.\n");
		exit(1);
	}

	fscanf(input1, "%d", &num);
	for (i = 0; i < num; i++) {
		fscanf(input1, "%d", &item);
		insert(&tree1, item);
	}

	input2 = fopen("input2.txt", "r");
	if (input2 == NULL) {
		printf("File open error. Program terminates.\n");
		exit(1);
	}

	fscanf(input2, "%d", &num);
	for (i = 0; i < num; i++) {
		fscanf(input2, "%d", &item);
		insert(&tree2, item);
	}

	ans = equal(tree1, tree2);
	if (ans) printf("YES\n");
	else printf("NO\n");

	fclose(input1);
	fclose(input2);
	return 0;
}

int equal(tree_pointer first, tree_pointer second) {
	return ((!first && !second) || (first && second && (first->data == second->data) &&
		equal(first->left_child, second->left_child) && equal(first->right_child, second->right_child)));
}

void insert(tree_pointer *node, int num) {
	/* if num is in the tree pointed at by nodet do nothing 
	otherwise add a new node with data = num */

	tree_pointer ptr, temp = modified_search(*node, num);
	if (temp || !(*node)) {
		ptr = (tree_pointer)malloc(sizeof(struct node));
		if (!ptr) {
			fprintf(stderr, "The memory is full. Program terminates.\n");
			exit(1);
		}
		ptr->data = num;
		ptr->left_child = NULL;
		ptr->right_child = NULL;
		if (*node) {
			if (num < temp->data)
				temp->left_child = ptr;
			else temp->right_child = ptr;
		}
		else *node = ptr;
	}
}

tree_pointer modified_search(tree_pointer node, int num) {
	
	if (node == NULL || node->data == num) {
		return NULL;
	}
	tree_pointer current = node;
	tree_pointer last_encountered = NULL;

	while (current != NULL) {
		last_encountered = current;

		if (num < current->data) {
			current = current->left_child;
		}
		else if (num > current->data) {
			current = current->right_child;
		}
		else {
			/* input value is already in the tree.*/
			return NULL; 
		}
	}
	return last_encountered;
}



