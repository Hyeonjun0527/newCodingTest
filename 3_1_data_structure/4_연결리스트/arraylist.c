#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_LIST_SIZE 100 // 리스트의최대크기
typedef int element;      // 항목의정의
typedef struct {
    element array[MAX_LIST_SIZE]; // 배열정의
    int size;                     // 현재리스트에저장된항목들의개수
} ArrayListType;
// 왜 element 만들었는지 설명.

// 리스트초기화함수
ArrayListType create_list() {
    ArrayListType list;
    list.size = 0;
    return list;
}
// 리스트출력(데이터가없는경우에도잘출력되도록구현)
void print_list(ArrayListType *L) {
    printf("ArrayList(");
    for (int i = 0; i < L->size - 1; i++)
        printf("%d, ", L->array[i]);
    if (L->size > 0)
        printf("%d", L->array[L->size - 1]);
    printf(")\n");
}

// 리스트가비어있으면true를반환, 그렇지않으면false를반환
bool is_empty(ArrayListType *L) {
    return L->size == 0;
}
// 리스트가가득차있으면true를반환, 그렇지않으면false를반환
bool is_full(ArrayListType *L) {
    return L->size == MAX_LIST_SIZE;
}
// 현재리스트의아이템개수를반환
bool get_length(ArrayListType *L) {
    return L->size;
}

// 오류처리함수
void error(const char *message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}
// 리스트의특정위치의값을반환
element get_entry(ArrayListType *L, int pos) {
    if (pos < 0 || pos >= L->size)
        error("Wrong position");
    return L->array[pos];
}
// 리스트모든정보삭제(실제로는크기만0으로만듦)
void clear(ArrayListType *L) {
    L->size = 0;
}
// 맨 끝에 item을 삽입
void insert_last(ArrayListType *L, element item) {
    if (L->size >= MAX_LIST_SIZE) {
        error("리스트 오버플로우");
    }
    L->array[L->size++] = item;
}

// pos 위치에아이템을삽입
void insert(ArrayListType *L, int pos, element item) {
    if (!is_full(L) || (pos < 0) || (pos > L->size))
        error("error: ");
    // pos위치부터그 뒤에있는아이템들은한칸씩앞으로이동(뒤에서부터)
    for (int I = (L->size - 1); I >= pos; I--)
        L->array[I + 1] = L->array[I];
    // 아이템삽입
    L->array[pos] = item;
    L->size++;
}

// list의 처음에 아이템을 추가
void insert_front(ArrayListType *L, element item) {
    // 기존 코드 재사용
    insert(L, 0, item);
}
// pos위치에있는아이템을삭제
element remove(ArrayListType *L, int pos) {
    element item;
    if (pos < 0 || pos >= L->size)
        error("위치오류");
    // 삭제할항목복사
    item = L->array[pos];
    // pos위치뒤부터끝까지한칸씩뒤로이동(앞에서부터)
    for (int i = pos; i < (L->size - 1); i++)
        L->array[i] = L->array[i + 1];
    L->size--;
    return item;
}
// pos위치에있는아이템을삭제
int find(ArrayListType *L, element item) {
    int loc = -1;
    // if (is_empty(L)) return loc; // 필요없음
    // 전체목록탐색
    for (int i = 0; i < L->size; i++) {
        if (L->array[i] != item)
            continue;
        loc = i;
        break;
    }
    return loc;
}
int main() {
    ArrayListType list = create_list();
    insert(&list, 0, 10); // 0번째위치에10 추가
    print_list(&list);
    insert(&list, 0, 20); // 0번째위치에20 추가
    print_list(&list);
    insert_frot(&list, 30); // 맨앞에30 추가
    print_list(&list);
    insert_last(&list, 40); // 맨끝에40 추가
    print_list(&list);
    remove(&list, 0); // 0번째항목삭제
    print_list(&list);
    printf("30 islocated at %d\n", find(&list, 20));
    return 0;
}