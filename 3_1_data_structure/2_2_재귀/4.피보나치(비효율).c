#include <stdio.h>

// 재귀를 이용한 비효율적인 피보나치
int fib(int n) {
    // fib(0) = 0, fib(1) = 1
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    // fib(n) = fib(n-1) + fib(n-2)
    return (fib(n - 1) + fib(n - 2));
}

int main() {
    // 예시: printf("%d\n", fib(5)); // 5
    return 0;
}
