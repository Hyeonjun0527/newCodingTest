/*
백준 1991번

이진트리란?
모든 노드가 2개이하의 서브트리를 가지고 있는 것.
모든 노드의 차수가 2개 이하다
깊이가 d라면 총 노드 수는?
2^d - 1이야
루트노드의 깊이는?
1이야
이진트리를 표현하는 방법은?
배열, 포인터 근데 배열 많이 사용해.
전위순회 중위순회 후위순회 하는 방법은?
가장 큰 트리를 보았을 때
루트 왼쪽 오른쪽
왼쪽 루트 오른쪽
왼쪽 오른쪽 루트
후위순회는 왼쪽을 최우선으로 보겠다 이거야. 사실은 이거 말로 표현하기 힘들고
코드로 봐야돼. 스택을 이용해서 왼쪽 우선 오른쪽 우선 현재노드(루트) 우선

세그먼트트리
N = N이면 리프노드 수 = K는???
N과 가장 가까운 2^k(2의 배수)개래. 즉 7이면 8이야.
그거 컴퓨터로 어케 구해?
log2N을 셀링(올림)을 해. 그리고 그걸 다시 2의 지수에 넣어.
K = ceil(log2N) 니까 pow(2,ceil(log2N)).
가장 가까운 >> ceil

K로 최대 깊이의 관계?
루트노드의 깊이를 1이라고 하면 리프노드의 수K === 2^(H-1)(최대 깊이 H 라고 하면) 야.

K와 총 노드 개수의 관계?
2 * K - 1이야.
리프노드수 x 2 - 1한 게 총 노드 수야.

그리고 노드 높이는 k + 1

입력 : A B C 이런게 n번 주어진데




char a = 'A'; // ASCII 값: 65
    char b = 'C'; // ASCII 값: 67
    int offset = 2;

    // 1. 더하기 연산 (+)
    cout << "a + offset (as int): " << (a + offset) << endl; // ASCII 값 65 + 2 = 67 출력
    cout << "a + offset (as char): " << static_cast<char>(a + offset) << endl; // ASCII 값 67 -> 문자 'C' 출력

    // 2. 빼기 연산 (-)
    cout << "b - a (as int): " << (b - a) << endl; // ASCII 값 67 - 65 = 2 출력
    cout << "b - a (as char): " << static_cast<char>(b - a) << endl; // 강제로 문자로 캐스팅 (출력은 제어 문자)

    // 3. 문자 + 문자
    cout << "a + b (as int): " << (a + b) << endl; // ASCII 값 65 + 67 = 132 출력
    cout << "a + b (as char): " << static_cast<char>(a + b) << endl; // ASCII 값 132 -> 문자로 변환
    cout << "a - b (as int): " << (a - b) << endl;
 */


#include <bits/stdc++.h>
using namespace std;

int n;
int tree[26][2];//26개의 노드 2차수
void preOrder(int now);
void inOrder(int now);
void postOrder(int now);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n;

    //1. 트리 만들어. 2. 순회 해
    for (int i = 0; i < n; i++) {//n번반복해
        char node_char, left_char, right_char;
        cin >> node_char >> left_char >> right_char;

        int node = node_char - 'A';
        int left = left_char - 'A';
        int right = right_char - 'A';

        if (left_char == '.') tree[node][0] = -1;
        else tree[node][0] = left;

        if (right_char == '.') tree[node][1] = -1;
        else tree[node][1] = right;
    }

    preOrder(0);
    cout << "\n";
    inOrder(0);
    cout << "\n";
    postOrder(0);
    cout << "\n";
}
void preOrder(int now) {
    if (now == -1) return;
    cout << static_cast<char>(now + 'A');//char와 char연산, int와 int와 연산은 다 int야
    preOrder(tree[now][0]);
    //tree[now][0] now의 왼쪽 자식노드 호출
    preOrder(tree[now][1]);
}
void inOrder(int now) {
    if (now == -1) return;
    inOrder(tree[now][0]);
    cout << static_cast<char>(now + 'A');
    inOrder(tree[now][1]);
}
void postOrder(int now) {
    if (now == -1) return;
    postOrder(tree[now][0]);
    postOrder(tree[now][1]);
    cout << static_cast<char>(now + 'A');
}