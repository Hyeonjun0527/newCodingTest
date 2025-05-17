#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MAX_LEN 1000

// 여는 괄호 스택을 직접 배열로 구현
typedef struct {
    char data[MAX_LEN];
    int top; // 인덱스야
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
    st->data[++(st->top)] = c; // +1하고 +1한 인덱스에 c를 추가
    return true;
}
bool pop(CharStack *st, char *out) {
    if (isEmpty(st)) {
        return false;
    }
    *out = st->data[(st->top)--]; // 꺼내고 인덱스에 -1
    return true;
}
char getOpeningBracket(char c) {
    switch (c) {
    case ')':
        return '(';
    case '}':
        return '{';
    case ']':
        return '[';
    default:
        return '\0';
    }
}

bool isBalanced(const char *str) {
    CharStack s;
    initStack(&s);

    for (int i = 0; str[i] != '\0'; i++) {
        char c = str[i];

        if (c == '(' || c == '{' || c == '[') {
            if (!push(&s, c)) {
                return false;
            }
        } else if (c == ')' || c == '}' |\ c == ']') {
            if (isEmpty(&s)) {
                return false;
            }
            char topChar;
            pop(&s, &topChar);
            if (topChar != getOpeningBracket(c)) {
                return false;
            }
        } else if (isalnum((unsigned char)c)) {
            continue;
        } else {
            continue;
        }
    }
    return isEmpty(&s);
}
