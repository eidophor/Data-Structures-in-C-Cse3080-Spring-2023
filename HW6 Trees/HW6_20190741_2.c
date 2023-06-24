#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node* treePointer;
typedef struct node {
    int key;
    treePointer parent;
    treePointer leftChild, rightChild;
};

void insert(treePointer* root, int key);
void deleteMax(treePointer* root);
void find(treePointer root, int num, int* identify);

int main() {
    char order;
    int num;
    treePointer root = NULL;

    /*Standard input, output representation of the program.
    find function searches if the num value is already in the root.
    If there is, the identifier will be change to 0 to identify 
    whether or not to insert the input number in the max heap.*/

    while (1) {
        scanf(" %c", &order);
        if (order == 'q') {
            break;
        }
        else if (order == 'i') {
            scanf("%d", &num);
            int identifier = 1;
            find(root, num, &identifier);
            if (identifier) {
                insert(&root, num);
                printf("Insert %d\n", num);
            }
            else {
                printf("Exist number\n");
            }
        }
        else if (order == 'd') {
            if (root != NULL) {
                deleteMax(&root);
            }
            else {
                printf("The heap is empty\n");
            }
        }
    }

    return 0;
}

void insert(treePointer* root, int key) {
    treePointer newNode = (treePointer)malloc(sizeof(struct node));
    if (!newNode) {
        fprintf(stderr, "Memory allocation error. Program terminates.\n");
        exit(1);
    }

    newNode->key = key;
    newNode->parent = NULL;
    newNode->leftChild = NULL;
    newNode->rightChild = NULL;

    if (*root == NULL) {
        *root = newNode;
        return;
    }

    treePointer currentNode = *root;
    while (1) {
        if (currentNode->leftChild == NULL) {
            currentNode->leftChild = newNode;
            newNode->parent = currentNode;
            break;
        }
        else if (currentNode->rightChild == NULL) {
            currentNode->rightChild = newNode;
            newNode->parent = currentNode;
            break;
        }
        else {
            /*each node must have a value greater than or equal to its children.
            To maintain the Max Heap property, the smaller right child should have a larger value than the current node.*/
            if (currentNode->leftChild->key >= currentNode->rightChild->key) {
                currentNode = currentNode->rightChild;
            }
            else {
                currentNode = currentNode->leftChild;
            }
        }
    }
    /*Max Heap reordering*/
    while (newNode->parent != NULL && newNode->key > newNode->parent->key) {
        int tempKey = newNode->key;
        newNode->key = newNode->parent->key;
        newNode->parent->key = tempKey;
        newNode = newNode->parent;
    }
}

void deleteMax(treePointer* root) {
    if (*root == NULL) {
        printf("The heap is empty\n");
        return;
    }
    int deletedValue = (*root)->key;
    treePointer lastNode = *root;

    /*exceptinal error handling. if key value of the root only exists.*/
    if (lastNode->leftChild == NULL && lastNode->rightChild == NULL) {
        free(lastNode);
        *root = NULL;
        printf("Delete %d\n", deletedValue);
        return;
    }

    /*search and update following max heap rule until the lastNode is leaf node. */
    while (lastNode->leftChild != NULL || lastNode->rightChild != NULL) {
        if (lastNode->rightChild != NULL) {
            if (lastNode->leftChild != NULL && lastNode->leftChild->key >= lastNode->rightChild->key) {
                lastNode->key = lastNode->leftChild->key;
                lastNode = lastNode->leftChild;
            }
            else {
                lastNode->key = lastNode->rightChild->key;
                lastNode = lastNode->rightChild;
            }
        }
        else { /* lastNode->rightChild is NULL */
            lastNode->key = lastNode->leftChild->key;
            lastNode = lastNode->leftChild;
        }
    }
    /*update parent and child relationship and finally delete lastNode*/
    if (lastNode->parent != NULL) {
        if (lastNode->parent->leftChild == lastNode) {
            lastNode->parent->leftChild = NULL;
        }
        else {
            lastNode->parent->rightChild = NULL;
        }
        free(lastNode);
    }
    else {
        free(lastNode);
        *root = NULL;
    }

    printf("Delete %d\n", deletedValue);
}

void find(treePointer root, int num, int *identify) {
    /*if the input key value is already in the heap, change identify to 0*/
    /*find function just searches with recursive mechanism*/
    if (root == NULL) {
        return;
    }
    if (root->key == num) {
        *identify = 0;
    }
    find(root->leftChild, num, identify);
    find(root->rightChild, num, identify);
}