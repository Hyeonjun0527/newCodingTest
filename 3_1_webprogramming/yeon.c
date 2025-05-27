#include <stdio.h>

int func(int i, int k, int num1, char eq[]) {
    for (int j = k; j < i; j++) {
        int num = eq[j] - '0';
        int q = i - 1 - j;
        if ('0' <= eq[j] && eq[j] <= '9') {
            while (q--) {
                num *= 10;
            }
        }
        num1 += num;
        // printf("보자 : %d\n", num1);
    }
    // printf("일단 보자 : %d\n\n\n\n\n", num1);
    return num1;
}

int main(void) {
    char eq[100]; // 100개짜리 문자열을 만들고..
    double result;
    int num1 = 0, num2 = 0, num3 = 0;
    char op1, op2;
    int i; // 왜 밖에서 하냐? 여러 for문에서 사용할꺼라서
    printf("수식을 입력하세요:");
    scanf("%s\n", eq);
    // 123+23-42
    // 1000 20000
    for (i = 0;; i++) // 종료조건이 없음
    {
        if ('0' <= eq[i] && eq[i] <= '9') {
        } else
            break;
    }
    // 123+23-42 이런식을 주면 123까지만 읽으니까 i= 3가 되겠지.

    num1 = func(i, 0, num1, eq);

    op1 = eq[i];
    i++;
    int k = i;
    for (;; i++) {
        if ('0' <= eq[i] && eq[i] <= '9') {
        } else
            break;
    }

    // 123+23-42 이런식을 주면 123까지만 읽으니까 i= 3가 되겠지.
    num2 = func(i, k, num2, eq);

    op2 = eq[i];
    i++;
    k = i;
    for (;; i++) {
        if ('0' <= eq[i] && eq[i] <= '9') {
        } else
            break;
    }

    num3 = func(i, k, num3, eq);

    result = num1 + num2 - num3;

    printf("수식의 결과값은 %lf입니다\n", result);
}