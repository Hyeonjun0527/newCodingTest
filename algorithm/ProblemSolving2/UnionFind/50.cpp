/*
쌩기초
백준 1717번
 */


//find 2줄 uni 2줄 checkSame 2줄
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
static  vector<int> mom;
//a의 부모를 찾아. 내가 부모? 아니면 파파
int find(int a) {	 // find 연산 : 최상단 부모(대표) 노드를 찾아서 리턴
    //a == parent[a] 내가 부모라는건 부모를 찾았다는거네. 대표 노드를 찾았다는거야.
    // if (a == p[a]) return a;
    // return p[a] = find(p[a]);	 // 재귀함수의 형태로 구현 // 평탄화 작업. 만약에 트리가 완전히 평탄화 되어있으면 find(a)를 하나 p[a]를 하나 동일한 결과 나옴.

    return a == mom[a] ? a : (mom[a] = find(mom[a]));

    //내가 부모가 아니라는건 내 대표노드가 있다는거. 내 대표노드도 부모가 있는지 확인해야지.
    // find(parent[a])로 1. 부모를 찾는다는 거 이게 핵심이야
    // 2. 두번째 핵심은 머냐면 a의 대표노들르 업데이트 한다는거야. a의 대표노드를 루트노드로..!
}
//a,b의 부모를 찾아. 합쳐.
void uni(int a, int b) { 	// union 연산 : 바로 연결이 아닌 대표 노드끼리 연결하여 줌
    int mom_a = find(a); int mom_b = find(b);
    if (mom_a != mom_b) mom[mom_b] = mom_a;
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
                cout << "YES" << "\n";
            }
            else {
                cout << "NO" << "\n";
            }
        }
    }
}
