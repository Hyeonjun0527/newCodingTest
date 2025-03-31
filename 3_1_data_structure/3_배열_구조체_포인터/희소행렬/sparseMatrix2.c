#include <stdio.h>
#include <stdlib.h>

#define MAX_TERMS 100
typedef struct {
    int r; // row
    int c; // col
    int v; // value
} Term;

typedef struct SparseMatrix {
    Term t[MAX_TERMS]; // (a,b,c) 항
    int rc;            // rowcount
    int cc;            // colcount
    int tc;            // term_count 항 개수
} SparseMatrix;

/*
자, 코드를 볼때는 이차원 배열이면
0 -> {}
1 -> {}
...
를 떠올리거나 테이블을 떠올려
*/

// pq는 < 하고 >해야 오름차
// comp는 <하고 < 해야 오름차
// return 음수 면 x,y순서로 정렬됨
// return x - y 하자. x-y<0 면 x,y순서로 정렬됨 오름차순
int comp(void *x, void *y) {
    Term *a = (Term *)x;
    Term *b = (Term *)y;

    if (a->r != b->r)
        return a->r - b->r;
    else
        return a->c - b->c;
}

SparseMatrix matrix_transpose2(SparseMatrix a) {
    SparseMatrix b;
    int bidx;
    // 희소행렬
    /*
    bidx : 0 =>(a,b,c)
    bidx : 1 =>(d,e,f)
    ...
    */
    b.rc = a.cc;
    b.cc = a.rc;
    b.tc = a.tc;
    if (a.tc > 0) {
        for (int i = 0; i < a.tc; i++) {
            b.t[i].r = a.t[i].c;
            b.t[i].c = a.t[i].r;
            b.t[i].v = a.t[i].v;
        }

        qsort(b.t, b.tc, sizeof(Term), comp);
    }
    return b;
}
void matrix_print(SparseMatrix a) {
    printf("====================\n");
    for (int i = 0; i < a.tc; i++) {
        printf("(%d, %d, %d) \n", a.t[i].r, a.t[i].c, a.t[i].v);
    }
    printf("====================\n");
}

int main(void) {
    SparseMatrix m = {{{0, 3, 7},
                       {1, 0, 9},
                       {1, 5, 8},
                       {3, 0, 6},
                       {3, 1, 5},
                       {4, 5, 1},
                       {5, 2, 2}},
                      6,
                      6,
                      7};
    SparseMatrix result;
    result = matrix_transpose2(m);
    matrix_print(result);
    return 0;
}