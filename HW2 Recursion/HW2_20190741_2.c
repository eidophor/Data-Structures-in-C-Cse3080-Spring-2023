#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int repCom(int num, int sum);

int main() {
	int n, s;
	scanf("%d", &n);
	scanf("%d", &s);
	if (n == 0) {
		printf("If n is 0, the equation that has no variable cannot be defined."); return 0;
	}
	printf("result: %d\n", repCom(n+s-1, s));

	return 0;
}


int repCom(int num, int sum) {
	int n = num, r = sum;
	int res;
	if (n == r || r == 0) return 1;
	else {
		return repCom(n - 1, r - 1) + repCom(n - 1, r);
	}
}

