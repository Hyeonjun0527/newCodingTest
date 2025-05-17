#include <stdio.h>
#include <stdlib.h>

#define MAX(a,b) (((a)>(b))?(a):(b))
#define MAX_DEGREE 100

typedef struct {
    float coef;
    int exp;
} Term;

typedef struct {
    int capacity;   // 배열의 용량 (최대 항의 개수)
    int size;       // 실제 저장된 항의 개수
    int degree;     // 최고 차수
    Term* terms;    // 항 배열
} Polynomial;

// 다항식 생성 (초기화)
Polynomial* create_polynomial(int capacity) {
    Polynomial* poly = (Polynomial*)malloc(sizeof(Polynomial));
    poly->terms = (Term*)malloc(sizeof(Term) * capacity);
    poly->capacity = capacity;
    poly->size = 0;
    poly->degree = -1;
    return poly;
}

// 다항식 메모리 해제
void free_polynomial(Polynomial* poly) {
    if (poly) {
        free(poly->terms);
        poly->terms = NULL;
        free(poly);
    }
}

// 다항식 출력
void print_poly(Polynomial* poly) {
    if (poly->size == 0) {
        printf("0\n");
        return;
    }

    for (int i = poly->size - 1; i > 0; i--)
        printf("%3.1fx^%d + ", poly->terms[i].coef, poly->terms[i].exp);
    printf("%3.1fx^%d\n", poly->terms[0].coef, poly->terms[0].exp);
}

// term 추가 함수 (용량 체크 포함)
void add_term(Polynomial* poly, float coef, int exp) {
    if (coef == 0) return;

    if (poly->size >= poly->capacity) {
        printf("용량 초과! 항 추가 불가 (capacity=%d)\n", poly->capacity);
        return;
    }

    // 같은 차수 존재 시 계수 합산
    for (int i = 0; i < poly->size; i++) {
        if (poly->terms[i].exp == exp) {
            poly->terms[i].coef += coef;
            return;
        }
    }

    poly->terms[poly->size].coef = coef;
    poly->terms[poly->size].exp = exp;
    poly->size++;
    poly->degree = MAX(exp, poly->degree);
}

// 항 존재 체크
void check_terms(Polynomial* poly, int* check) {
    for (int i = 0; i < poly->size; i++) {
        int exp = poly->terms[i].exp;
        check[exp]++;
    }
}

// 필요한 항 개수 확인
int get_terms_size(int* array, int degree) {
    int size = 0;
    for (int exp = 0; exp <= degree; exp++)
        if (array[exp] > 0)
            size++;
    return size;
}

// 다항식 덧셈 함수
Polynomial* poly_add(Polynomial* A, Polynomial* B) {
    int array[MAX_DEGREE + 1] = { 0 };//array는 항의 계수(4x^2에서 4)

    check_terms(A, array);
    check_terms(B, array);//전체 항의 개수를 얻어 C를 만들기 위함

    int degree = MAX(A->degree, B->degree);
    int size = get_terms_size(array, degree);//전체 항의 개수를 얻어 C를 만들기 위함
    Polynomial* C = create_polynomial(size);

    for (int exp = 0; exp <= degree; exp++) {
        float coef = 0.0;

        for (int i = 0; i < A->size; i++)
            if (A->terms[i].exp == exp) {
                coef += A->terms[i].coef;
                break;
            }

        for (int i = 0; i < B->size; i++)
            if (B->terms[i].exp == exp) {
                coef += B->terms[i].coef;
                break;
            }

        add_term(C, coef, exp);
    }

    return C;
}

// 메인 함수 (테스트 코드)
int main(void) {
    Polynomial* a = create_polynomial(5);
    add_term(a, 1, 0);  
    add_term(a, 7, 1);  
    add_term(a, 8, 3);  
    print_poly(a);      

    Polynomial* b = create_polynomial(5);
    add_term(b, 1, 0);  
    add_term(b, 3, 2);  
    add_term(b, 10, 3); 
    print_poly(b);      

    Polynomial* c = poly_add(a, b);
    printf("-----------------------------\n");
    print_poly(c);      

    free_polynomial(a);
    free_polynomial(b);
    free_polynomial(c);

    return 0;
}
