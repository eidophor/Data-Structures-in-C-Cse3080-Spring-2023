#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int isInteger(double val);
int min_blocks(int n, int m);

int main() {
    int n, m, num_blocks; 

    scanf("%d", &n);
    scanf("%d", &m);

    num_blocks = min_blocks(n, m);
    printf("The smallest number of blocks required to cover a %d x %d size floor is %d.\n", n, m, num_blocks);
    return 0;
}

int isInteger(double val)
{
    int truncated = (int)val;
    if (val == 0 || truncated == 0) return 0;
    return (val == truncated);
}

int min_blocks(int n, int m) {
    int num1 = n; int num2 = m;
    int a, b;

    if (n == 1 && m == 1) { // base case: single block
        return 1;
    }
    else if (n == 0 || m == 0) return 0;
    else if (isInteger(log2(num1)) && isInteger(log2(num2)) && n == m) {
        return 1;
    }
    else { // recursive case
        int i = -1;
        int j = -1;
        int pow2 = 1;
        while (pow2 <= n) {
            i++;
            pow2 *= 2;
        }
        pow2 = 1;
        while (pow2 <= m) {
            j++;
            pow2 *= 2;
        }
        a = (int)pow(2, i);
        b = (int)pow(2, j);
        if (a < b) b = a;
        if (b < a) a = b;

        return min_blocks(n - a, m - b) + min_blocks(n - a, b) + min_blocks(a, m - b) + min_blocks(a, b);
    }
}
