#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct Node {
    element data;
    struct Node *prev_node;
    struct Node *next_node;
} Node;

typedef struct {
    Node *head;
    int size;
} DLinkedListType;

// 0,NULL, NULL인 싹 빈 노드로 data,prev,next_node 채워서 만들면 돼.
Node *create_node(element value, Node *before_node, Node *after_node) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = value;
    node->prev_node = before_node;
    node->next_node = after_node;
    return node;
}

// 리스트 만드는거?
// head만 만들면돼. head는 양손가락으로 자신을 가르키게 만들어놓아.
DLinkedListType *create_list() {
    Node *head = create_node(0, NULL, NULL);
    head->prev_node = head;
    head->next_node = head;

    DLinkedListType *list = (DLinkedListType *)malloc(sizeof(DLinkedListType));
    list->head = head;
    list->size = 0;
    return list;
}

// insert_after은 before과 after_node 둘 다 연결선 고치는거야. 근데 방법이
// 2가지인거. 그림그려보면 확실히 알아. 당연히 before와 다음으로 연결된 친구의
// prev부터 새로운 노드와 연결해줘야하는거지.
void insert_after(Node *before_node, element data) {
    Node *node = create_node(data, before_node, before_node->next_node);
    before_node->next_node->prev_node = node;
    before_node->next_node = node;
}
// 처음에 아무것도 없고, insert_after(head,10)호출하는 경우는 head ⇆ A ⇆ head
// 이렇게 됨.

// 얘도 같은 논리로 after와 연결된 친구인 before부터 새로운 노드와
// 연결해줘야하는거야.
void insert_before(Node *after_node, element data) {
    Node *node = create_node(data, after_node->prev_node, after_node);
    after_node->prev_node->next_node = node;
    after_node->prev_node = node;
}

// node을 삭제하는거야. 센티널(head)과 삭제하려는노드를 줘
// head는 안전 삭제를 위한거야. 그 외 다른 의미는 없어.
bool remove_node(Node *head, Node *node) {
    if (node == head)
        return false; // head는 센티널노드야. 삭제되면 리스트 자체가 끝이야.
                      // 삭제 거부해.
    node->prev_node->next_node = node->next_node;
    node->next_node->prev_node = node->prev_node;
    free(node);
    return true;
}

// 얘는 안써도 되는거 print_list(list->head);
// 순환이라서 p->next != head 일때까지만
// 반복하면 그게 마지막까지 반복이야.
// 마지막 원소가 p->next != head 를 만족하는 마지막 놈이야.
// 그 다음은 첫번째 요소가 돼.
void print_list(Node *head) {
    if (head->prev_node == head && head->next_node == head) {
        printf("empty\n");
        return;
    }
    Node *p;
    printf("[head node]");
    for (p = head->next_node; p != head; p = p->next_node) {
        printf(" %d <->", p->data);
    }
    printf("\n");
}

Node *get_node(DLinkedListType *L, int pos) {
    if (pos < 0 || pos >= L->size)
        return NULL;

    Node *cur = L->head->next_node;
    for (int i = 0; i < pos; i++)
        cur = cur->next_node;
    return cur;
}

// 찾을때까지 다음으로 넘어가.
// 못찾았어? 못찾고 넘어갔더니 head까지 넘어갔으면 반복안해.
// 쉽게 말해 cur != L->head까지 반복해야 마지막까지 반복이야.
Node *find_node(DLinkedListType *L, element value) {
    Node *cur = L->head->next_node;
    while (cur != L->head && cur->data != value)
        cur = cur->next_node;
    return (cur == L->head) ? NULL : cur;
}

// cur != L->head 였으면 마지막요소까지 출력하고 cur은 head가 돼.
// cur->next != L->head해서 마지막요소 전까지 출력하고, cur은 마지막요소가 돼.
// 마지막 요소 전까지 순회 while(cur->next != L->head) cur=cur->next_node;
// 마지막 요소까지 순회 while(cur != L->head) cur = cur->next_node;
void print_dlist(DLinkedListType *L) {
    printf("DLinkedList(%d) [", L->size);
    if (L->size != 0) {
        Node *cur = L->head->next_node;

        while (cur->next_node != L->head) {
            printf("%d, ", cur->data);
            cur = cur->next_node;
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
    Node *cur = get_node(L, pos);
    if (cur != NULL) {
        insert_after(cur, value);
        L->size++;
    }
}
// 삭제는 안전삭제를 위해 인자로 head센티널을 준다고 했어.
// 그리고 삭제를 원하는 노드를 주면 된다고 했어. head의 next를 주면 front
// 삭제인거지.
void remove_front(DLinkedListType *L) {
    if (remove_node(L->head, L->head->next_node)) // 헤드랑 노드
        L->size--;
}
// head의 prev를 주면 last 삭제인거지.
void remove_last(DLinkedListType *L) {
    if (remove_node(L->head, L->head->prev_node))
        L->size--;
}

// pos로 찾고 그거 삭제하면 되겠지.
void remove_pos(DLinkedListType *L, int pos) {
    Node *cur = get_node(L, pos);
    if (cur && remove_node(L->head, cur))
        L->size--;
}

// 한바퀴 돌면 cur == L->head 된다.
void clear(DLinkedListType *L) {
    Node *cur = L->head->next_node; // head는 더미라서 head->next.
    Node *temp;
    while (cur != L->head) {
        temp = cur;
        cur = cur->next_node;
        free(temp);
    }
    L->head->next_node = L->head;
    L->head->prev_node = L->head;
    L->size = 0;
}

/* ------------------ main ------------------ */
int main(void) {
    DLinkedListType *list = create_list();
    puts("== 삽입(front) ==");
    for (int i = 0; i < 3; ++i) {
        insert_front(list, i);
        print_dlist(list);
    }

    puts("\n== 삽입(last) ==");
    for (int i = 10; i < 13; ++i) {
        insert_last(list, i);
        print_dlist(list);
    }

    puts("\n== 임의 위치 삽입(insert) ==");
    insert(list, 2, 99); /* 2번 인덱스 뒤에 99 */
    print_dlist(list);

    puts("\n== 직접 insert_after / insert_before 사용 ==");
    Node *first = get_node(list, 0);
    insert_after(first, -1);
    list->size++;
    insert_before(list->head, -2);
    list->size++;
    print_dlist(list);

    puts("\n== get_node / find_node ==");
    Node *n = get_node(list, 3);
    printf("get_node(3) → %d\n", n ? n->data : -1);
    n = find_node(list, 99);
    printf("find_node(99) → %p (%d)\n", (void *)n, n ? n->data : 0);

    puts("\n== 삭제(front / last / pos) ==");
    remove_front(list);
    print_dlist(list);
    remove_last(list);
    print_dlist(list);
    remove_pos(list, 1);
    print_dlist(list);

    puts("\n== 직접 remove_node 사용 ==");
    n = find_node(list, 10);
    if (n && remove_node(list->head, n)) {
        list->size--;
    }
    print_dlist(list);

    puts("\n== print_list (순회 확인용, head 기준) ==");
    print_list(list->head);

    puts("\n== clear ==");
    clear(list);
    print_dlist(list);

    /* 정리 */
    free(list->head);
    free(list);
    return 0;
}
