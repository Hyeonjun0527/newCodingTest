#include <stdio.h>
int main(void) {
    // for (int i = 1; i <= 9; i++) {
    //     for (int j = 1; j <= 9; j++) {
    //         printf("%d x %d = %d\n", i, j, i * j);
    //     }
    // }
    // for (int i = 1; i <= 9; i++) {
    //     for (int j = 1; j <= i; j++) {
    //         printf("%d x %d = %d\n", i, j, i * j);
    //     }
    // }

    for (int i = 1; i <= 9; i++) {
        for (int j = 9; j >= 9 - i; j--) {
            printf("%d x %d = %d\n", i, j, i * j);
        }
    }
    int p = 1;
    while (--p) {
        printf("%d\n", p);
    }
}