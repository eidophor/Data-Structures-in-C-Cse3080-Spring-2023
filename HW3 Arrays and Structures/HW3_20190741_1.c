#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void fail(char*, int failure[]);
void pmatch(char*, char*, int ans[], int failure[], int *);
int pmatch_delete(int ans[], int index[], int *count, int lenS, int lenP);


int main() {
	int failure[100], ans[100], count = 0, index[100], result;
	char *string, *pat;
	int lenS, lenP;

	while (1) {
		string = (char*)malloc(1000000 * sizeof(char));
		if (!string) {
			printf("Memory allocation error\n");
			exit(1);
		}
		scanf("%s", string);
		lenS = strlen(string);
		if (lenS <= 0 || lenS>30) {
			printf("The length of input string must be 1<=length<=30. Please input string again.\n");
			free(string);
			continue;
		}
		else break;
	}

	while (1) {
		pat = (char*)malloc(1000000 * sizeof(char));
		if (!pat) {
			printf("Memory allocation error\n");
			exit(1);
		}
		scanf("%s", pat);
		lenP = strlen(pat);
		if (lenP <= 0 || lenP>30) {
			printf("The length of input pattern must be 1<=pattern<=30. Please input pattern again.\n");
			free(pat);
			continue;
		}
		else if (lenP > lenS) {
			printf("The length of pattern couldn't be longer than that of string. Please input pattern again.\n");
			free(pat);
		}
		else break;
	}
	
	fail(pat, failure);
	pmatch(string, pat, ans, failure, &count);
	result = pmatch_delete(ans, index, &count, lenS, lenP);

	// print result
	if (result == 0) {
		printf("%s\n", string);
	}
	else {
		int printCount = 0;
		for (int i = 0; i < lenS; i++) {
			if (index[i] == 1) {
				printf("%c", string[i]);
				printCount++;
			}
		}
		if (printCount == 0) printf("Empty string. The string is deleted by matched pattern(s).");
		printf("\n");
	}

	free(string); free(pat);
	return 0;
}

void fail(char* pat, int failure[]) {
	int i, j, n = strlen(pat);
	failure[0] = -1;
	for (j = 1; j < n; j++) {
		i = failure[j - 1];
		while ((pat[j] != pat[i + 1]) && (i >= 0)) i = failure[i];
		if (pat[j] == pat[i + 1]) failure[j] = i + 1;
		else failure[j] = -1;
	}
}

void pmatch(char* string, char* pat, int ans[], int failure[], int *count) {
	int i = 0, j = 0, temp;
	int lens = strlen(string);
	int lenp = strlen(pat);
	while (i < lens) {
		if (j == lenp) {
			ans[*count] = i - lenp;
			temp = j;
			(*count)++;
			j = failure[temp - 1] + 1;
		}
		else if (string[i] == pat[j]) {
			i++; j++;
		}
		else if (j == 0) i++;
		else j = failure[j - 1] + 1;
	}
	if (j == lenp) {
		ans[*count] = i - lenp;
		(*count)++;
	}

}

int pmatch_delete(int ans[], int index[], int *count, int lenS, int lenP) {
	int i, j, k;

	for (i = 0; i < lenS; i++) {
		index[i] = 1; 
	}

	if (*count == 0) {
		//no matched pattern
		return 0;
	}

	for (i = 0; i < *count; i++) {
		j = ans[i];
		k = ans[i];
		for ( ;j < k+lenP; j++) {
			index[j] = 0;
		}
	}
	return 1;
	
}
