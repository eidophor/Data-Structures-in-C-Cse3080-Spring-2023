#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int change(char a);
int result(char a[]);
char *printNum(int a);

int main() {
	int T, ans[2];
	char imp[1000];
	scanf("%d", &T);

	for (int i = 0; i < T; i++) {
		char str[2][1000], res[1000];
		int output;

		scanf("%s", str[0]);
		scanf("%s", str[1]);
		ans[0] = result(str[0]);
		ans[1] = result(str[1]);
		output = ans[0] + ans[1];
		strcpy(imp, printNum(output));

		printf("%s+%s=%s\n", str[0], str[1], imp);
		printf("%d+%d=%d\n", ans[0], ans[1], output);

	}
	return 0;
}


int change(char a) {
	switch (a) {
	case 'I': return 1; break;
	case 'V': return 5; break;
	case 'X': return 10; break;
	case 'L': return 50; break;
	case 'C': return 100; break;
	case 'D': return 500; break;
	case 'M': return 1000; break;
	}

}

int result(char a[]) {
	char input[1000];
	strcpy(input, a);

	int len = strlen(input), num = 0;

	for (int i = 0, j = 1; i < len; i++) {
		if (change(input[i]) < change(input[j])) {
			num += change(input[j]) - change(input[i]);
			i++; j += 2;
		}
		else {
			num += change(input[i]);
			j++;
		}
	}
	return num;
}


char *printNum(int a) {
	char str[1000];
	int j = -1, input = a, num[4];

	num[0] = input / 1000 * 1000;
	input = input - num[0];
	num[1] = input / 100 * 100;
	input = input - num[1];
	num[2] = input / 10 * 10;
	input = input - num[2];
	num[3] = input;

	for (int i = 0; i < 4; i++) {
		if (num[i] == 0) continue;
		else {
			switch (num[i]) {
			case 1: str[++j] = 'I'; break;
			case 2: str[++j] = 'I'; str[++j] = 'I'; break;
			case 3: str[++j] = 'I'; str[++j] = 'I'; str[++j] = 'I'; break;
			case 4: str[++j] = 'I'; str[++j] = 'V'; break;
			case 5: str[++j] = 'V'; break;
			case 6: str[++j] = 'V'; str[++j] = 'I'; break;
			case 7: str[++j] = 'V'; str[++j] = 'I'; str[++j] = 'I'; break;
			case 8: str[++j] = 'V'; str[++j] = 'I'; str[++j] = 'I'; str[++j] = 'I';break;
			case 9: str[++j] = 'I'; str[++j] = 'X'; break;
			case 10: str[++j] = 'X'; break;
			case 20: str[++j] = 'X'; str[++j] = 'X'; break;
			case 30: str[++j] = 'X'; str[++j] = 'X'; str[++j] = 'X'; break;
			case 40: str[++j] = 'X'; str[++j] = 'L'; break;
			case 50: str[++j] = 'L'; break;
			case 60: str[++j] = 'L'; str[++j] = 'X'; break;
			case 70: str[++j] = 'L'; str[++j] = 'X'; str[++j] = 'X'; break;
			case 80: str[++j] = 'L'; str[++j] = 'X'; str[++j] = 'X'; str[++j] = 'X'; break;
			case 90: str[++j] = 'X'; str[++j] = 'C'; break;
			case 100: str[++j] = 'C'; break;
			case 200: str[++j] = 'C'; str[++j] = 'C'; break;
			case 300: str[++j] = 'C'; str[++j] = 'C'; str[++j] = 'C'; break;
			case 400: str[++j] = 'C'; str[++j] = 'D'; break;
			case 500: str[++j] = 'D'; break;
			case 600: str[++j] = 'D'; str[++j] = 'C'; break;
			case 700: str[++j] = 'D'; str[++j] = 'C'; str[++j] = 'C'; break;
			case 800: str[++j] = 'D'; str[++j] = 'C'; str[++j] = 'C'; str[++j] = 'C'; break;
			case 900: str[++j] = 'C'; str[++j] = 'M'; break;
			case 1000: str[++j] = 'M'; break;
			case 2000: str[++j] = 'M'; str[++j] = 'M'; break;
			case 3000: str[++j] = 'M'; str[++j] = 'M'; str[++j] = 'M'; break;
			}
		}
	}
	str[++j] = '\0';
	return str;
}


