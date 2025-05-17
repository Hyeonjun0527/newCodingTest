#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode {
    element data;
    struct ListNode *next_node;
} ListNode;

ListNode *create_node(element data, ListNode *next_node) {
    ListNode *new_node = (ListNode *)malloc(sizeof(ListNode));
    if (new_node == NULL) {
        printf("메모리 할당 오류\n");
        exit(1);
    }
    new_node->data = data;
    new_node->next_node = next_node;
    return new_node;
}

element find(element data, ListNode *node) {
    ListNode *p;
    element k = 0;
    while (node->next_node != NULL) {
        if (node->data == data) {
            return node->data;
        }
        node = node->next_node;
    }
    return 0;
}

int main(void) {
    ListNode *head = NULL;
    ListNode *cur = NULL;
    int i;
    int initial_value = 10; // 시작 값

    // 100개의 노드를 생성하여 리스트에 추가
    for (i = 0; i < 100; i++) {
        ListNode *new_node = create_node(initial_value, NULL);
        initial_value += 10; // 원하는 데이터 값 처리 방식 (예: 10씩 증가)
        if (head == NULL) {  // 리스트가 비어있는 경우
            head = new_node;
            cur = head;
        } else {
            cur->next_node = new_node;
            cur = new_node;
        }
    }

    // 예: 값 30을 찾기 (head부터 탐색)
    int target = 30;
    element found = find(target, head);
    if (found)
        printf("리스트에서 %d을(를) 찾았습니다.\n", found);
    else
        printf("리스트에서 %d을(를) 찾지 못했습니다.\n", target);

    // 리스트 출력
    cur = head;
    while (cur != NULL) {
        printf("%d -> ", cur->data);
        cur = cur->next_node;
    }
    printf("NULL\n");

    // 할당한 메모리 해제
    cur = head;
    while (cur != NULL) {
        ListNode *temp = cur;
        cur = cur->next_node;
        free(temp);
    }

    return 0;
}
