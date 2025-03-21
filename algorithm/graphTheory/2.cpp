#include <iostream>
#include <vector>

using namespace std;

/*
백준 1717번일지도.
7 8
0 1 3
1 1 7
0 7 6
1 7 1
0 3 7
0 4 2
0 1 1
1 1 1
*/

// 특정 원소가 속한 집합을 찾기 (경로 압축 기법 사용)
int find_parent(vector<int>& parent, int x) {
    if (parent[x] != x) {
        //경로압축 : 루트노드를 저장하는 parent테이블 생성
        parent[x] = find_parent(parent, parent[x]);
    }
    return parent[x];
}

// 두 원소가 속한 집합을 합치기
void union_parent(vector<int>& parent, int a, int b) {
    //각 원소가 속한 집합의 루트 노드를 찾는다. 루트노드를 합친다.
    a = find_parent(parent, a);
    b = find_parent(parent, b);
    if (a < b) {
        parent[b] = a;
    } else {
        parent[a] = b;
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    //부모 테이블을 초기화. 처음에는 자신이 부모야.
    vector<int> parent(n + 1);
    for (int i = 0; i <= n; i++) {
        parent[i] = i;
    }

    // 각 연산을 하나씩 확인
    for (int i = 0; i < m; i++) {
        int oper, a, b;
        cin >> oper >> a >> b;

        if (oper == 0) { // 합집합(union) 연산인 경우
            union_parent(parent, a, b);
        } else if (oper == 1) { // 찾기(find) 연산인 경우
            if (find_parent(parent, a) == find_parent(parent, b)) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
        }
    }

    return 0;
}
