#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_LITS_SIZE 1000
typedef int element;      // 항목의 정의
typedef struct ListNode { // 리스트 노드 정의
    element data;
    struct ListNode *link;
} ListNode;

typedef struct {
    ListNode *head; // 리스트 헤드 포인터
    int size;       // 현재 리스트에 저장된 항목들의 개수
} CircularListType;

// 리스트 초기화 함수
CircularListType *create_list() {
    CircularListType *list =
        (CircularListType *)malloc(sizeof(CircularListType));
    list->size = 0;
    list->head = NULL;
    return list;
}

// 리스트 출력(데이터가 없는 경우에도 잘 출력되도록 구현)
void print_list(CircularListType *L) {
    printf("CircularList(%d) [", L->size);
    if (L->head != NULL) {
        ListNode *cur = L->head->link;
        while (cur != L->head) {
            printf("%d, ", cur->data);
            cur = cur->link;
        }
        printf("%d", cur->data);
    }
    printf("]\n");
}
// 리스트가비어있으면true를반환, 그렇지않으면false를반환
bool is_empty(CircularListType *L) {
    returnL->size == 0;
}
// 리스트가가득차있으면true를반환, 그렇지않으면false를반환
bool is_full(CircularListType *L) {
    returnL->size == MAX_LIST_SIZE;
}
// 현재리스트의아이템개수를반환
bool get_length(CircularListType *L) {
    returnL->size;
}
int main() {
    CircularListType *list = create_list();
    print_list(list);
    return 0;
}