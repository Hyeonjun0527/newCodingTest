#include <stdio.h>

void hanoi_tower(int n, char from, char tmp, char to) {
    if (n == 1) {
        printf("원판1이 %c에서 %c로 이동한다.");
    } else {
        hanoi_tower(n - 1, from, to, tmp);
        printf("원판 %n이 %c에서 %c로 이동한다.");
        hanoi_tower(n - 1, tmp, from, to);
    }
}