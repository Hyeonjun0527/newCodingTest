#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MAX_LEN 1000

// 여는 괄호 스택을 직접 배열로 구현
typedef struct {
    char data[MAX_LEN];
    int top;
} CharStack;

void initStack(CharStack *st) {
    st->top = -1; // 스택이 비어있음을 나타냄
}

bool isEmpty(const CharStack *st) {
    return (st->top == -1);
}

bool isFull(const CharStack *st) {
    return (st->top == MAX_LEN - 1);
}

bool push(CharStack *st, char c) {
    if (isFull(st)) {
        return false;
    }
    st->data[++(st->top)] = c;
    return true;
}

bool pop(CharStack *st, char *out) {
    if (isEmpty(st)) {
        return false;
    }
    *out = st->data[(st->top)--];
    return true;
}

// 닫는 괄호에 대응하는 여는 괄호를 반환하는 함수
char getOpeningBracket(char c) {
    switch (c) {
    case ')':
        return '(';
    case '}':
        return '{';
    case ']':
        return '[';
    default:
        return '\0'; // 해당 없음
    }
}

// 문자열이 올바른 괄호열인지 확인
bool isBalanced(const char *str) {
    CharStack s;
    initStack(&s);

    for (int i = 0; str[i] != '\0'; i++) {
        char c = str[i];

        // 여는 괄호인 경우
        if (c == '(' || c == '{' || c == '[') {
            // 스택에 push
            if (!push(&s, c)) {
                // 스택 용량 초과 시 false
                return false;
            }
        }
        // 닫는 괄호인 경우
        else if (c == ')' || c == '}' || c == ']') {
            if (isEmpty(&s)) {
                // 스택이 비어있는데 닫으려 하면 불일치
                return false;
            }
            char topChar;
            pop(&s, &topChar);
            // 매핑된 여는 괄호와 비교
            if (topChar != getOpeningBracket(c)) {
                return false;
            }
        }
        // 알파벳이나 숫자인 경우 (무시)
        else if (isalnum((unsigned char)c)) {
            continue;
        }
        // 그 외 문자 (무시)
        else {
            continue;
        }
    }

    // 모든 괄호가 스택에서 정상적으로 pop되었다면 균형
    return isEmpty(&s);
}

int main() {
    int n;
    scanf("%d", &n); // 테스트 케이스 개수 입력

    // 개행문자가 남아있으면 제거하는 것이 안전
    // (문자열 입력시 영향을 줄 수 있으므로)
    getchar();

    while (n--) {
        char str[MAX_LEN + 1]; // +1: 널문자 고려
        // 공백 없이 한 줄로 입력받는다고 가정
        scanf("%s", str);

        if (isBalanced(str)) {
            printf("T\n");
        } else {
            printf("F\n");
        }
    }

    return 0;
}
