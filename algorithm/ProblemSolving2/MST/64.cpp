/*
쌩기초
 * 1197
3 3 V : 노드개수 E : 엣지개수
1 2 1 노드 1과 노드 2가 가중치1의 엣지로 연결되어있음 이런라인이 E개 만큼있음 가중치는 음수도 가능
2 3 2
1 3 3

출력 : MST의 전체 가중치 합

MST >> 유니온 파인드, 우선순위 큐, 사이클 안생기면 노드 유니온

 */
#include <bits/stdc++.h>
using namespace std;

// Union-Find 구조에서 부모를 저장하는 벡터
vector<int> mom;

// 부모 노드를 찾고 Union-Find 연산을 수행하기 위한 함수 선언

//찾아야지 > 부모를 찾는 거잖아(대표,최상단 부모) > 파파
int find(int a) {   // 특정 노드의 부모를 찾는 함수 (Find)
    return a == mom[a] ? a : (mom[a] = find(mom[a]));
}

//합쳐야지 > 뭐를? 같은 집합으로 만드는거잖아 > 부모를 합쳐야지
void uni(int a, int b) {// 두 노드를 합치는 함수 (Union)
    a = find(a); b = find(b);
    if (a != b) mom[b] = a;
}
bool check_same(int a, int b) {
    if(find(a) == find(b)) return true;
    return false;
}
//엣지 리스트 생성. 인접리스트아님.
// 에지(Edge)의 정보를 저장하는 구조체 정의 에지 - 노드1, 노드2, 가중치
struct Edge {
    int start, end, w;
    Edge(int start, int end, int w) : start(start), end(end), w(w) {};

    //같은방향이면 내림차순 10 5 3 2 1  > v>o.v면 내림차순
    bool operator<(const Edge& other) const {
        return w > other.w;
    }
};
priority_queue<Edge> pq;
int count_use_edge = 0;  // 현재까지 사용된 에지의 수
int sum_weight = 0;   // MST의 총 가중치

int main() {
    // 입출력 속도 최적화
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    // N: 노드의 개수, M: 에지의 개수
    int N, M;
    cin >> N >> M;
    // 최소 힙을 사용하여 에지를 가중치 기준 오름차순으로 저장
    // Union-Find 초기화: 각 노드가 자기 자신을 부모로 가짐
    mom.resize(N+1);
    for (int i = 1; i <= N; i++) {
        mom[i] = i;
    }


    // 에지 정보를 입력받아 우선순위 큐에 추가
    for (int i = 0; i < M; i++) {
        int s,e,v;
        cin >> s >> e >> v; // s: 시작 노드, e: 끝 노드, v: 가중치
        pq.emplace(s, e, v);// 우선순위 큐에 에지 삽입

        //다익스트라는 간성정보를 인접리스트에 다 담아. 그리고 큐순회에서 인접리스트를 순회해.
        //MST는
    }
    // MST(Minimum Spanning Tree) 구성 변수


    // MST를 만들기 위해 N-1개의 에지가 필요
    // MST 완성하는 시점에 useEdge, result 다 완성되어있어.
    //while (useEdge < N - 1) 은 useEdge == N-1로 만들겠다는 뜻이야.(useEdge=0, ++이므로)
    while (count_use_edge < N - 1 && !pq.empty()) {//pq.empty()는 입력조건이 모든 도시 연결할 수 없는 걸 주면 무한루프를 도는데, 그걸 방지함.

        Edge current = pq.top(); pq.pop(); // 가중치가 가장 작은 에지를 가져옴
        int a = current.start;
        int b = current.end;

        // 사이클이 생기지 않는 경우만 에지를 사용
        if (check_same(a, b)) continue;// 두 노드의 부모가 다르면 사이클이 생기지 않음

        uni(a, b); // 두 노드를 Union 연산으로 연결
        sum_weight += current.w;// 현재 에지의 가중치를 결과에 추가
        count_use_edge++;   // 사용한 에지 수 증가
    }
    //while N-1만큼 사용해야대 두 대표가 다를 때 유니온,

    // MST의 총 가중치를 출력
    cout << sum_weight;
}




/*
#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
using namespace std;

void unionSet(int a, int b);
int find(int a);

static vector<int> p;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;
    p.resize(N + 1);
    for (int i = 1; i <= N; i++) p[i] = i;

    while (M--) {
        int s, e, v;
        cin >> s >> e >> v;
        pq.push({v, s, e}); // 가중치, 시작 노드, 끝 노드 순으로 푸시
    }

    int useEdge = 0, result = 0;
    while (useEdge < N - 1 && !pq.empty()) {
        auto [v, s, e] = pq.top(); pq.pop(); // 튜플 구조 분해
        if (find(s) != find(e)) { // 사이클이 발생하지 않으면
            unionSet(s, e);
            result += v;
            useEdge++;
        }
    }

    cout << result;
    return 0;
}

void unionSet(int a, int b) {
    a = find(a);
    b = find(b);
    if (a != b) p[b] = a;
}

int find(int a) {
    return (a == p[a]) ? a : (p[a] = find(p[a]));
}

 */