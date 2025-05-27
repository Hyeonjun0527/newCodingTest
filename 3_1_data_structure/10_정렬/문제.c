/* --------------- 헤더 파일 --------------- */
#include <stdio.h>  // 표준 입·출력 함수들(printf, scanf)을 쓰기 위해 포함
#include <stdlib.h> // 동적 메모리 할당 함수(malloc, free)를 쓰기 위해 포함

/* --------------- 자료형 정의 --------------- */
typedef struct {
    int x; // 점의 x 좌표
    int y; // 점의 y 좌표
} Point;   // 이제 Point 라는 새 자료형 이름으로 사용 가능

/* --------------- 비교(순서 판정) 함수 --------------- */
/* 두 점 a, b 중 a가 b보다 앞(작다)이면 1, 아니면 0을 반환 */
static inline int is_less(Point a, Point b) {
    /* 1) x 좌표가 더 작으면 true
       2) x 좌표가 같을 때는 y 좌표가 더 작으면 true */
    return (a.x < b.x) || (a.x == b.x && a.y < b.y);
}

/* --------------- swap(교환) 매크로 --------------- */
/* A와 B(모두 Point형)의 값을 tmp에 잠시 저장했다가 서로 맞바꾼다. */
#define SWAP(A, B)                                                             \
    do {                                                                       \
        Point tmp = (A);                                                       \
        (A) = (B);                                                             \
        (B) = tmp;                                                             \
    } while (0)

/* --------------- Hoare 파티션 함수 --------------- */
/* 배열 arr의 구간 [left, right]를 피벗 기준으로 둘로 나눈 뒤
   왼쪽 파티션의 끝 인덱스(== pivot의 최종 위치)를 반환한다. */
int partition(Point arr[], int left, int right) {
    Point pivot = arr[left]; // ① 맨 왼쪽 원소를 피벗으로 선택
    int low = left - 1;      // ② low는 구간 바깥(left-1)부터 출발
    int high = right + 1;    // ③ high는 구간 바깥(right+1)부터 출발

    while (1) { // 무한 루프 → 내부에서 break로 탈출
        /* ④ pivot 이상(>=)인 원소를 만날 때까지 low를 오른쪽으로 이동 */
        do {
            low++;
        } while (is_less(arr[low], pivot));

        /* ⑤ pivot 이하(<=)인 원소를 만날 때까지 high를 왼쪽으로 이동 */
        do {
            high--;
        } while (is_less(pivot, arr[high]));

        if (low >= high) // ⑥ 엇갈렸으면 파티션 완료 → high 반환
            return high;

        /* ⑦ 아직 안 엇갈렸으면 low, high 위치의 원소를 교환 */
        SWAP(arr[low], arr[high]);
    }
}

/* --------------- 재귀 퀵 정렬 함수 --------------- */
/* 배열 arr의 구간 [left, right]를 제자리(in-place) 정렬 */
void quick_sort(Point arr[], int left, int right) {
    if (left < right) {                      // 구간에 원소가 2개 이상일 때만
        int p = partition(arr, left, right); // ① 파티션 → p는 왼쪽 구간 끝
        quick_sort(arr, left, p);            // ② 왼쪽 파티션 재귀 정렬
        quick_sort(arr, p + 1, right);       // ③ 오른쪽 파티션 재귀 정렬
    }
}

/* --------------- main 함수(프로그램 진입점) --------------- */
int main(void) {
    int N;                    // 정렬할 점의 개수
    if (scanf("%d", &N) != 1) // ① 개수 입력, 실패 시 프로그램 종료
        return 0;

    /* ② N개 Point 저장할 동적 배열 할당 (N ≤ 100,000 이라 0.8MB 정도) */
    Point *pts = (Point *)malloc(sizeof(Point) * N);
    if (!pts) // 메모리 할당 실패 체크
        return 0;

    /* ③ N개의 (x, y) 좌표 입력 */
    for (int i = 0; i < N; ++i)
        scanf("%d %d", &pts[i].x, &pts[i].y);

    /* ④ 퀵 정렬 호출: 배열 전체([0, N-1])를 정렬 */
    quick_sort(pts, 0, N - 1);

    /* ⑤ 결과 출력: 정렬된 순서대로 한 줄에 하나씩 */
    for (int i = 0; i < N; ++i)
        printf("%d %d\n", pts[i].x, pts[i].y);

    free(pts); // ⑥ 동적 메모리 해제
    return 0;  // ⑦ 프로그램 정상 종료
}
