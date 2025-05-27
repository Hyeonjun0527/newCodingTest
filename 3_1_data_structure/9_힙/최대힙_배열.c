/* max_heap_plain.c : 구조체 없이 전역 배열로만 구현한 최대 힙 */
#include <stdio.h>

#define MAX_SIZE 200 /* data[1]이 루트(1-base) */

int A[MAX_SIZE];   /* 힙 배열 */
int heap_size = 0; /* 현재 원소 수 */

/* ---------- 유틸리티 ---------- */
void print_heap(void) {
    printf("Heap(size=%d): ", heap_size);
    for (int i = 1; i <= heap_size; ++i)
        printf("%d ", A[i]);
    puts("");
}

/* ---------- 삽입 (up-heap) ---------- */
void push_max_heap(int key) {
    if (heap_size >= MAX_SIZE - 1) {
        fprintf(stderr, "Heap overflow!\n");
        return;
    }

    int cur = ++heap_size; /* 마지막 칸 구멍 */
    int parent = cur / 2;

    while (parent >= 1 && key > A[parent]) {
        A[cur] = A[parent]; /* 부모 ↓ */
        cur = parent;       /* 구멍 ↑ */
        parent = cur / 2;
    }
    A[cur] = key; /* 자리 확정 */
}

/* ---------- 삭제 (down-heap) ---------- */
int pop_max_heap(void) {
    if (heap_size < 1)
        return -1; /* sentinel */

    int ret = A[1];            /* 루트 저장 */
    int last = A[heap_size--]; /* 끝 값 */

    int cur = 1, left = cur * 2;
    while (left <= heap_size) {
        int child = left;
        if (left + 1 <= heap_size && A[left] < A[left + 1])
            child = left + 1; /* 더 큰 자식 */

        if (last >= A[child])
            break; /* 자리 찾음 */

        A[cur] = A[child]; /* 큰 자식을 끌어올림 */
        cur = child;
        left = cur * 2;
    }
    A[cur] = last; /* 빈 칸에 last */
    return ret;
}

/* ---------- 데모 ---------- */
int main(void) {
    int input[] = {10, 5, 4, 3, 2, 1, 30, 7, 2, 6};
    const int N = sizeof(input) / sizeof(input[0]);

    puts("== 삽입 과정 ==");
    for (int i = 0; i < N; ++i) {
        push_max_heap(input[i]);
        print_heap();
    }

    puts("\n== 삭제 과정 ==");
    for (int i = 0; i < N; ++i) {
        int del = pop_max_heap();
        printf("deleted: %d\n", del);
        print_heap();
    }

    int del = pop_max_heap(); /* 빈 힙 pop 테스트 */
    printf("deleted(empty): %d\n", del);
    return 0;
}
