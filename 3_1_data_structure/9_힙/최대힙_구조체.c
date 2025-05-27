/* max_heap_struct.c */
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 200 /* 최대 원소 수(1-베이스: data[1]이 루트) */

/* (1) 자료형 선언 */
typedef struct {
    int key;
} element;

typedef struct {
    element data[MAX_SIZE]; /* data[0] 는 사용 안 함 */
    int heap_size;
} Heap;

/* (2) 힙 생성 */
Heap *create_heap(void) {
    Heap *h = (Heap *)malloc(sizeof(Heap));
    h->heap_size = 0;
    return h;
}

/* (3) 현재 힙 내용 출력(디버그용) */
void print_heap(const Heap *h) {
    printf("Heap(size=%d): ", h->heap_size);
    for (int i = 1; i <= h->heap_size; ++i)
        printf("%d ", h->data[i].key);
    puts("");
}

/* (4) 삽입 – up-heap */
void push_max_heap(Heap *h, element item) {
    if (h->heap_size >= MAX_SIZE - 1) { /* +1 해도 넘치면 에러 */
        fprintf(stderr, "Heap overflow!\n");
        return;
    }
    int cur =
        ++h->heap_size;   // (1) 마지막 칸에 '구멍' 하나 만듦, 현재 인덱스임.
    int parent = cur / 2; // (2) 그 구멍의 부모 인덱스

    while (parent >= 1 &&
           item.key > h->data[parent].key) { // 이미 루트까지 올라옴
                                             // 부모가 더 크거나 같아야함(힙
                                             // 조건 만족). 그렇지 않으면 반복
        h->data[cur] = h->data[parent];      // (3) 부모 값을 아래로 복사
        cur = parent;     // (4) 현재인덱스가 부모 자리로 이동
        parent = cur / 2; // (5) 새 부모 계산
    }
    h->data[cur] = item; // (6) 구멍이 멈춘 곳에 새 원소 삽입
}

/* (5) 삭제 – down-heap (최댓값 반환) */
element pop_max_heap(Heap *h) {
    element error = {-1};
    if (h->heap_size < 1)
        return error;

    element ret = h->data[1];               /* 루트 값 */
    element last = h->data[h->heap_size--]; /* 배열 끝 값 */

    int cur = 1,
        left = cur * 2; //// ⑥ 현재 '구멍' 위치 = 루트 // ⑦ 그 왼쪽 자식 인덱스
    while (left <= h->heap_size) {      // ⑧ 자식이 하나라도 존재?
        int child = left;               // ⑨ 기본은 왼쪽
        if (left + 1 <= h->heap_size && // ⑩ 오른쪽도 존재하고
            h->data[left].key < h->data[left + 1].key)
            child = left + 1; // ⑪ 오른쪽이 더 크면 교체

        if (last.key >= h->data[child].key) // ⑫ 이미 제자리?
            break;                          // ⑬ 루프 탈출

        h->data[cur] = h->data[child]; /* 큰 자식을 끌어올림 */
        cur = child;
        left = cur * 2;
    }
    h->data[cur] = last; /* 빈 칸에 last 삽입 */
    return ret;
}

/* (6) 데모 */
int main(void) {
    element input[] = {{10}, {5}, {4}, {3}, {2}, {1}, {30}, {7}, {2}, {6}};
    const int N = sizeof(input) / sizeof(input[0]);

    Heap *heap = create_heap();

    puts("== 삽입 과정 ==");
    for (int i = 0; i < N; ++i) {
        push_max_heap(heap, input[i]);
        print_heap(heap);
    }

    puts("\n== 삭제 과정 ==");
    for (int i = 0; i < N; ++i) {
        element e = pop_max_heap(heap);
        printf("deleted: %d\n", e.key);
        print_heap(heap);
    }

    element e = pop_max_heap(heap); /* 빈 힙 pop 테스트 */
    printf("deleted(empty): %d\n", e.key);

    free(heap);
    return 0;
}
