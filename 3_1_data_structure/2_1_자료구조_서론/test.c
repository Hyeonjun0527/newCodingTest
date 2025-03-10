#include <stdio.h>
#define MAX_ELEMENTS 100

int scores[MAX_ELEMENTS];

int get_max_score(int n) { // 학생의 숫자는 n
    int i, largest;
    largest = scores[0];
    for (i = 1; i < n; i++) {
        if (scores[i] > largest) {
            largest = scores[i];
        }
    }
    return largest;
}

int main() {
    // 예시 데이터를 입력합니다.
    scores[0] = 50;
    scores[1] = 80;
    scores[2] = 65;
    int n = 3;
    int max = get_max_score(n);
    printf("최대 점수는: %d\n", max);
    return 0;
}
