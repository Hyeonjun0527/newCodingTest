#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 스택의 노드 정의 (int 데이터 저장)
typedef int element;
typedef struct StackNode {
    element data;
    struct StackNode *next_node;
} StackNode;

// 스택 관리 구조체
typedef struct {
    StackNode *top;
    int size;
} LinkedStackType;

// 스택 생성 함수
LinkedStackType *create_stack() {
    LinkedStackType *s = (LinkedStackType *)malloc(sizeof(LinkedStackType));
    s->top = NULL;
    s->size = 0;
    return s;
}

// 스택 메모리 해제 함수
void free_stack(LinkedStackType *s) {
    StackNode *temp;
    while (s->top != NULL) {
        temp = s->top;
        s->top = s->top->next_node;
        free(temp);
    }
    free(s);
}

// 스택 공백 체크 함수
int is_empty(LinkedStackType *s) {
    return (s->top == NULL);
}

// 스택 push 함수
void push(LinkedStackType *s, element item) {
    StackNode *temp = (StackNode *)malloc(sizeof(StackNode));
    temp->data = item;
    temp->next_node = s->top;
    s->top = temp;
    s->size++;
}

// 스택 pop 함수
element pop(LinkedStackType *s) {
    if (is_empty(s)) {
        fprintf(stderr, "Stack is Empty\n");
        exit(1);
    }
    StackNode *temp = s->top;
    element data = temp->data;
    s->top = s->top->next_node;
    free(temp);
    s->size--;
    return data;
}

// 두 피연산자와 연산자를 받아 연산 결과를 반환하는 함수
int applyOp(int a, int b, char op) {
    switch (op) {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    default:
        return 0;
    }
}

// 후위 표기식을 계산하여 결과를 반환하는 함수
int evaluatePostfix(const char *expr) {
    LinkedStackType *s = create_stack();
    char expr_copy[200];
    strcpy(expr_copy, expr);

    char *token = strtok(expr_copy, " "); // 공백 단위로 토큰 분리

    while (token != NULL) {
        if (isdigit(token[0])) {
            // 숫자일 때는 스택에 push
            push(s, atoi(token));
        } else {
            // 연산자일 때는 스택에서 두 수를 꺼내 연산 수행
            int b = pop(s); // 두 번째 피연산자
            int a = pop(s); // 첫 번째 피연산자
            int result = applyOp(a, b, token[0]);
            push(s, result); // 연산 결과 push
        }
        token = strtok(NULL, " "); // 다음 토큰 가져오기
    }

    int final_result = pop(s); // 최종 결과
    free_stack(s);             // 스택 메모리 해제
    return final_result;
}

int main() {
    char expr[200];

    // 사용자로부터 후위 표기식 입력 받기
    printf("후위 표기식 입력: ");
    fgets(expr, sizeof(expr), stdin);

    // 입력 문자열에서 개행 제거
    expr[strcspn(expr, "\n")] = '\0';

    // 후위 표기식 계산 및 출력
    int result = evaluatePostfix(expr);
    printf("계산 결과: %d\n", result);

    return 0;
}

// 후위 표기식을 공백 기준으로 분리하여 처리 (strtok 함수 사용)

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