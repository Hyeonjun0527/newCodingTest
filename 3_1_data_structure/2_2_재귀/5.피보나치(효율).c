#include <stdio.h>

/// @brief 반복적인 방법으로 피보나치 구하기
int fib_iter(int n) {
    // 기저 케이스
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;

    int result = 0;
    int pp = 0; // fib(n-2) 값
    int p = 1;  // fib(n-1) 값
    for (int i = 2; i <= n; i++) {
        // 현재 항 = 이전 항 2개의 합
        result = p + pp;
        // 다음 계산을 위해 값 갱신
        pp = p;
        p = result;
    }
    return result;
}

/// @brief 메모이제이션을 이용한 재귀 피보나치(비효율 개선)
int mem_fib[50] = {
    0,
}; // 미리 0으로 초기화
int fib(int n) {
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    // mem_fib[n]이 0이면 아직 계산 안 함
    if (mem_fib[n] == 0)
        mem_fib[n] = fib(n - 1) + fib(n - 2);
    return mem_fib[n];
}

int main() {
    // 예시 테스트
    // printf("%d\n", fib_iter(10));  // 55
    // printf("%d\n", fib(10));       // 55 (메모이제이션)
    return 0;
}
