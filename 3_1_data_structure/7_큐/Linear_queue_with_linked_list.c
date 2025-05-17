#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef int element; // 요소의타입
typedef struct {     // 큐의노드의타입
    element data;
    struct QueueNode *next_node;
} QueueNode;
typedef struct { // 큐 전체의정보를저장하는타입
    QueueNode *front;
    QueueNode *rear;
} LinkedQueueType;

// 큐초기화
LinkedQueueType *create_queue() {
    LinkedQueueType *q = (LinkedQueueType *)malloc(sizeof(LinkedQueueType));
    q->front = NULL;
    q->rear = NULL;
    return q;
}
// 큐 완전 제거
// 프론트 손가락 가르키는거 free하고, 손가락 다음으로 옮기는거야
// 근데 손가락을 지워버리잖아. 그럼 안되지 그래서 다른 손가락을 추가하는거.
void free_queue(LinkedQueueType *q) {
    QueueNode *temp = NULL;
    QueueNode *cur = q->front;
    while (cur != NULL) {
        temp = cur;           // temp로 똑같이 가르키네?
        cur = cur->next_node; // 다음으로 이동하네?
        free(temp);           // temp를 이용해서 free
    }
    free(q);
}

// 오류함수
void error(const char *message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}
// 비었는지확인
bool is_empty(LinkedQueueType *q) {
    return (q->front == NULL);
}
void print_queue(LinkedQueueType *q) {
    printf("Queue: ");
    for (QueueNode *p = q->front; p != NULL; p = p->next_node) {
        printf(" %d | ", p->data);
    }
    printf("\n");
}
// 삽입함수(리스트맨뒤에추가)
void enqueue(LinkedQueueType *q, element data) {
    QueueNode *temp = (QueueNode *)malloc(sizeof(QueueNode));
    temp->data = data;      // 데이터저장
    temp->next_node = NULL; // 링크필드를NULL
    if (is_empty(q)) {      // 큐가공백이면
        q->front = temp;
        q->rear = temp;
    } else {                       // 큐가공백이아니면
        q->rear->next_node = temp; // 먼저 새로운 놈과 기존 놈을 연결해야지
        q->rear = temp;            // 연결하고 나서 손가락을 옮겨야지.
    }
}
// 이 순서가 중요해 손가락부터 옮기면 어떻게 될까?
// 손가락부터 옮겼다고 하자.
// 그러면 우리는 다음에 할 일이 머냐.
// 기존 놈이 새로운 놈을 가르키게 해야지?
// 근데 기존 놈을 가르키던 rear 손가락이 없어졌어.
// 어라라? 기존 놈에 접근을 못하네?(물론 front쓰면 접근가능 but
// 비효율적이지) 그래! 그러면 두 놈을 연결시키고 손가락을 옮기면
// 되는거지!

// 삭제 함수
// 흠 어케하지. front를 제거&&리턴하는거자나.
// 꺼내! 그리고 손가락 옮겨줘. 그럼 끝이야.
// 큐가 비었으면 rear도 NULL로 업데이트 해주면 되는거야.
element dequeue(LinkedQueueType *q) {
    // QueueNode *temp = q->front;
    if (is_empty(q)) { // 공백상태
        error("Queue is Empty.");
    }
    // data = temp->data;
    element data = q->front->data;  // 데이터를 꺼낸다.
    q->front = q->front->next_node; // front의 다음 노드

    if (q->front == NULL) // 큐가 비었다면
        q->rear = NULL;   // 다른데 가르키던 rear도 초기화 해줘야지.
    // free(temp);
    return data; // 데이터 반환
}

int main() {
    LinkedQueueType *q = create_queue();
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
    free_queue(q);
    return 0;
}