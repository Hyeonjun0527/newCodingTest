#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 100
typedef int element;
typedef struct { // 큐타입
    int front;
    int rear;
    element data[MAX_QUEUE_SIZE];
} QueueType;

// 오류함수
void error(const char *message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}

QueueType *create_queue() {
    QueueType *q = (QueueType *)calloc(1, sizeof(QueueType));
    q->front = -1;
    q->rear = -1;
    return q;
}
void free_queue(QueueType *q) {
    free(q);
}

bool is_full(QueueType *q) {
    if (q->rear == MAX_QUEUE_SIZE - 1)
        return true;
    else
        return false;
}
bool is_empty(QueueType *q) {
    if (q->front == q->rear)
        return true;
    else
        return false;
}

/* 0~MAX_QUEUE_SIZE-1 전체를 시각화 */
// void print_queue(const QueueType *q) {
//     puts("─────── array slots ───────");
//     /* 데이터 줄 */
//     for (int i = 0; i < 10; ++i) {
//         if (i <= q->front || i > q->rear)
//             printf("   ·   "); // 빈 칸 표시(·)
//         else
//             printf("%5d ", q->data[i]); // 채워진 값
//     }
//     putchar('\n');

//     /* 인덱스 줄 (0 ~ 9만 찍고 싶으면 i%10) */
//     for (int i = 0; i < 10; ++i)
//         printf("%5d ", i);
//     putchar('\n');

//     /* 포인터 줄 (front, rear) */
//     for (int i = 0; i < MAX_QUEUE_SIZE; ++i) {
//         if (i == q->front + 1 && !is_empty((QueueType *)q))
//             printf("  F↑  "); // front + 1 = 실제 첫 요소
//         else if (i == q->rear)
//             printf("  R↑  "); // rear
//         else
//             printf("      ");
//     }
//     puts("\n──────────────────────────");
// }

void print_queue(QueueType *q) {
    if (is_empty(q)) {
        printf("비었음\n");
        return;
    }
    for (int i = q->front + 1; i <= q->rear; i++)
        printf("%d ", q->data[i]);
    printf("\n");
}

element peek(QueueType *q) {
    if (is_empty(q)) {
        error("비었음");
        return -1;
    }
    return q->data[q->front + 1];
}
void enqueue(QueueType *q, element item) {
    if (is_full(q)) {
        error("Queue is Full.");
        return;
    }
    q->data[++(q->rear)] = item;
}
element dequeue(QueueType *q) {
    if (is_empty(q)) {
        error("Queue is Empty.");
        return -1;
    }
    element item = q->data[++(q->front)];
    return item;
}
int main() {
    QueueType *q = create_queue();
    enqueue(q, 10);
    print_queue(q);
    enqueue(q, 20);
    print_queue(q);
    enqueue(q, 30);
    print_queue(q);
    dequeue(q);
    print_queue(q);
    dequeue(q);
    print_queue(q);
    dequeue(q);
    print_queue(q);
    enqueue(q, 10);
    print_queue(q);
    free_queue(q);
    return 0;
}