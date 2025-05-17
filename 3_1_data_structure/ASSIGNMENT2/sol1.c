#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_LIST_SIZE 1000
typedef int element;      // 항목의정의
typedef struct ListNode { // 리스트노드 정의
    element data;
    struct ListNode *next_node;
} ListNode;
typedef struct LinkedListType {
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
void print_list2(LinkedListType *L) {
    if (L->head != NULL) {
        // 전체리스트순회
        ListNode *cur = L->head;
        int k = 1;
        while (cur->next_node != NULL) {
            printf("%d", cur->data);
            cur = cur->next_node;
            if (L->size - 1 >= k) {
                printf("->");
            }
            k++;
        }
        printf("%d->NULL", cur->data);
    } else {
        printf("NULL");
    }
    printf("\n");
}
// 오류처리함수
void error(const char *message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}
ListNode *create_node(element value, ListNode *link) {
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));
    p->data = value;
    p->next_node = link;
    return p;
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
        // while문이 끝나면 cur->link == NULL이야. 그래서
        cur->next_node = p;
    }
    L->size++;
}
// EXERCISE 1
int find__(LinkedListType *L, int value) {
    ListNode *cur = L->head;
    while (cur != NULL && cur->data != value) {
        cur = cur->next_node;
    }
    if (cur == NULL) {
        error("리스트에 값이 존재하지 않습니다.");
        return -1;
    }
    printf("리스트에서 %d을 찾았습니다.\n", cur->data);
    return cur->data;
}

// EXERCISE 2
ListNode *copy_nodes(ListNode *head) {
    if (head == NULL)
        return NULL;
    ListNode *new_head = create_node(head->data, NULL);
    ListNode *current = new_head;
    head = head->next_node;
    while (head != NULL) {
        current->next_node = create_node(head->data, NULL);
        current = current->next_node;
        head = head->next_node;
    }
    return new_head;
}
LinkedListType union_list(LinkedListType L1, LinkedListType L2) {
    LinkedListType L3 = create_list();

    L3.head = copy_nodes(L1.head);

    ListNode *cur = L3.head;
    if (cur == NULL) {
        L3.head = copy_nodes(L2.head);
    } else {
        while (cur->next_node != NULL) {
            cur = cur->next_node;
        }
        cur->next_node = copy_nodes(L2.head);
    }

    L3.size = L1.size + L2.size;
    return L3;
}
void insert_front(LinkedListType *L, element value) {
    L->head = create_node(value, L->head);
    L->size++;
}
LinkedListType reverse_list(LinkedListType L) {
    LinkedListType rev = create_list();
    ListNode *cur = L.head;

    while (cur != NULL) {
        insert_front(&rev, cur->data);
        cur = cur->next_node;
    }
    return rev;
}

int main() {

    // EXERCISE1
    printf("EXERCISE1\n");
    LinkedListType list = create_list();
    for (int i = 1; i <= 4; i++) {
        insert_last(&list, i * 10);
        print_list(&list);
    }
    find__(&list, 30);
    printf("\nEXERCISE2\n");
    // EXERCISE2
    LinkedListType l1 = create_list();
    LinkedListType l2 = create_list();
    for (int i = 1; i <= 3; i++) {
        insert_last(&l1, i * 10);
        insert_last(&l2, i * 10 + 30);
    }
    LinkedListType l3 = union_list(l1, l2);
    print_list(&l1);
    print_list(&l2);
    print_list(&l3);
    // EXERCISE3
    printf("\nEXERCISE3\n");
    LinkedListType list3 = create_list();
    for (int i = 1; i <= 3; i++) {
        insert_front(&list3, i * 10);
    }
    LinkedListType rev = reverse_list(list3);
    print_list2(&list3);
    print_list2(&rev);

    // EXERCISE4
    // ll_exercise4로..
    return 0;
}