#include <stdio.h>
#include <stdlib.h>
typedef int element;
typedef struct ListNode { // 노드 타입을 구조체로 정의한다.
    element data;
    struct ListNode *link;
} ListNode;

int main() {
    ListNode *head = NULL;
    head = (ListNode *)malloc(sizeof(ListNode));
    head->data = 10; // 1번째 노드
    head->link = NULL;

    // 2번째노드생성
    ListNode *p;
    p = (ListNode *)malloc(sizeof(ListNode));
    p->data = 20;
    p->link = NULL;
    head->link = p; // // 1번째-2번째노드의연결

    // 노드의끝으로이동
    ListNode *cur = head;
    while (cur->link != NULL) { // 마지막으로이동
        cur = cur->link;
    }

    // 지정된위치의노드로이동
    int pos = 3;
    ListNode *cur = head;
    int count = 0;
    while (cur != NULL && count < pos) {
        cur = cur->link;
        count++;
    }
    return cur; // return NULL or a node at pos

    // 특정 값을 가지는 노드 탐색
    int value = 5;
    ListNode *cur = head;
    while (cur != NULL && cur->data == value) {
        cur = cur->link;
    }
    return cur; // return NULL or a node at pos

    ListNode *head = NULL; // 리스트의headpointer

    // 노드의값을이용하여원하는위치에추가
    ListNode *prev = NULL;
    ListNode *cur = head;
    while (cur != NULL && cur->data < value) {
        prev = cur;
        cur = cur->link;
    }
    if (prev == NULL)
        head = create_node(value, head);
    else
        prev->link = create_node(value, prev->link);

    ListNode *head = NULL; // 리스트의headpointer

    // 노드의값을이용하여특정값삭제
    ListNode *prev = NULL;
    ListNode *cur = head;
    while (cur != NULL && cur->data == value) {
        prev = cur;
        cur = cur->link;
    }
    if (prev == NULL)
        head = cur->link;
    else
        prev->link = cur->link;

    free(cur);  // 대상노드메모리해제
    free(p);    // 2번째노드의메모리해제
    free(head); // 1번째노드(헤드)의메모리해제
}