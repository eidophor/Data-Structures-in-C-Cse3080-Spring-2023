#include <stdio.h>
#include <stdlib.h>

int main() {
	int input[105][105], result[105][105], m, n, k;
	scanf_s("%d", &k);
	// update maximum number of foods in the following index at the result array

	for (int repeat = 0; repeat < k; repeat++) {

		scanf_s("%d %d", &m, &n);
	// Input Handling (If the input value M,N < 1, matrix cannot be defined.)
		if (m <= 0 || n <= 0) {
			printf("number of row/column in a matrix should bigger than 0.\n"); 
			continue;
		}

		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				scanf_s("%d", &input[i][j]);
				result[i][j] = 0;
			}
		}

		result[0][0] = input[0][0];
		for (int i = 1; i < n; i++) {
			result[0][i] = result[0][i - 1] + input[0][i];
		}

		for (int i = 1; i < m; i++) {
			result[i][0] = result[i - 1][0] + input[i][0];
		}

		for (int i = 1; i < m; i++) {
			for (int j = 1; j < n; j++) {
				if (result[i - 1][j] > result[i][j - 1]) {
					result[i][j] = result[i - 1][j] + input[i][j];
				}
				else {
					result[i][j] = result[i][j - 1] + input[i][j];
				}
			}
		}

		printf("%d\n", result[m - 1][n - 1]);
	}
	return 0;
}