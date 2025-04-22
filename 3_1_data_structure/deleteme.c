#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct {
    element data;
    struct DListNode *prev;
    struct DListNode *next;
} DListNode;

typedef struct {
    DListNode *head;
    int size;
} DLinkedListType;

DListNode *create_node()