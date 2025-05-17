#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 1000

// 문자 스택 구현용 구조체
typedef struct {
    char data[MAX_LEN];
    int top;
} CharStack;

// 스택 초기화
void initStack(CharStack *st) {
    st->top = -1;
}

// 스택이 비었는지 확인
int isEmpty(const CharStack *st) {
    return (st->top == -1);
}

// 스택이 가득 찼는지 확인
int isFull(const CharStack *st) {
    return (st->top == MAX_LEN - 1);
}

// 스택에 push
int push(CharStack *st, char c) {
    if (isFull(st)) {
        return 0; // 실패
    }
    st->data[++(st->top)] = c;
    return 1; // 성공
}

// 스택에서 pop
char pop(CharStack *st) {
    if (isEmpty(st)) {
        // 오류 처리 - 여기서는 간단히 에러 메시지 출력하고 종료
        fprintf(stderr, "Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    return st->data[(st->top)--];
}

// 스택의 top을 확인 (제거하지 않음)
char top(const CharStack *st) {
    if (isEmpty(st)) {
        // 스택이 비어있다면 에러 처리 (혹은 특정 문자 반환 등)
        return '\0'; // 여기서는 단순히 널 문자 반환
    }
    return st->data[st->top];
}

// 연산자 우선순위
int precedence(char op) {
    switch (op) {
    case '+':
    case '-':
        return 1; // 덧셈, 뺄셈
    case '*':
    case '/':
        return 2; // 곱셈, 나눗셈
    }
    return 0; // 그 외 (괄호 등)
}

// 중위 표기식 -> 후위 표기식 변환
void infixToPostfix(const char *expr, char *result) {
    CharStack opStack;
    initStack(&opStack);

    int i = 0; // expr 인덱스
    int j = 0; // result 인덱스

    while (expr[i] != '\0') {
        char c = expr[i];

        // 알파벳 또는 숫자면 결과에 추가
        if (isalpha((unsigned char)c) || isdigit((unsigned char)c)) {
            result[j++] = c;

            // 여는 괄호 '('
        } else if (c == '(') {
            push(&opStack, c);

            // 닫는 괄호 ')'
        } else if (c == ')') {
            // '('를 만날 때까지 스택에서 pop하여 결과에 추가
            while (!isEmpty(&opStack) && top(&opStack) != '(') {
                result[j++] = pop(&opStack);
            }
            // '(' pop해서 버린다 (스택에서 제거)
            if (!isEmpty(&opStack) && top(&opStack) == '(') {
                pop(&opStack);
            }

            // 연산자 (+, -, *, /)
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            // 현재 연산자 c의 우선순위보다 높거나 같은 연산자는 전부 pop
            while (!isEmpty(&opStack) &&
                   precedence(top(&opStack)) >= precedence(c) &&
                   top(&opStack) != '(') {
                // top(&opStack) != '('가 있으면 break;해야함
                //'('가 잇으면
                result[j++] = pop(&opStack);
            }
            // 그리고 현재 연산자를 push
            push(&opStack, c);
        }
        // 공백, 기타 문자는 여기서는 무시
        i++;
    }

    // 수식 처리가 끝난 후, 스택에 남아있는 연산자를 모두 pop
    while (!isEmpty(&opStack)) {
        char t = pop(&opStack);
        // 혹시 스택에 '('가 남아있다면 버림
        if (t != '(') {
            result[j++] = t;
        }
    }

    // 문자열 끝
    result[j] = '\0';
}

int main(void) {
    char expr[MAX_LEN + 1];    // 중위표현식
    char postfix[MAX_LEN + 1]; // 후위 표기식은 넉넉함.

    if (!fgets(expr, sizeof(expr), stdin)) {
        // 입력 실패
        return 1;
    }

    // '\n' 제거
    expr[strcspn(expr, "\n")] = '\0';

    infixToPostfix(expr, postfix);
    printf("%s", postfix);

    return 0;
}

/*
1.연산자 스택 준비 (push, pop, 우선순위 확인).

2. 피연산자면 결과에 바로 추가,
연산자면 스택에서 우선순위 같거나 높은 연산자 pop 후 결과에 추가
그리고 새 연산자 push.

3. 남은 연산자도 마지막에 전부 결과로 추가.


변환알고리즘은 연산자를 스택에 넣어.
계산알고리즘은 피연산자를 스택에 넣어.

*/