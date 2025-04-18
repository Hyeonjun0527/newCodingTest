#include <stdio.h>

// 하노이 탑 재귀 알고리즘
// n개의 원반을 from 기둥에서 to 기둥으로 옮기되,
// 중간 기둥 tmp를 보조로 사용
void hanoi_tower(int n, char from, char tmp, char to) {
    // 원반이 1개만 남았다면 바로 옮기고 출력
    if (n == 1)
        printf("원판1을 %c에서 %c으로 옮긴다.\n", from, to);
    else {
        // n-1개를 임시 기둥(tmp)로 옮김
        hanoi_tower(n - 1, from, to, tmp);
        // 가장 큰 원판(n번째)을 목적지(to)로 옮김
        printf("원판%d을 %c에서 %c으로 옮긴다.\n", n, from, to);
        // 임시 기둥(tmp)에 있던 n-1개 원반을 목적지(to)로 옮김
        hanoi_tower(n - 1, tmp, from, to);
    }
}

int main(void) {
    // 원반 4개를 A에서 C로 옮기기 (B는 보조기둥)
    hanoi_tower(4, 'A', 'B', 'C');
    return 0;
}
