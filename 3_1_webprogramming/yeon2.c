#include <stdio.h>
int main(void) {
    char eq[100]; // 100개짜리 문자열을 만들고.. eqaution : eq // 123+23-42
    double result;
    int num1 = 0, num2 = 0, num3 = 0;

    char op1, op2;

    int i; // 왜 밖에서 하냐? 여러 for문에서 사용할꺼라서

    printf("수식을 입력하세요:");

    scanf("%s", eq);

    // 123+23-42
    // 123-23+42
    // 123*23*42
    // 123/12/12
    for (i = 0;; i++) // 종료조건이 없음
    {
        if ('0' <= eq[i] && eq[i] <= '9') {

            // eq[i]-'0' --> 숫자로 바뀌고.. 기존에 누적된
            // 숫자에 10을 곱해서 더하면 된다

        }

        else
            break;
    }

    op1 = eq[i];

    i++;

    for (;; i++)

    {

        if ('0' <= eq[i] && eq[i] <= '9')

        {

        }

        else
            break;
    }

    op2 = eq[i];

    i++;

    for (; eq[i]; i++)

    {

        if ('0' <= eq[i] && eq[i] <= '9')

        {

        }

        else
            break;
    }

    printf("수식의 결과값은 %lf입니다\n", result);
}