#include <stdio.h>
#define RC 3
#define CC 3
void mt(int a[RC][CC], int b[RC][CC]) {
    for (int r = 0; r < RC; r++) {
        for (int c = 0; c < CC; c++) {
            b[c][r] = a[r][c];
        }
    }
}
void mp(int a[RC][CC]) {
    printf("====================\n");
    for (int r = 0; r < RC; r++) {
        for (int c = 0; c < CC; c++)
            printf("%d ", a[r][c]);
        printf("\n");
    }
    printf("====================\n");
}

int main(void) {
    int array1[RC][CC] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int array2[RC][CC];
    mt(array1, array2);
    mp(array1);
    mp(array2);
    return 0;
}