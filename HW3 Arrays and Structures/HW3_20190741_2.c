#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/* struct and struct pointer definition is not a global variable*/

struct data{
	char word[100000];
	struct data *link;
};


int compare(char* str1, char* str2);
void liveSort();

int main() {
	liveSort();
	return 0;
}

int compare(char* str1, char* str2) {
	int i = 0;
	while (str1[i] != '\0' && str2[i] != '\0') {
		if (str1[i] == str2[i]) {
			i++;
			continue;
		}
		else if (str1[i] < str2[i]) {
			return -1;
		}
		else {
			return 1;
		}
	}
	// have same characters until the index min(length of str1, length of str2)-1.

	if (str1[i] == '\0' && str2[i] == '\0') {
		return 0;   //equal case
	}
	else if (str1[i] == '\0') {
		return -1;    //str2 is same as str1 until index(i-1) and has more characters
	}
	else {
		return 	1;		 //str1 is same as str2 until index(i-1) and has more characters
	}
}

void liveSort() {
    int num = 0, countT = 0;
    struct data* head = (struct data*)malloc(sizeof(struct data));
    struct data* tail = (struct data*)malloc(sizeof(struct data));
    struct data* curr = (struct data*)malloc(sizeof(struct data));
  

    while (1) {
        int found = 0, cmp = 0, count = 1;
      
        struct data* new_word;
      

        while (1) {
            int countW = 0, same = 0;
            new_word = (struct data*)malloc(sizeof(struct data));
            if (!new_word) {
                    printf("Memory allocation error\n");
                    exit(1);
                    return;
            }
            new_word->link = NULL;
            scanf("%s", new_word->word);

            while (countW <= 100 && new_word->word[countW] != '\0') {
                countW++;
            }

            if (compare(new_word->word, "exit") == 0) {
                exit(1);
            }

            if (countW > 100) {
                printf("The number of characters of input word is over than 100. Please input less than or equal to 100 characters.\n");
                free(new_word);
                continue;
            }

            if (countT >= 100) {
                printf("The number of input words is now over than 100. Program terminates.");
                exit(1);
            }

            if (countT > 0) {
                curr = head;
                while (curr != NULL) {
                    if (!compare(new_word->word, curr->word)) {
                        printf("The input word is already in the dictionary. Please input other word again.\n");
                        same = 1;
                        free(new_word);
                        break;
                    }
                    curr = curr->link;
                }
            }
            if (same == 1) continue;
            if (countW > 100) continue;
            break;
        }

        countT++;
        //normal input


        if (num == 0) {
            head = new_word;
            tail = new_word;
        }
        else {
            cmp = compare(new_word->word, head->word);
            if (cmp < 0) {
                new_word->link = head;
                head = new_word;
            }
            else {
                curr = head;
                while (curr->link != NULL && compare(new_word->word, curr->link->word) >= 0) {
                    curr = curr->link;
                }
                new_word->link = curr->link;
                curr->link = new_word;
                if (tail == curr) {
                    tail = new_word;
                }
            }
        }

        num++;

        curr = head;
        while (curr != NULL) {
            if (countT == 1) printf("%s", curr->word);
            else if (count == countT) printf("%s", curr->word);
            else {
                printf("%s, ", curr->word);
                count++;
            }
            curr = curr->link;
        }
        printf("\n");
    }

    //free memory from head to tail
    curr = head;
    while (curr != NULL) {
        struct data* temp = curr->link;
        free(curr);
        curr = temp;
   }
}