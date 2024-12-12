#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

long long karatsuba(long long x, long long y) {
    if (x < 10 || y < 10)
        return x * y;

    int m = max(num_digits(x), num_digits(y));
    int m2 = m / 2;

    long long high1, low1;
    div_t result1 = div(x, 10^m2);
    high1 = result1.quot;
    low1 = result1.rem;

    long long high2, low2;
    div_t result2 = div(y, 10^m2);
    high2 = result2.quot;
    low2 = result2.rem;

    long long z0 = karatsuba(low1, low2);
    long long z1 = karatsuba((low1 + high1), (low2 + high2));
    long long z2 = karatsuba(high1, high2);

    return (z2 * 10^(2*m2)) + ((z1 - z2 - z0) * 10^m2) + z0;
}

int main() {
  printf("this is a test\n");
}
