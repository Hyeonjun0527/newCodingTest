#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_LITS_SIZE 1000
typedef int element; // 항목의 정의
typedef struct {     // 리스트 노드 정의
    element data;
    struct ListNode *next_node;
} ListNode;

typedef struct {
    ListNode *head; // 리스트 헤드 포인터
    int size;       // 현재 리스트에 저장된 항목들의 개수
} CircularListType;

// 리스트 초기화 함수
/*
삽입·삭제 시 “처음 노드인지?”만 따지면 된다. 그래서 head == null로 충분.
*/

// 신규 노드 생성
ListNode *create_node(element value, ListNode *next_node) {
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));
    p->data = value;
    p->next_node = next_node;
    return p;
}

CircularListType *create_list() {
    CircularListType *list =
        (CircularListType *)malloc(sizeof(CircularListType));
    list->head = NULL;
    list->size = 0;
    return list;
}

// 전체메모리해제
void clear(CircularListType *L) {
    ListNode *cur = L->head;
    ListNode *temp;
    while (cur != NULL) {
        temp = cur;
        cur = cur->next_node;
        free(temp);
    }
    L->head = NULL;
    L->size = 0;
}

// 리스트 출력(데이터가 없는 경우에도 잘 출력되도록 구현)
void print_list(CircularListType *L) {
    printf("CircularList(%d) [", L->size);
    if (L->head != NULL) {
        ListNode *cur = L->head->next_node;
        while (cur != L->head) {
            printf("%d, ", cur->data);
            cur = cur->next_node;
        }
        printf("%d", cur->data);
    }
    printf("]\n");
}
// 리스트가비어있으면true를반환, 그렇지않으면false를반환
bool is_empty(CircularListType *L) {
    return L->size == 0;
}
// 리스트가가득차있으면true를반환, 그렇지않으면false를반환
bool is_full(CircularListType *L) {
    return L->size == MAX_LIST_SIZE;
}
// 현재리스트의아이템개수를반환
bool get_length(CircularListType *L) {
    return L->size;
}

// 오류처리함수
void error(const char *message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}
// 리스트의특정위치의값을반환
element get_entry(CircularListType *L, int pos) {
    if (pos < 0 || pos >= L->size)
        error("Wrong position");
    // pos위치까지이동
    ListNode *cur = L->head->next_node;
    for (int i = 0; i < pos; i++)
        cur = cur->next_node;
    return cur->data;
}

void insert_front(CircularListType *L, element value) {
    if (L->head == NULL) {
        L->head = create_node(value, NULL);
        L->head->next_node = L->head; // 순환링크생성
    } else {
        /*
        L->head->next를 next로 가지고 있는 노드를 만들어.
        그 노드를, L->head의 next로 넣어줘?
        */
        L->head->next_node = create_node(value, L->head->next_node);
    }
    L->size++; // 리스트크기증가
}
void insert_last(CircularListType *L, element value) {
    if (L->head == NULL) {
        L->head = create_node(value, NULL);
        L->head->next_node = L->head; // 순환링크생성
    } else {
        L->head->next_node = create_node(value, L->head->next_node);
        // 순환링크에맞게마지막항목을head로설정
        L->head = L->head->next_node;
    }
    L->size++; // 리스트크기증가
}

// 노드 prev_node 뒤에 새로운 노드 삽입
void insert(CircularListType *L, int pos, element value) {
    if (pos < 0 || pos >= L->size) { // 위치값 오류 확인
        printf("Wrong position\n");
        return;
    }
    // 맨 앞에 삽입하는 경우 (헤드 변경 필요)
    if (pos == 0) {
        // 처음에 추가하는 경우
        insert_front(L, value);
    } else if {
        (pos == L->size - 1)
            // 끝에 추가하는 경우
            insert_last(L, value)
    }; else {                          // 중간에 삽입하는 경우
        ListNode *prev_node = L->head; // prev_node 위치검색
        for (int i = 0; i < pos; i++)
            prev_node = prev_node->next_node;
        prev_node->next_node = create_node(value, prev_node->next_node);
        L->size++; // 리스트 크기 증가
    }
}

// 맨앞의노드를삭제
void remove_front(CircularListType *L) {
    if (L->head == NULL)
        return;
    if (L->size == 1) {
        free(L->head);
        L->head = NULL;
    } else {
        ListNode *remove = L->head->next_node;
        L->head->next_node = remove->next_node;
        free(remove);
    }
    L->size--; // 리스트크기감소
}
// 맨뒤의노드를삭제
void remove_last(CircularListType *L) {
    if (L->head == NULL)
        return;
    if (L->size == 1) {
        free(L->head);
        L->head = NULL;
    } else {
        ListNode *remove = L->head;
        // 헤드이전노드탐색
        ListNode *prev_node = remove->next_node;
        while (prev_node->next_node != L->head)
            prev_node = prev_node->next_node;
        // 노드삭제및링크정리
        prev_node->next_node = remove->next_node; // 노드링크변경
        L->head = prev_node;            // 헤드포인트변경
        free(remove);
    }
    L->size--; // 리스트크기감소
}
// pos위치의노드를삭제
void remove(CircularListType *L, int pos) {
    // 위치값오류확인
    if (pos < 0 || pos >= L->size) {
        return;
    }
    if (pos == 0) { // 맨앞을삭제하는경우
        remove_front(L);
    } else {
        // 삭제직전노드찾기
        ListNode *prev_node = L->head;
        for (int i = 0; i < pos; i++)
            prev_node = prev_node->next_node;
        // 노드삭제
        ListNode *remove = prev_node->next_node; // 삭제대상
        prev_node->next_node = remove->next_node;
        if (remove == L->head)
            L->head = prev_node;
        L->size--;    // 리스트크기감소
        free(remove); // 노드삭제
    }
}

int main() {
    CircularListType *list = create_list();
    for (int i = 0; i < 5; i++) {
        insert_last(list, i);
        print_list(list);
    }
    ListNode *cur = list->head->next_node;
    for (int i = 0; i < 10; i++) {
        printf("현재차례=%d \n", cur->data);
        cur = cur->next_node;
    }
    return 0;
}