#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **data;  // 동적 할당된 문자열 배열
    int front;    // 읽을 인덱스
    int rear;     // one‐past‐the‐last 인덱스
    int capacity; // data 배열의 크기
} Queue;

// 큐 초기화: capacity 만큼의 슬롯을 할당
void initQueue(Queue *q, int capacity) {
    q->data = malloc(capacity * sizeof(char *));
    q->front = 0;
    q->rear = 0;
    q->capacity = capacity;
}

// 큐가 비어 있으면 1, 아니면 0
int isEmpty(const Queue *q) {
    return q->front >= q->rear;
}

// 큐에 word를 enqueue (rear 위치에 복사)
void enqueue(Queue *q, const char *word) {
    if (q->rear < q->capacity) {
        q->data[q->rear++] = strdup(word);
    }
}

// 큐 맨 앞을 peek (비어 있으면 NULL)
const char *peek(const Queue *q) {
    if (isEmpty(q))
        return NULL;
    return q->data[q->front];
}

// 큐에서 front를 dequeue하여 out에 복사, 성공(1)/실패(0)
int dequeue(Queue *q, char *out) {
    if (isEmpty(q))
        return 0;
    strcpy(out, q->data[q->front]);
    free(q->data[q->front]);
    q->front++;
    return 1;
}

int main() {
    int T;
    if (scanf("%d", &T) != 1)
        return 0;

    while (T--) {
        int N, M;
        scanf("%d %d", &N, &M);

        // 1) 동적 이중포인터로 target 단어 배열 할당
        char **target = malloc(M * sizeof(char *));
        char buf[101];
        for (int i = 0; i < M; i++) {
            scanf("%100s", buf);
            target[i] = strdup(buf);
        }

        // 2) 동적 큐 배열 할당 및 초기화
        Queue *qlist = malloc(N * sizeof(Queue));
        for (int i = 0; i < N; i++) {
            int K;
            scanf("%d", &K);
            initQueue(&qlist[i], K);
            for (int j = 0; j < K; j++) {
                scanf("%100s", buf);
                enqueue(&qlist[i], buf);
            }
        }

        // 3) 그리디 매칭
        int ok = 1;
        for (int i = 0; i < M && ok; i++) {
            int found = 0;
            for (int j = 0; j < N; j++) {
                const char *f = peek(&qlist[j]);
                if (f && strcmp(f, target[i]) == 0) {
                    char dummy[101];
                    dequeue(&qlist[j], dummy);
                    found = 1;
                    break;
                }
            }
            if (!found)
                ok = 0;
        }

        printf("%d\n", ok);

        // --- 메모리 해제 ---
        // target 해제
        for (int i = 0; i < M; i++)
            free(target[i]);
        free(target);

        // 큐별 남은 요소 해제 + data 배열 해제
        for (int i = 0; i < N; i++) {
            Queue *q = &qlist[i];
            while (!isEmpty(q)) {
                free(q->data[q->front]);
                q->front++;
            }
            free(q->data);
        }
        free(qlist);
    }

    return 0;
}
