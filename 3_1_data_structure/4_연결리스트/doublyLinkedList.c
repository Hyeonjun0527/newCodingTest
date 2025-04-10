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

DListNode *create_node(element value, DListNode *before, DListNode *after) {
    DListNode *node = (DListNode *)malloc(sizeof(DListNode));
    node->data = value;
    node->prev = before;
    node->next = after;
    return node;
}

DListNode *init() {
    DListNode *head = create_node(0, NULL, NULL);
    head->prev = head;
    head->next = head;
    return head;
}

void insert_after(DListNode *before, element data) {
    DListNode *node = create_node(data, before, before->next);
    before->next->prev = node;
    before->next = node;
}

void insert_before(DListNode *after, element data) {
    DListNode *node = create_node(data, after->prev, after);
    after->prev->next = node;
    after->prev = node;
}

bool remove_node(DListNode *head, DListNode *cur) {
    if (cur == head)
        return false;
    cur->prev->next = cur->next;
    cur->next->prev = cur->prev;
    free(cur);
    return true;
}

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

DLinkedListType *create_list() {
    DListNode *head = create_node(0, NULL, NULL);
    head->prev = head;
    head->next = head;

    DLinkedListType *list = (DLinkedListType *)malloc(sizeof(DLinkedListType));
    list->head = head;
    list->size = 0;
    return list;
}

DListNode *get_node(DLinkedListType *L, int pos) {
    if (pos < 0 || pos >= L->size)
        return NULL;

    DListNode *cur = L->head->next;
    for (int i = 0; i < pos; i++)
        cur = cur->next;
    return cur;
}

DListNode *find_node(DLinkedListType *L, element value) {
    DListNode *cur = L->head->next;
    while (cur != L->head && cur->data != value)
        cur = cur->next;
    return (cur == L->head) ? NULL : cur;
}

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

void insert_front(DLinkedListType *L, element value) {
    insert_after(L->head, value);
    L->size++;
}

void insert_last(DLinkedListType *L, element value) {
    insert_before(L->head, value);
    L->size++;
}

void insert(DLinkedListType *L, int pos, element value) {
    DListNode *cur = get_node(L, pos);
    if (cur != NULL) {
        insert_after(cur, value);
        L->size++;
    }
}

void remove_front(DLinkedListType *L) {
    if (remove_node(L->head, L->head->next))
        L->size--;
}

void remove_last(DLinkedListType *L) {
    if (remove_node(L->head, L->head->prev))
        L->size--;
}

void remove_pos(DLinkedListType *L, int pos) {
    DListNode *cur = get_node(L, pos);
    if (cur && remove_node(L->head, cur))
        L->size--;
}

void clear(DLinkedListType *L) {
    DListNode *cur = L->head->next;
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
