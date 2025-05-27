#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char name[7]; // 최대 6자 + '\0'
    int pathLen;  // 루트→자신까지 전체 길이
    struct Node *left, *right;
} Node;

/* 노드 생성 */
Node *newNode(const char *s) {
    Node *n = malloc(sizeof(Node));
    strcpy(n->name, s); // name채우고,
    n->pathLen = 0;
    n->left = n->right = NULL;
    return n;
}

/* (루트, 부모까지 길이) → 서브트리의 pathLen 채우기 */
void setLen(Node *cur, int parentLen) {
    if (!cur)
        return;
    cur->pathLen = parentLen + (int)strlen(cur->name);
    if (cur->left)
        setLen(cur->left, cur->pathLen + 1); // ‘/’
    if (cur->right)
        setLen(cur->right, cur->pathLen + 1);
}

int main(void) {
    int T;
    scanf("%d", &T);
    while (T--) {
        int N;
        scanf("%d", &N);

        /* 1) 노드 배열 만들기 (1-베이스) 동적배열 제작*/
        Node **v = malloc((N + 1) * sizeof(Node *));
        for (int i = 1; i <= N; ++i) {
            char buf[8];
            scanf("%s", buf);
            v[i] = newNode(buf);
        }
        // v 는 Node* 포인터 배열
        for (int i = 1; i <= N; ++i) { // ① 모든 노드에 대해
            int l = i * 2;             //    왼쪽 자식 예상 번호
            int r = i * 2 + 1;         //    오른쪽 자식 예상 번호

            if (l <= N)             // ② 실제로 노드가 존재하면
                v[i]->left = v[l];  //    왼쪽 포인터 연결
            if (r <= N)             // ③ (마찬가지)
                v[i]->right = v[r]; //    오른쪽 포인터 연결
        } //   존재하지 않으면 NULL 유지

        /* 3) 경로 길이 채우기 (루트부터) */
        setLen(v[1], 0);

        /* 4) 출력 */
        for (int i = 1; i <= N; ++i)
            printf("%d\n", v[i]->pathLen);

        /* 5) 메모리 해제 */
        for (int i = 1; i <= N; ++i)
            free(v[i]);
        free(v);
    }
    return 0;
}
