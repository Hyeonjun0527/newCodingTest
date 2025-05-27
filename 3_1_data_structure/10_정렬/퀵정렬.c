#include <stdio.h>

/* ---------- 유틸리티 ---------- */
#define SWAP(a, b)                                                             \
    do {                                                                       \
        int t = (a);                                                           \
        (a) = (b);                                                             \
        (b) = t;                                                               \
    } while (0)

/* ---------- 파티션 (Hoare) ---------- */
/* list[left]를 피벗으로 삼아:
   pivot보다 작은 값은 왼쪽, 큰 값은 오른쪽으로 분할
   pivot의 새 위치(인덱스) 반환                                  */
int partition(int list[], int left, int right) {
    int pivot = list[left]; /* 피벗 */
    int low = left - 1;     /* 배열 밖에서 시작 → 앞으로 ++ */
    int high = right + 1;   /* 배열 밖에서 시작 → 뒤로 --  */

    while (1) {
        /* pivot보다 작은 값이 아닐 때까지(즉 pivot 이상 만날 때까지) low++ */
        do {
            low++;
        } while (list[low] < pivot);

        /* pivot보다 큰 값이 아닐 때까지(즉 pivot 이하 만날 때까지) high-- */
        do {
            high--;
        } while (list[high] > pivot);

        if (low >= high) /* 포인터가 엇갈리면 파티션 완료 */
            return high;

        SWAP(list[low], list[high]); /* 잘못된 두 값 교환 */
    }
}

/* ---------- 재귀 퀵 정렬 ---------- */
void quick_sort(int list[], int left, int right) {
    if (left < right) {
        int p = partition(list, left, right);
        quick_sort(list, left, p);      /* Hoare는 p까지 포함 */
        quick_sort(list, p + 1, right); /* p+1부터 오른쪽 */
    }
}

/* ---------- 테스트용 main ---------- */
int main(void) {
    int arr[] = {38, 27, 43, 3, 9, 82, 10};
    int n = sizeof(arr) / sizeof(arr[0]);

    quick_sort(arr, 0, n - 1);

    for (int i = 0; i < n; ++i)
        printf("%d ", arr[i]);
    puts("");

    return 0;
}
