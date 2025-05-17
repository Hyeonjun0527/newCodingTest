#include <stdio.h>
#include <stdlib.h>
#define DEFAULT_SIZE 2
#define MAX_STACK_SIZE 10
typedef int element;
typedef struct {
    element *data;
    int capacity;
    // data은 포인터로 정의된다.
    // 현재 data의 크기
    int top;
} StackType;

// 스택생성
StackType *create_stack() {
    StackType *s = (StackType *)malloc(sizeof(StackType));
    s->top = -1;
    s->capacity = DEFAULT_SIZE;
    s->data = (element *)malloc(s->capacity * sizeof(element));
    return s;
}
// 스택제거(동적할당은같은수준에서해제)
void free_stack(StackType *s) {
    free(s->data);
    free(s);
}
// Top 값반환
element peek(StackType *s) {
    if (s->top == -1)
        return -1;
    return s->data[s->top];
}
// 공백상태검출함수
int is_empty(StackType *s) {
    return (s->top == -1);
}
// 포화상태검출함수
int is_full(StackType *s) {
    return (s->top == (MAX_STACK_SIZE - 1));
}
// 데이터크기확장(기존내용보존)
bool extend_data(StackType *s) {
    s->capacity += DEFAULT_SIZE; // increase capacity
    s->data = (element *)realloc(s->data, s->capacity * sizeof(element));
    printf("Extended size to %d\n", s->capacity);
    return true;
}
// 삽입함수
void push(StackType *s, element item) {
    if (is_full(s)) {
        fprintf(stderr, "Stackis Full\n");
        return;
    } else {
        // 맨위인덱스가 버퍼의 마지막 칸과 같다면
        //==해도 논리적으론 같게 작동
        if (s->top >= s->capacity - 1)
            extend_data(s);
        s->data[++(s->top)] = item;
    }
}
// 삭제함수
element pop(StackType *s) {
    if (is_empty(s)) {
        fprintf(stderr, "Stack is Empty\n");
        exit(1);
    } else
        return s->data[(s->top)--]
};

int main() {
    StackType *s = create_stack(10);
    int i;
    for (i = 0; i < 10; i++) {
        push(s, i);
    }
    push(s, 10);
    printf("Current Top: %d\n", peek(s));
    for (i = 0; i < 10; i++) {
        printf("%d\n", pop(s));
    }
    printf("%d\n", pop(s));
    free_stack(s);
    return 0;
}
