#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_LIST_SIZE 1000
typedef int element; // 항목의정의
typedef struct {     // 리스트노드 정의
    element data;
    struct ListNode *next_node;
} ListNode;
typedef struct {
    ListNode *head; // 리스트헤드포인터
    int size;       // 현재리스트에저장된항목들의개수
} LinkedListType;
// 리스트초기화함수
LinkedListType create_list() {
    LinkedListType list;
    list.size = 0;
    list.head = NULL;
    return list;
}
// 리스트출력(데이터가없는경우에도잘출력되도록구현)
void print_list(LinkedListType *L) {
    printf("LinkedList(%d) [", L->size);
    if (L->head != NULL) {
        // 전체리스트순회
        ListNode *cur = L->head;
        while (cur->next_node != NULL) {
            printf("%d, ", cur->data);
            cur = cur->next_node;
        }
        printf("%d", cur->data);
    }
    printf("]\n");
}

// 리스트가비어있으면true를반환, 그렇지않으면false를반환
bool is_empty(LinkedListType *L) {
    return L->size == 0;
}
// 리스트가가득차있으면true를반환, 그렇지않으면false를반환
bool is_full(LinkedListType *L) {
    return L->size == MAX_LIST_SIZE;
}
// 현재리스트의아이템개수를반환
bool get_length(LinkedListType *L) {
    return L->size;
}
// 오류처리함수
void error(const char *message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}
// 리스트의특정위치의값을반환
element get_entry(LinkedListType *L, int pos) {
    if (pos < 0 || pos > L->size)
        error("Wrong position");
    ListNode *cur = L->head;
    for (int i = 0; i < pos; i++) {
        cur = cur->next_node;
    }
    return cur->data;
}
// 전체 메모리 해제
// 현재 포인터저장. 다음 포인터이동. 그리고 현재를 삭제하면 돼. 현재가
// NULL일때까지 반복
element clear(LinkedListType *L) {
    ListNode *cur = L->head;
    ListNode *temp;
    while (cur != NULL) {
        temp = cur;
        cur = cur->next_node;
        free(temp);
    }
    L->head = NULL;
    L->size = 0;
    // free(L)하면 리스트 자체가 삭제되어버림.
}
ListNode *create_node(element value, ListNode *next_node) {
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));
    p->data = value;
    p->next_node = next_node;
    return p;
}
void insert_front(LinkedListType *L, element value) {
    L->head = create_node(value, L->head);
    L->size++;
}

void insert_last(LinkedListType *L, element value) {
    ListNode *p = create_node(value, NULL);

    if (L->head == NULL) {
        L->head = p;
    } else {
        ListNode *cur = L->head;
        while (cur->next_node != NULL) {
            cur = cur->next_node;
        }
        // while문이 끝나면 cur->next_node == NULL이야. 그래서
        cur->next_node = p;
    }
    L->size++;
}

void insert(LinkedListType *L, int pos, element value) {
    if (pos < 0 || pos >= L->size) {
        printf("Wrong position\n");
        return;
    }
    if (pos == 0) {
        L->head = create_node(value, L->head);
    } else {
        ListNode *cur = L->head;
        for (int i = 0; i < pos - 1; i++) {
            cur = cur->next_node;
        }
        cur->next_node = create_node(value, cur->next_node);
    }
    L->size++;
}

void remove_front(LinkedListType *L) {
    if (L->head == NULL) {
        return;
    }
    // 저장하자 헤드 옮기고, 삭제해야되니까 미리 저장해놔.
    ListNode *cur = L->head;

    L->head = cur->next_node;
    L->size--;
    free(cur);
}
void remove_last(LinkedListType *L) {
    ListNode *cur = L->head;
    ListNode *prev_node;

    if (cur->next_node == NULL) {
        L->head = NULL;
    } else {
        while (cur->next_node != NULL) {
            prev_node = cur;
            cur = cur->next_node;
        }
        prev_node->next_node = NULL;
    }
    free(cur);
    L->size--;
}

void remove_(LinkedListType *L, int pos) {
    if (pos < 0 || pos >= L->size)
        return;

    ListNode *prev_node = L->head;
    for (int i = 0; i < pos - 1; i++) {
        prev_node = prev_node->next_node;
    }
    ListNode *removed = prev_node->next_node;
    prev_node->next_node = removed->next_node;
    L->size--;
    free(removed);
}
int main() {
    LinkedListType list = create_list();
    for (int i = 0; i < 5; i++) {
        insert_last(&list, i);
        print_list(&list);
    }
    for (int i = 0; i < 5; i++) {
        remove_last(&list);
        print_list(&list);
    }

    for (int i = 0; i < 5; i++) {
        insert_front(&list, i * 10);
    }
    print_list(&list);
    insert_front(&list, 1);
    print_list(&list);
    insert(&list, 4, 5);
    print_list(&list);
    remove_front(&list);
    print_list(&list);
    remove_(&list, 3);
    print_list(&list);
    clear(&list);
    print_list(&list);
    return 0;
}