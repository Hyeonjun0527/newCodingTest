#include <stdio.h>

// 분할정복 재귀적인 방법
double power(double x, int n) {
    if (n == 0)
        return 1;
    else if (n % 2 == 0)
        return power(x * x, n / 2);
    else
        return x * power(x * x, (n - 1) / 2);
}
// 기존에는 n을 1씩 줄이면서 x => x^2 => x^3 이렇게 했었음
// x => x^2 => x^4 => x^8 이렇게 증가시켜. n을 반씩 줄이면서.
// 분할정복 반복적인 방법
double power_iter(double x, int n) {
    double result = 1.0;

    while (n > 0) {
        if (n % 2 == 1)
            result *= x;
        x *= x;
        n /= 2;
    }
    return result;
}

int main() {
    int x, n, sol;
    scanf("%d %d", &x, &n);
    sol = power_iter(x, n);
    printf("%d", sol);
    return 0;
}
