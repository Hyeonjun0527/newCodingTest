#include <stdio.h>

// 분할정복을 이용한 재귀적인 x^n 계산
double power(double x, int n) {
    // n이 0이면 x^0 = 1
    if (n == 0)
        return 1;
    // n이 짝수일 때: x^n = (x^2)^(n/2)
    else if (n % 2 == 0)
        return power(x * x, n / 2);
    // n이 홀수일 때: x^n = x * (x^2)^((n-1)/2)
    else
        return x * power(x * x, (n - 1) / 2);
}

// 분할정복을 이용한 반복적인 x^n 계산
double power_iter(double x, int n) {
    double result = 1.0;

    // n이 0이 될 때까지
    while (n > 0) {
        // n이 홀수라면 result에 x를 곱해줌
        if (n % 2 == 1)
            result *= x;
        // 이제 n이 짝수야.
        //  x를 제곱하면 지수가 반토막 나겠지.
        x *= x;
        // 지수가 반토막 났을테니 n을 2로 나눔. log n 번 반복한다.
        n /= 2;
    }
    return result;
}

int main() {
    int x, n;
    scanf("%d %d", &x, &n); // 예: 2 10
    // 분할정복 반복문 버전 사용
    double sol = power_iter(x, n);
    printf("%.0f\n", sol); // 결과 출력 (정수처럼 보고싶다면 %.0f)
    return 0;
}
