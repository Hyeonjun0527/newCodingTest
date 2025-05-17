#include <stdio.h>
#include <stdlib.h>
#define MAX(a, b) (a > b ? a : b)
typedef struct _TermNode { // 노드타입
    double coef;
    int exp;
    struct _TermNode *next_node;
} TermNode;
typedef struct {     // 다항식구조체타입선언
    int size;        // 다항식항의개수
    int degree;      // 다항식의최고차수
    TermNode *terms; // 다항식의계수정보(linked list)
} Polynomial;

// 다항식초기화함수
Polynomial *create_polynomial() {
    Polynomial *poly = (Polynomial *)malloc(sizeof(Polynomial));
    poly->terms = NULL;
    poly->size = 0;
    poly->degree = 0;
    return poly;
}
// 다항식의한Term을생성
TermNode *create_term(float coef, int exp, TermNode *next_node) {
    TermNode *term = (TermNode *)malloc(sizeof(TermNode));
    term->exp = exp;
    term->coef = coef;
    term->next_node = next_node;
    return term;
}
// term 추가
void add_term(Polynomial *poly, float coef, int exp) {
    if (coef == 0)
        return; // 계수가0인항은추가하지않음
    // 추가할노드를검색(exp의내림차순)
    TermNode *prev_node = NULL;
    TermNode *cur = poly->terms;
    while (cur != NULL && cur->exp > exp) {
        prev_node = cur;
        cur = cur->next_node;
    }
    TermNode *new_node = create_term(coef, exp, NULL);

    // 새항추가

    if (prev_node == NULL) { // 맨 앞에 추가
        new_node->next_node = poly->terms;
        poly->terms = new_node;
    } else { // 중간 또는 마지막에 추가
        new_node->next_node = cur;
        prev_node->next_node = new_node;
    }
    poly->size++;
    poly->degree = MAX(exp, poly->degree);
}
// 다항식메모리해제함수
void free_polynomial(Polynomial *poly) {
    TermNode *temp = NULL;
    TermNode *cur = poly->terms;
    while (cur) {
        temp = cur;
        cur = cur->next_node;
        free(temp);
    }
    free(poly);
}
// 다항식출력
void print_poly(Polynomial *poly) {
    TermNode *cur = poly->terms;
    printf("Poly(%d, %d) = ", poly->degree, poly->size);
    while (cur) {
        printf("%.1fx^%d ", cur->coef, cur->exp);
        if (cur->next_node)
            printf("+ ");
        cur = cur->next_node;
    }
    printf(";\n");
}
Polynomial *poly_add(Polynomial *A, Polynomial *B) {
    TermNode *curA = A->terms;
    TermNode *curB = B->terms;
    Polynomial *poly = create_polynomial();
    while (curA && curB) {
        if (curA->exp > curB->exp) { // a의차수> b의차수
            add_term(poly, curA->coef, curA->exp);
            curA = curA->next_node;
        } else if (curA->exp < curB->exp) { // a의차수< b의차수
            add_term(poly, curB->coef, curB->exp);
            curB = curB->next_node;
        } else { // a의차수== b의차수(0인경우는add_term에서처리)
            add_term(poly, curA->coef + curB->coef, curA->exp);
            curA = curA->next_node;
            curB = curB->next_node;
        }
    }
    // A나B중의하나가먼저끝나게되면poly로남은항들복사
    for (; curA != NULL; curA = curA->next_node)
        add_term(poly, curA->coef, curA->exp);
    for (; curB != NULL; curB = curB->next_node)
        add_term(poly, curB->coef, curB->exp);
    return poly;
}
Polynomial *poly_sub(Polynomial *A, Polynomial *B) {
    TermNode *curA = A->terms;
    TermNode *curB = B->terms;
    Polynomial *poly = create_polynomial();
    while (curA && curB) {
        if (curA->exp > curB->exp) { // a의차수> b의차수
            add_term(poly, curA->coef, curA->exp);
            curA = curA->next_node;
        } else if (curA->exp < curB->exp) { // a의차수< b의차수
            add_term(poly, -curB->coef, curB->exp);
            curB = curB->next_node;
        } else { // a의차수== b의차수(0인경우는add_term에서처리)
            add_term(poly, curA->coef - curB->coef, curA->exp);
            curA = curA->next_node;
            curB = curB->next_node;
        }
    }
    // A나B중의하나가먼저끝나게되면poly로남은항들복사
    for (; curA != NULL; curA = curA->next_node)
        add_term(poly, curA->coef, curA->exp);
    for (; curB != NULL; curB = curB->next_node)
        add_term(poly, -curB->coef, curB->exp);
    return poly;
}
// 연결리스트 과제2
Polynomial *derivative(Polynomial *eq) {
    Polynomial *result = create_polynomial();
    TermNode *cur = eq->terms;

    while (cur != NULL) {
        int before_coef = cur->coef;
        int before_exp = cur->exp;
        if (before_exp >= 1) {
            add_term(result, before_coef * before_exp, before_exp - 1);
        }
        cur = cur->next_node;
    }
    return result;
}
// 연결리스트 과제2
float calculate_polynomial(Polynomial *eq, float x) {
    float result = 0.0;
    TermNode *cur = eq->terms;

    while (cur != NULL) {
        result += cur->coef * powf(x, cur->exp);
        cur = cur->next_node;
    }
    return result;
}
int main(void) {
    Polynomial *a = create_polynomial(); // 다항식a생성
    add_term(a, 1, 0);
    add_term(a, 2, 8);
    add_term(a, 3, 12);
    print_poly(a);
    // Polynomial *b = create_polynomial(); // 다항식b생성
    // add_term(b, 10, 6);
    // add_term(b, -3, 10);
    // add_term(b, 8, 12);
    // print_poly(b);
    // Polynomial *c = poly_add(a, b); // 다항식합성

    Polynomial *d = derivative(a);
    printf("##미분구하기\n");
    print_poly(d);

    Polynomial *b = create_polynomial(); // 다항식b생성
    add_term(b, 10, 2);
    add_term(b, -1, 1);
    add_term(b, 2, 3);
    print_poly(b);
    float x = 2.0;
    float value = calculate_polynomial(b, x);
    printf("##값 계산 : x=%.2f\n", x);
    printf("f(%.2f) = %.2f\n", x, value);

    free_polynomial(a);
    free_polynomial(b);
    // free_polynomial(c);
    free_polynomial(d);
    return 0;
}