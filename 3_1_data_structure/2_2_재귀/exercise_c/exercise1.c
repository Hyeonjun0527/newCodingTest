#include <stdio.h>
#include <time.h>

/* 반복문으로 x^n 계산 */
double power_iterative(double x, int n) {
    double result = 1.0;
    int i;
    for (i = 0; i < n; ++i) {
        result *= x;
    }
    return result;
}

/* 재귀 호출로 x^n 계산 */
double power_recursive(double x, int n) {
    if (n == 0) {
        return 1.0;             /* x^0 = 1 */
    }
    return x * power_recursive(x, n - 1);
}

int main(void) {
    clock_t start, end;
    int i;

    /* 반복 방식 시간 측정 */
    start = clock();
    for (i = 0; i < 10000; ++i) {
        power_iterative(2.0, i);
    }
    end = clock();
    printf("power_iterative took %f seconds.\n",
           (double)(end - start) / CLOCKS_PER_SEC);

    /* 재귀 방식 시간 측정 */
    start = clock();
    for (i = 0; i < 10000; ++i) {
        power_recursive(2.0, i);
    }
    end = clock();
    printf("power_recursive took %f seconds.\n",
           (double)(end - start) / CLOCKS_PER_SEC);

    return 0;
}
