#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node* tree_pointer;
typedef struct node {
	int data;
	tree_pointer left_child;
	tree_pointer right_child;
};

int equal(tree_pointer first, tree_pointer second);
void insert(tree_pointer* node, int num);
tree_pointer modified_search(tree_pointer node, int num);
tree_pointer delete_node(tree_pointer root, int num);
tree_pointer find_max(tree_pointer node);
void inorder(tree_pointer root);
void preorder(tree_pointer root);

int main() {
	FILE* input, * delete;
	tree_pointer tree1;
	int i, num, item;

	tree1 = NULL;
	
	input = fopen("input.txt", "r");
	if (input == NULL) {
		printf("File open error. Program terminates.\n");
		exit(1);
	}

	fscanf(input, "%d", &num);
	for (i = 0; i < num; i++) {
		fscanf(input, "%d", &item);
		insert(&tree1, item);
	}

	delete = fopen("delete.txt", "r");
	if (delete == NULL) {
		printf("File open error. Program terminates.\n");
		exit(1);
	}

	fscanf(delete, "%d", &item);

	while (1) {
		/*get input until the input number is 0.*/
		if (item == 0) break;
		tree1 = delete_node(tree1, item);
		fscanf(delete, "%d", &item);
	}

	printf("inorder : "); inorder(tree1); printf("\n");
	printf("preorder : "); preorder(tree1); printf("\n");

	fclose(input);
	fclose(delete);
	return 0;
}

int equal(tree_pointer first, tree_pointer second) {
	return ((!first && !second) || (first && second && (first->data == second->data) &&
		equal(first->left_child, second->left_child) && equal(first->right_child, second->right_child)));
}

void insert(tree_pointer* node, int num) {
	/* if num is in the tree pointed at by node do nothing
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

tree_pointer delete_node(tree_pointer root, int num) {
	/*Assumed that input num is in the given tree*/
	if (root == NULL) {
		return root;
	}

	if (num < root->data) {
		root->left_child = delete_node(root->left_child, num);
	}
	else if (num > root->data) {
		root->right_child = delete_node(root->right_child, num);
	}
	else {
		/* Deletion node is found */
		if (root->left_child == NULL && root->right_child == NULL) {
			return NULL;
		}
		else if (root->left_child == NULL) {
			tree_pointer temp = root->right_child;
			return temp;
		}
		else if (root->right_child == NULL) {
			tree_pointer temp = root->left_child;
			return temp;
		}
		else {
			tree_pointer temp = find_max(root->left_child);
			root->data = temp ->data;
			root->left_child = delete_node(root->left_child, temp->data);
		}
	}
	return root;
}

tree_pointer find_max(tree_pointer node) {
	tree_pointer current = node;

	while (current && current->right_child != NULL) {
		current = current->right_child;
	}
	return current;
}

void inorder(tree_pointer root) {
	if (root != NULL) {
		inorder(root->left_child);
		printf("%d ", root->data);
		inorder(root->right_child);
	}
}

void preorder(tree_pointer root) {
	if (root != NULL) {
		printf("%d ", root->data);
		preorder(root->left_child);
		preorder(root->right_child);
	}
}