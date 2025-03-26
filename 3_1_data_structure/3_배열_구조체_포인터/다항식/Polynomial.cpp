#include <stdio.h>

#define MIN(a, b) (a < b ? a : b)
#define MAX(a, b) (a < b ? b : a)
#define MAX_DEGREE 100

// 다항식을 표현하는 구조체 정의
typedef struct {
    int degree;
    float coef[MAX_DEGREE + 1];
} Polynomial;

// 다항식 덧셈 연산 함수: 결과 다항식 C = A + B
// 만약에 쓰레기 값 없이 없는건 0으로 초기화가 잘 된다면 굳이 나눠서 더할 필요가 없음.

Polynomial poly_add(Polynomial A, Polynomial B) {
    Polynomial C;
    int min_degree = MIN(A.degree, B.degree);
    int max_degree = MAX(A.degree, B.degree);

    C.degree = max_degree;
    
    int pos = 0;

    for (; pos <= min_degree; pos++)
        C.coef[pos] = A.coef[pos] + B.coef[pos];

    // A의 차수가 더 클 경우 남은 항 복사 왜 복사하냐 큰 항은 다른 다항식에 없자나
    
    // 차수가 큰 쪽을 선택하여 복사
    Polynomial* longer = A.degree > B.degree ? &A : &B;

    for (;pos <= max_degree; pos++)
        C.coef[pos] = longer -> coef[pos];

    return C;
}

// 다항식 뺄셈 연산 함수: 결과 다항식 C = A - B
Polynomial poly_subtract(Polynomial A, Polynomial B) {
    Polynomial C;
    int min_degree = MIN(A.degree, B.degree);
    int max_degree = MAX(A.degree, B.degree);
    C.degree = max_degree;

    int pos = 0;
    // 공통 차수 항끼리 빼기
    for (; pos <= min_degree; pos++)
        C.coef[pos] = A.coef[pos] - B.coef[pos];

    // A의 차수가 더 클 경우 남은 항 복사
    // 포인터와 부호변수로 분기 제거
    Polynomial *longer = (A.degree > B.degree) ? &A : &B;
    float sign = (A.degree > B.degree) ? 1.0f : -1.0f;

    for (; pos <= max_degree; pos++)
        C.coef[pos] = sign * longer->coef[pos];
    

    // if (A.degree > B.degree) {
    //     for (; pos <= max_degree; pos++)
    //         C.coef[pos] = A.coef[pos];
    // }
    // // B의 차수가 더 클 경우 남은 항 음수로 복사
    // else {
    //     for (; pos <= max_degree; pos++)
    //         C.coef[pos] = -B.coef[pos];
    // }

    return C;
}

// 다항식 출력 함수
void print_poly(Polynomial p) {
    for (int i = p.degree; i > 0; i--)
        printf("%3.1fx^%d + ", p.coef[i], i);
    printf("%3.1f\n", p.coef[0]);
}

// 메인 함수 (프로그램의 진입점)
int main(void) {
    Polynomial a = { 5, { 3, 6, 0, 0, 0, 10 } };  // 10x^5 + 6x + 3
    Polynomial b = { 4, { 7, 0, 5, 0, 1 } };      // 1x^4 + 5x^2 + 7
    Polynomial c;
    printf("다항식 A: ");
    print_poly(a);

    printf("다항식 B: ");
    print_poly(b);

    // 덧셈 수행
    c = poly_add(a, b);
    printf("-------------------------------------\n");
    printf("A + B = ");
    print_poly(c);

    // 뺄셈 수행
    c = poly_subtract(a, b);
    printf("A - B = ");
    print_poly(c);

    return 0;
}
