#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/*
트리 노드의 NULL 포인터 자리에 “다음에 중위 순회에서 방문할 노드” 주소를 끼워
넣어 실처럼 꿰어 놓는다는 뜻의 thread

*/
typedef struct TreeNode {
    char data; // 그림과 맞추기 위해 char 사용
    struct TreeNode *left;
    struct TreeNode *right;
    bool right_thread; // 오른쪽 링크가 스레드인가?
} TreeNode;

/* ---------- 기본 유틸 ---------- */
TreeNode *create_node(char data) {
    TreeNode *n = malloc(sizeof(TreeNode));
    n->data = data;
    n->left = n->right = NULL;
    n->right_thread = false;
    return n;
}

/* ---------- 1단계: 스레드(후속자) 달기 ---------- */
/* successor 파라미터 = “현재 서브트리를 다 돌고 나면 가야 할 다음 노드” */
void assign_successor(TreeNode *cur, TreeNode *successor) {
    if (cur == NULL)
        return;

    /* 왼쪽 서브트리를 먼저 방문하므로
       “왼쪽에서 되돌아왔을 때”의 후속자는 현재 노드 */
    assign_successor(cur->left, cur);

    /* 현재 노드의 오른쪽 자식이 없으면
       → inorder 후속자를 스레드로 달아 준다 */
    if (cur->right == NULL) {
        cur->right = successor;
        cur->right_thread = true;
    } else {
        /* 오른쪽이 진짜 서브트리라면 successor 유지한 채 재귀 */
        assign_successor(cur->right, successor);
    }
}

/* ---------- 2단계: 왼쪽 끝 노드 찾기 ---------- */
static TreeNode *leftmost(TreeNode *n) {
    while (n && n->left)
        n = n->left;
    return n;
}

/* ---------- 3단계: 스레드 이용 중위 순회 ---------- */
void inorder_threaded_traverse(TreeNode *root, void (*visit)(TreeNode *)) {
    /* ① 루트에서 가장 왼쪽으로 가면 중위 순회의 첫 노드 */
    for (TreeNode *cur = leftmost(root); cur != NULL;) {
        visit(cur); /* 현재 노드 처리 */

        /* ② right_thread == true : 이미 후속자가 걸려 있으니
              그쪽으로 한 칸만 이동 */
        if (cur->right_thread)
            cur = cur->right;
        else
            /* ③ 오른쪽이 진짜 서브트리면, 그 서브트리의
                   ‘가장 왼쪽’ 노드가 다음 방문 대상  */
            cur = leftmost(cur->right);
    }
}

/* 방문 함수 예: 데이터 출력 */
void print_node(TreeNode *n) {
    printf("[%c] ", n->data);
}

/* ---------- 데모 ---------- */
int main(void) {
    /*   예시 트리
                  A
                /   \
               B     C
              / \   / \
             D   E F   G
       → 중위(Inorder): D B E A F C G
    */
    TreeNode *A = create_node('A');
    TreeNode *B = create_node('B');
    TreeNode *C = create_node('C');
    TreeNode *D = create_node('D');
    TreeNode *E = create_node('E');
    TreeNode *F = create_node('F');
    TreeNode *G = create_node('G');

    A->left = B;
    A->right = C;
    B->left = D;
    B->right = E;
    C->left = F;
    C->right = G;

    /* 1) 한 번만 돈 뒤 오른쪽 NULL 자리마다 후속자 연결 */
    assign_successor(A, NULL);

    /* 2) 스레드를 이용해 재귀·스택 없이 중위 순회 */
    printf("Inorder = ");
    inorder_threaded_traverse(A, print_node);
    puts("");

    /* 실제 사용에서는 free 도 수행해야 함 (스레드 때문에 순환 x) */
    return 0;
}
