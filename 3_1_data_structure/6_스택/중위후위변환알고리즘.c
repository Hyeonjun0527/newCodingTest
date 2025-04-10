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
int pop(CharStack *st, char *out) {
    if (isEmpty(st)) {
        return 0; // 실패
    }
    *out = st->data[(st->top)--];
    return 1; // 성공
}

// 연산자 우선순위 반환 함수
int precedence(char op) {
    switch (op) {
    case '+':
    case '-':
        return 1; // 덧셈, 뺄셈
    case '*':
    case '/':
        return 2; // 곱셈, 나눗셈
    default:
        return 0;
    }
}

// 중위 표기식 -> 후위 표기식 변환 함수
// expr  : 입력 중위 표기식
// result: 변환된 후위 표기식을 저장할 버퍼
void infixToPostfix(const char *expr, char *result) {
    CharStack opStack;
    initStack(&opStack);

    int i = 0; // expr 인덱스
    int j = 0; // result 인덱스
    char c;

    while ((c = expr[i]) != '\0') {
        // 알파벳 또는 숫자인 경우 (피연산자) 단순히 추가해.
        if (isalpha((unsigned char)c) || isdigit((unsigned char)c)) {
            result[j++] = c;
            result[j++] = ' '; // 피연산자 간 구분 위해 공백 추가
        }
        // 여는 괄호 '('
        else if (c == '(') {
            push(&opStack, c);
        }
        // 닫는 괄호 ')' 나오면
        else if (c == ')') {
            // '('가 나올 때까지 스택에서 pop
            char topChar;
            while (!isEmpty(&opStack)) {
                pop(&opStack, &topChar);
                if (topChar == '(') {
                    // '('는 버리고 종료
                    break;
                }
                // pop된 연산자를 결과에 추가
                result[j++] = topChar;
                result[j++] = ' ';
            }
        }
        // 연산자 (+, -, *, /)
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            char topChar;
            // 스택이 비어있지 않고, 스택 top의 우선순위가 현재 연산자보다
            // 크거나 같다면 pop
            while (!isEmpty(&opStack)) {
                if (!pop(&opStack, &topChar))
                    break;
                if (precedence(topChar) >= precedence(c)) {
                    result[j++] = topChar;
                    result[j++] = ' ';
                } else {
                    // 우선순위가 낮으면 다시 스택에 넣고 중단
                    push(&opStack, topChar);
                    break;
                }
            }
            // 현재 연산자를 스택에 push
            push(&opStack, c);
        }
        // 공백, 기타 문자 등은 여기서는 특별히 처리하지 않고 무시
        else {
            // 필요 시 원하는 대로 처리 가능
        }

        i++;
    }

    // 수식 처리가 끝난 뒤, 스택에 남아있는 연산자를 모두 결과에 추가
    char topChar;
    while (!isEmpty(&opStack)) {
        pop(&opStack, &topChar);
        result[j++] = topChar;
        result[j++] = ' ';
    }

    // 문자열 끝에 널 문자 추가
    result[j] = '\0';
}

int main(void) {
    char expr[MAX_LEN + 1];
    char postfix[MAX_LEN * 2];
    // 후위 표기식은 피연산자 사이에 공백이 추가되므로 조금 더 넉넉히 잡음

    // 수식 한 줄 입력
    // 예: (3+4)*2
    printf("중위 표기식을 입력하세요: ");
    if (!fgets(expr, sizeof(expr), stdin)) {
        // 입력 실패
        return 1;
    }

    // fgets로 읽으면 끝에 '\n'이 포함될 수 있으므로 제거
    expr[strcspn(expr, "\n")] = '\0';

    // 변환 수행
    infixToPostfix(expr, postfix);

    // 결과 출력
    printf("후위 표기식: %s\n", postfix);

    return 0;
}
