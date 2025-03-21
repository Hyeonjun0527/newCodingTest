/*
64.cpp 65.cpp 참고하기
간선을 큐에 추가하는 부분을 보자.
먼저 우선순위 큐는 push pop할 때 시간복잡도가 logM이다.
그런데 이를 M번 반복하고 있으므로 MlogM의 시간복잡도가 걸린다.

이제 크루스칼 알고리즘으로 두 노드를 계속 유니온 연산으로 연결해보자.
두 노드가 다른 집합에 있어야, 즉 부모가 달라야 유니온 연산을 할 수 있다.
사이클이 생기지 않기 위해서다.
사용된 엣지가 N-1이어야 MST가 생길 수 있다.
그래서 use_edge를 N-1번 whlie문으로 수행한다.
그리고 우선순위 큐를 pop하므로 logM의 시간복잡도가 걸린다.
그래서 이때 NlogM의 시간복잡도가 걸린다.
N보다는 M이 더 크므로 MlogM이 가장 크고 M은 10의 4승이다. 그러므로 TLE(시간제한초과)가 발생하지 않는다.

 */


#include <bits/stdc++.h>
using namespace std;

vector<int> mom;

int find(int a) {
    return a == mom[a] ? a : (mom[a] = find(mom[a]));
}

void uni(int a, int b) {
    a = find(a); b = find(b);
    if (a != b) mom[b] = a;
}

struct Edge {
    int start, end, w;
    bool operator> (const Edge& other) const {
        return w > other.w;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N, M, K;
    cin >> N >> M >> K;

    mom.resize(N + 1);
    for (int i = 1; i <= N; i++) {
        mom[i] = i;
    }

    priority_queue<Edge, vector<Edge>, greater<Edge>> pq;

    for (int i = 0; i < M; i++) {
        int s,e,v;
        cin >> s >> e >> v;
        pq.push(Edge{s,e,v});
    }


    for (int i = 0; i < K; i++) {
        int A, B, C;
        cin >> A >> B >> C;
    }


    int use_edge = 0;
    int result = 0;

    while (use_edge < N - 1 && !pq.empty()) {
        Edge current_edge = pq.top(); pq.pop();

        if (find(current_edge.start) != find(current_edge.end)) {
            uni(current_edge.start, current_edge.end);
            result += current_edge.w;
            use_edge++;
        }
    }

    if (use_edge == N - 1) cout << result;
    else cout << -1;
    
}
