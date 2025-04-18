#include <stdio.h>

// 최대공약수(GCD)를 구하는 함수(유클리드 호제법 사용)
int gcd(int a, int b) {
    // b가 0이 될 때까지 반복
    // GCD(a,b) = GCD(b,a%b)
    while (b != 0) {
        int tmp = b;
        b = a % b; // 나머지를 새로운 b로
        a = tmp;   // b였던 값을 a로
    }
    // b가 0이 될 때의 a값이 최대공약수
    return a;
}

int main() {
    // gcd(48,12) = 12
    printf("GCD of (48,12) = %d\n", gcd(48, 12));
    // gcd(270,192) = 6
    printf("GCD of (270,192) = %d\n", gcd(270, 192));
    // gcd(2,2) = 2
    printf("GCD of (2,2) = %d\n", gcd(2, 2));
    // gcd(5,7) = 1 (서로소)
    printf("GCD of (5,7) = %d\n", gcd(5, 7));
    // gcd(1,2) = 1
    printf("GCD of (1,2) = %d\n", gcd(1, 2));

    return 0;
}
