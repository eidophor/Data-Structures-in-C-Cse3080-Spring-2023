#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_ROW 10
#define MAX_COL 10
#define TRUE 1
#define FALSE 0

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

typedef struct node* nodePointer; 
typedef struct node {
	nodePointer next_link;
	element data;
	nodePointer before_link;
};

void main() {
	FILE *input, *output;
	int i, j, row = 10, col = 10, nextRow, nextCol, dir, found = FALSE, item;
	int exitRow = 8, exitCol = 8;
	int maze[MAX_ROW][MAX_COL];
	int mark[MAX_ROW][MAX_COL];
	nodePointer head, position, new, print, temp;

	input = fopen("maze.txt", "r");
	if (input == NULL) {
		printf("File open error");
		exit(1);
	}

	output = fopen("path.txt", "w");
	if (output == NULL) {
		printf("File open error");
		exit(1);
	}

	//maze input 
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			fscanf(input, "%d", &item);
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
	fclose(input);

	/* more greedy version of move */
	move[0].vert = 0; move[0].horiz = 1;    // East
	move[1].vert = 1; move[1].horiz = 1;    // SE
	move[2].vert = 1; move[2].horiz = 0;    // South
	move[3].vert = 1; move[3].horiz = -1;    // SW
	move[4].vert = 0; move[4].horiz = -1;    // West
	move[5].vert = -1; move[5].horiz = -1;    // NW
	move[6].vert = -1; move[6].horiz = 0;    // North
	move[7].vert = -1; move[7].horiz = 1;    // NE

	mark[1][1] = 1;
	head = (nodePointer)malloc(sizeof(struct node));
	if (!head) {
		fprintf(stderr, "Memory is Full. Program terminates.\n");
		exit(1);
	}
	new = (nodePointer)malloc(sizeof(struct node));
	if (!new) {
		fprintf(stderr, "Memory is Full. Program terminates.\n");
		exit(1);
	}
	/*initial doubly linked lists setting*/
	head->data.row = -1;  head->data.col = -1;  head->data.dir = 10;
	new->data.row = 1; new->data.col = 1; new->data.dir = 0;
	
	head->before_link = new; head->next_link = new;
	new->before_link = head; new->next_link = head;
	position = head->next_link;

	while (position != head && !found) {
		/*delete current position and update position to its before_link*/
		position->before_link->next_link = position->next_link;
		position->next_link->before_link = position->before_link;
		row = position->data.row; col = position->data.col; dir = position->data.dir;
		temp = position;
		position = position->before_link;
		free(temp);
	   
		while (dir < 8 && !found) {
			/* move in direction dir */
			nextRow = row + move[dir].vert;
			nextCol = col + move[dir].horiz;
			if (nextRow == exitRow && nextCol == exitCol && !maze[nextRow][nextCol])
				found = TRUE;
			else if (!maze[nextRow][nextCol] && !mark[nextRow][nextCol]) {
				mark[nextRow][nextCol] = 1;
				new = (nodePointer)malloc(sizeof(struct node));
				if (!new) {
					fprintf(stderr, "Memory is Full. Program terminates.\n");
					exit(1);
				}
				/*insert new node*/
				new->data.row = row; new->data.col = col; new->data.dir = ++dir;
				new->before_link = position; new->next_link = position->next_link;
				position->next_link->before_link = new;
				position->next_link = new;
				position = new;
			
				row = nextRow; col = nextCol; dir = 0;

			}
			else ++dir;
		}
	}

	if (found && !maze[1][1]) {
		print = head->next_link;
		for ( ; print != head; print = print->next_link) {
			fprintf(output, "%2d%5d\n", print->data.row, print->data.col);
		}
		fprintf(output, "%2d%5d\n", row, col);
		fprintf(output, "%2d%5d\n", exitRow, exitCol);
	}
	else fprintf(output, "The maze does not have a path.\n");
	fclose(output);
}

