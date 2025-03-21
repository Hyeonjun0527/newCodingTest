/*
단순 유니온 파인드.
백준 1717번

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


//find 2줄 uni 2줄 checkSame 2줄
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
vector<int> mom;
//최상위 부모노드 호출
int find(int a) {
    return a == mom[a] ? a : (mom[a] = find(mom[a]));
}
//a,b의 부모를 찾아. 합쳐.
void uni(int a, int b) { 	// union 연산 : 바로 연결이 아닌 대표 노드끼리 연결하여 줌
    a = find(a), b = find(b);
    if (a != b) mom[b] = a;
}

bool check_same(int a, int b) { // 두 원소가 같은 집합인지 확인
    if (find(a) == find(b)) return true;
    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N, M;
    cin >> N >> M;
    mom.resize(N + 1);

    for (int i = 0; i <= N; i++) { 	// 대표 노드를 자기 자신으로 초기화 하기
        mom[i] = i;
    }

    for (int i = 0; i < M; i++) {
        int question, a, b;
        cin >> question >> a >> b;
        if (question == 0) { 	// 집합 합치기
            uni(a, b);
        } else {	 // 같은 집합의 원소인지 확인하기
            if (check_same(a, b)) {
                cout << "YES\n";
            }
            else {
                cout << "NO\n";
            }
        }
    }
}
