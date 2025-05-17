#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MAX_LEN 1000

// 여는 괄호 스택을 직접 배열로 구현
typedef struct {
    char data[MAX_LEN];
    int top;//인덱스야
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

    // 모든 괄호가 스택에서 정상적으로 pop되었다면 균형(=성공)
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

/*

1.스택 준비
여는 괄호 만나면 push.
닫는 괄호 만나면 pop해서 짝이 맞는지 확인.

2. 순서
문자열을 처음부터 끝까지 한 글자씩 본다.
여는 괄호 ( { [ 는 스택에 push.
닫는 괄호 ) } ] 는 스택에서 하나 pop하고,
올바른 쌍인지 검사(+비었는지 검사).
다른 문자(알파벳/숫자 등)는 무시.

3. 결과 판단
전부 검사한 뒤 스택이 비었으면 균형(T),
비어있지 않으면 불균형(F).
*/

/*
1.연산자 스택 준비 (push, pop, 우선순위 확인).

2. 피연산자면 결과에 바로 추가,
연산자면 스택에서 우선순위 같거나 높은 연산자 pop 후 결과에 추가
그리고 새 연산자 push.

3. 남은 연산자도 마지막에 전부 결과로 추가.
*/

/*
이거 말로만 매우 축약해서 암기하기 쉽게 만들어서
말로 암기하고 그걸 기반으로 코드짜는 연습할래.

초간단 암기용 요약
연결 스택 만들기:
StackNode (데이터, 링크)
LinkedStackType (top, size)
create_stack, push, pop, is_empty, free_stack

후위 계산:
문자열 공백으로 잘라서(token)
숫자면 push
연산자면 pop 2번 → 연산 → push
끝나면 pop해서 결과

메인:
fgets로 문자열 입력
개행 제거
evaluatePostfix 호출 → 결과 출력

*/