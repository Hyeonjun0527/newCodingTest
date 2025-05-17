#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#define MAX_QUEUE_SIZE 5

typedef struct { // 요소 타입
    int id;             // 고객번호
    int arrival_time;   // 도착시간
    int service_time;   // 서비스에 필요한 시간
    int waiting_time;   //서비스 시작까지 대기시간
} element;

typedef struct { // 큐 타입
    element  data[MAX_QUEUE_SIZE];
    int  front, rear;
} QueueType;


// 오류 함수
void error(const char* message){
    fprintf(stderr, "%s\n", message);
    // exit(1);
}

// 큐 자료구조 생성
QueueType* create_queue(){
    QueueType* q = (QueueType*)malloc(sizeof(QueueType));
    q->front = q->rear = 0;
    return q;
}

// 큐 자료구조 제거
void free_queue(QueueType* q){
    free(q);
}

// 공백 상태 검출 함수
int is_empty(QueueType* q){
    return (q->front == q->rear);
}

// 포화 상태 검출 함수
int is_full(QueueType* q){
    return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front % MAX_QUEUE_SIZE);
}

// 원형큐 출력 함수
void print_queue(QueueType* q){
    printf("    >> QUEUE: ");
    if (!is_empty(q)) {
        int i = q->front;
        do {
            i = (i + 1) % (MAX_QUEUE_SIZE);
            printf("%d (%d), ", q->data[i].id, q->data[i].service_time);
            if (i == q->rear)
                break;
        } while (i != q->front);
    }
    printf("\n");
}

// 삽입 함수
void enqueue(QueueType* q, element item){
    if (is_full(q))
        error("Queue is Full.");

    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}

// 삭제 함수
element dequeue(QueueType* q){
    if (is_empty(q))
        error("Queue is Empty.");

    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}

element peek_front(QueueType* q) {
    if (is_empty(q))
        error("Queue is Empty.");

    return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}

element peek_rear(QueueType* q) {
    if (is_empty(q))
        error("Queue is Empty.");

    return q->data[q->rear];
}


///////////////
///////////////
///////////////
int TOTAL_CUSTOMERS = 0;
int ARRIVAL_PROBABILITY = 30;   // 30%
int TOTAL_WAIT = 0;            // 누적 대기시간간

bool is_customer_arrived(){
    // rand(): return [0, RAND_MAX=32767] in random
    // 확률로 고객 입장
    if ((rand() % 100) > ARRIVAL_PROBABILITY) 
        return false;
    return true;
}

element get_customer(int clock){
    // 고객정보생성 (업무 처리에 필요한 시간은 랜덤으로 할당)
    element customer; 
    customer.id = TOTAL_CUSTOMERS++;
    customer.arrival_time = clock;
    customer.service_time = rand() % 3 + 1; // return [1, 3]
    return customer;
}


int main() {
    int minutes = 10;


    element in_service = {-1, 0, 0, 0};      // 은행원의 서비스 대상
    QueueType* queue = create_queue();

    srand(time(NULL)); //랜덤 값을 고정하고 싶으면 time(NULL) 대신 숫자 시드

    for (int clock = 0; clock < minutes; clock++) {
        printf("[%dm] \n", clock); 
        // 고객의 도착 이벤트 처리
        if (is_customer_arrived()==true){
            element customer = get_customer(clock);
            enqueue(queue, customer);
            printf("[%dm] Entered a Customer (ID: %d, Required service time: %dm)\n", 
                customer.arrival_time, customer.id, customer.service_time);
            print_queue(queue);
        }

        // 은행원의 업무 처리
        if (in_service.id == -1 && !is_empty(queue)) {
            in_service = dequeue(queue);
            in_service.waiting_time = clock - in_service.arrival_time;
            printf("[%dm] Service is started for Customer %d (waited_time: %d)\n", 
                clock, in_service.id, in_service.waiting_time);
            print_queue(queue);
            TOTAL_WAIT += in_service.waiting_time;
        }

        if (in_service.id != -1) {
            in_service.service_time--;
            printf("[%dm] In service for Customer %d (remaining: %dm)\n", clock, in_service.id, in_service.service_time);
            if (in_service.service_time == 0){
                printf("[%dm]    Service for Customer %d is finished\n", clock, in_service.id);
                in_service.id = -1;
            }
        }
    }
    printf("\nTotal Waiting Time = %dm \n", TOTAL_WAIT);
    return 0;
}
