#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct DListNode {
    element data;
    struct DListNode *prev;
    struct DListNode *next;
} DListNode;

typedef struct {
    DListNode *head;
    int size;
} DLinkedListType;

// 0,NULL, NULL인 싹 빈 노드로 data,prev,next 채워서 만들면 돼.
DListNode *create_node(element value, DListNode *before, DListNode *after) {
    DListNode *node = (DListNode *)malloc(sizeof(DListNode));
    node->data = value;
    node->prev = before;
    node->next = after;
    return node;
}

// 리스트 만드는거?
// head만 만들면돼. head는 양손가락으로 자신을 가르키게 만들어놓아.
DLinkedListType *create_list() {
    DListNode *head = create_node(0, NULL, NULL);
    head->prev = head;
    head->next = head;

    DLinkedListType *list = (DLinkedListType *)malloc(sizeof(DLinkedListType));
    list->head = head;
    list->size = 0;
    return list;
}

// insert_after은 before과 after 둘 다 연결선 고치는거야. 근데 방법이 2가지인거.
// 그림그려보면 확실히 알아. 당연히 before와 다음으로 연결된 친구의 prev부터
// 새로운 노드와 연결해줘야하는거지.
void insert_after(DListNode *before, element data) {
    DListNode *node = create_node(data, before, before->next);
    before->next->prev = node;
    before->next = node;
}
// 처음에 아무것도 없고, insert_after(head,10)호출하는 경우는 head ⇆ A ⇆ head
// 이렇게 됨.

// 얘도 같은 논리로 after와 연결된 친구인 before부터 새로운 노드와
// 연결해줘야하는거야.
void insert_before(DListNode *after, element data) {
    DListNode *node = create_node(data, after->prev, after);
    after->prev->next = node;
    after->prev = node;
}

// node을 삭제하는거야. 센티널(head)과 삭제하려는노드를 줘
// head는 안전 삭제를 위한거야. 그 외 다른 의미는 없어.
bool remove_node(DListNode *head, DListNode *node) {
    if (node == head)
        return false; // head는 센티널노드야. 삭제되면 리스트 자체가 끝이야.
                      // 삭제 거부해.
    node->prev->next = node->next;
    node->next->prev = node->prev;
    free(node);
    return true;
}

// 얘는 안써도 되는거 print_list(list->head);
// 순환이라서 p->next != head 일때까지만
// 반복하면 그게 마지막까지 반복이야.
// 마지막 원소가 p->next != head 를 만족하는 마지막 놈이야.
// 그 다음은 첫번째 요소가 돼.
void print_list(DListNode *head) {
    if (head->prev == head && head->next == head) {
        printf("empty\n");
        return;
    }
    DListNode *p;
    printf("[head node]");
    for (p = head->next; p != head; p = p->next) {
        printf(" %d <->", p->data);
    }
    printf("\n");
}

DListNode *get_node(DLinkedListType *L, int pos) {
    if (pos < 0 || pos >= L->size)
        return NULL;

    DListNode *cur = L->head->next;
    for (int i = 0; i < pos; i++)
        cur = cur->next;
    return cur;
}

// 찾을때까지 다음으로 넘어가.
// 못찾았어? 못찾고, 넘어갔더니 head까지 넘어갔으면 반복안해.
// 쉽게 말해 cur != L->head까지 반복해야 마지막까지 반복이야.
DListNode *find_node(DLinkedListType *L, element value) {
    DListNode *cur = L->head->next;
    while (cur != L->head && cur->data != value)
        cur = cur->next;
    return (cur == L->head) ? NULL : cur;
}

// cur != L->head 였으면 마지막요소까지 출력하고 cur은 head가 돼.
// cur->next != L->head해서 마지막요소 전까지 출력하고, cur은 마지막요소가 돼.
void print_dlist(DLinkedListType *L) {
    printf("DLinkedList(%d) [", L->size);
    if (L->size != 0) {
        DListNode *cur = L->head->next;

        while (cur->next != L->head) {
            printf("%d, ", cur->data);
            cur = cur->next;
        }
        printf("%d", cur->data);
    }
    printf("]\n");
}

// 삽입을 헤드의 다음꺼에 하면 그게 front 삽입인거지.
void insert_front(DLinkedListType *L, element value) {
    insert_after(L->head, value);
    L->size++;
}
// 삽입을 마지막 요소 다음꺼에 하면 그게 last 삽입이야.
// 그런데 삽입을 head 이전꺼에 하면 그것도 last삽입이야. 그게 더 빠르겠지.
void insert_last(DLinkedListType *L, element value) {
    insert_before(L->head, value);
    L->size++;
}

// 삽입을 pos으로 찾는거 다음꺼에 하는거야.
void insert(DLinkedListType *L, int pos, element value) {
    DListNode *cur = get_node(L, pos);
    if (cur != NULL) {
        insert_after(cur, value);
        L->size++;
    }
}
// 삭제는 안전삭제를 위해 인자로 head센티널을 준다고 했어.
// 그리고 삭제를 원하는 노드를 주면 된다고 했어. head의 next를 주면 front
// 삭제인거지.
void remove_front(DLinkedListType *L) {
    if (remove_node(L->head, L->head->next))
        L->size--;
}
// head의 prev를 주면 last 삭제인거지.
void remove_last(DLinkedListType *L) {
    if (remove_node(L->head, L->head->prev))
        L->size--;
}

// pos로 찾고 그거 삭제하면 되겠지.
void remove_pos(DLinkedListType *L, int pos) {
    DListNode *cur = get_node(L, pos);
    if (cur && remove_node(L->head, cur))
        L->size--;
}

// 한바퀴 돌면 cur == L->head 된다.
void clear(DLinkedListType *L) {
    DListNode *cur = L->head->next; // head는 더미라서 head->next.
    DListNode *temp;
    while (cur != L->head) {
        temp = cur;
        cur = cur->next;
        free(temp);
    }
    L->head->next = L->head;
    L->head->prev = L->head;
    L->size = 0;
}

int main() {
    DLinkedListType *list = create_list();
    for (int i = 0; i < 5; i++) {
        insert_front(list, i);
        print_dlist(list);
    }

    DListNode *node = find_node(list, 1);
    if (node)
        printf("Found: %p (%d)\n", node, node->data);
    else
        printf("Node not found\n");

    for (int i = 0; i < 5; i++) {
        remove_front(list);
        print_dlist(list);
    }

    clear(list);
    print_dlist(list);
    free(list->head);
    free(list);
    return 0;
}
