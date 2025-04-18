#include <stdio.h>
#include <time.h>

// 반복적인 방법으로 x^n(거듭제곱)을 구하는 함수
double power_iterative(double x, int n) {
    double result = 1.0;
    // n번 반복하며 result에 x를 계속 곱함
    for (int i = 0; i < n; i++) {
        result *= x;
    }
    return result;
}

// 재귀적인 방법으로 x^n(거듭제곱)을 구하는 함수
double power_recursive(double x, int n) {
    // n이 0이면 x^0 = 1이므로 1 반환
    if (n == 0) {
        return 1.0;
    }
    // x * x^(n-1)을 이용하여 재귀적으로 계산
    return x * power_recursive(x, n - 1);
}

int main() {
    clock_t start, end;
    start = clock();

    // 반복 함수를 10000번 호출하여 시간 측정
    for (int i = 0; i < 10000; i++) {
        power_iterative(2, i);
    }
    end = clock();
    // 측정된 시간 출력
    printf("The power_iterative took %f seconds.\n",
           ((double)end - start) / CLOCKS_PER_SEC);

    clock_t s, e;
    s = clock();

    // 재귀 함수를 10000번 호출하여 시간 측정
    for (int i = 0; i < 10000; i++) {
        power_recursive(2, i);
    }
    e = clock();
    // 측정된 시간 출력
    printf("The power_recursive took %f seconds.\n",
           ((double)e - s) / CLOCKS_PER_SEC);

    return 0;
}
