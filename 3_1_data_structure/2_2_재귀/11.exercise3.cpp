#include <stdio.h>

// 정수 n을 이진수로 변환하여 출력하는 함수
// 단, n < 0 이거나 n > 2100000000 이면 "Not available" 출력
void bin(int n) {
    if (n < 0 || n > 2100000000) {
        printf("Not available\n");
        return;
    }
    // 0이면 바로 "0" 출력 후 종료
    if (n == 0) {
        printf("0\n");
        return;
    }

    char c[100];
    int i = 0;

    // n이 0이 될 때까지 2로 나눈 나머지를 c 배열에 저장
    // 이 때, 2진수는 거꾸로 구해지므로 나중에 뒤집어서 출력
    while (n > 0) {
        c[i++] = (n % 2) + '0'; // '0'을 더해서 문자 형태로 저장
        n /= 2;                 // 2로 나누어 몫으로 갱신
    }

    // 거꾸로 저장된 배열을 역순으로 출력
    for (int j = i - 1; j >= 0; j--) {
        printf("%c", c[j]);
    }
    printf("\n");
}

int main() {
    bin(10);         // 10 -> 1010
    bin(0);          // 0 -> 0
    bin(1);          // 1 -> 1
    bin(2);          // 2 -> 10
    bin(1024);       // 1024 -> 10000000000
    bin(2100000001); // 범위 초과 -> Not available
    return 0;
}
