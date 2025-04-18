#include <stdio.h>

// 반복문을 사용한 x^n 구하기 (비효율 예시)
double slow_power(double x, int n) {
    int i;
    double result = 1.0;
    // n번 반복 곱
    for (i = 0; i < n; i++)
        result *= x;
    return result;
}

// 재귀 함수를 사용한 x^n 구하기 (비효율 예시)
double slow_power_recursive(double x, int n) {
    // n이 0이면 x^0 = 1
    if (n == 0)
        return 1;
    // x * x^(n-1)을 이용
    return x * slow_power_recursive(x, n - 1);
}

int main() {
    // 예시: 출력 및 테스트는 필요시 추가
    // printf("%f\n", slow_power(2.0, 10));            // 1024.0
    // printf("%f\n", slow_power_recursive(2.0, 10));  // 1024.0
    return 0;
}
