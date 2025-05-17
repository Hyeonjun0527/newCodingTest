#include <stdio.h>
#include <stdlib.h>
// 스택의노드구조체
typedef int element;
typedef struct StackNode {
    element data;
    struct StackNode *next_node;
} StackNode;
// 스택의관리구조체
typedef struct {
    StackNode *top;
    int size;
} LinkedStackType;

// 스택생성
LinkedStackType *create_stack() {
    LinkedStackType *s = (LinkedStackType *)malloc(sizeof(LinkedStackType));
    s->top = NULL;
    s->size = 0;
    return s;
}
// 스택제거(동적할당은같은수준에서해제)
void free_stack(LinkedStackType *s) {
    StackNode *temp;
    while (s->top != NULL) {
        temp = s->top;
        s->top = s->top->next_node;
        free(temp);
    }
    free(s);
}
// 공백상태검출함수
int is_empty(LinkedStackType *s) {
    return (s->top == NULL);
}
// 포화상태검출함수
int is_full(LinkedStackType *s) {
    return 0;
}
// 스택의크기반환
int get_size(LinkedStackType *s) {
    returns->size;
}

// 순회및프린트함수
void print_stack(LinkedStackType *s) {
    for (StackNode *p = s->top; p->next_node != NULL; p = p->next_node)
        printf("%d->", p->data);
    printf("%d //", p->data);
    printf("NULL \n");
}

// Top의데이터확인
element peek(LinkedStackType *s) {
    if (s->size == 0)
        return -1;
    return s->top->data;
}

// 삽입 함수
void push(LinkedStackType *s, element item) {
    StackNode *temp =
        // (1) create node
        (StackNode *)malloc(sizeof(StackNode));
    temp->data = item;
    temp->next_node = s->top; // (2) push node
    s->top = temp;            // (3) move top
    s->size++;
}

// 삭제함수
element pop(LinkedStackType *s) {
    if (is_empty(s)) {
        fprintf(stderr, "Stack isEmpty\n");
        exit(1);
    } else {
        StackNode *temp = s->top;   // (1) copy next_node
        s->top = s->top->next_node; // (2) move top
        element data = temp->data;  // (3) backup data
        free(temp);                 // (3) free memory
        s->size++;
        return data;
    }
}

int main() {
    LinkedStackType *s = create_stack();
    int i;
    for (i = 0; i < 10; i++) {
        push(s, i);
    }
    printf("Current top: %d\n", peek(s));
    for (i = 0; i < 10; i++) {
        printf("%d\n", pop(s));
    }
    printf("%d\n", pop(s));
    return 0;
}