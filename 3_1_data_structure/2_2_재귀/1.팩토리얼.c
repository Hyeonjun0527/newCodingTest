#include <stdio.h>

// 재귀를 이용한 팩토리얼 함수
int factorial(int n) {
    // n이 1 이하이면 팩토리얼 결과는 1
    if (n <= 1)
        return 1;
    else
        // n! = n * (n-1)!
        return n * factorial(n - 1);
}

// 반복문을 이용한 팩토리얼 함수
int factorial_iter(int n) {
    int k = 1;
    int ret = 1;
    // n부터 1까지 차례로 곱해나감
    for (k = n; k > 0; k--) {
        ret *= k;
    }
    return ret;
}

int main() {
    // 예시: 출력 및 테스트는 필요시 추가
    // printf("%d\n", factorial(5));       // 120
    // printf("%d\n", factorial_iter(5));  // 120
    return 0;
}
