/*
relax함수는 이중 중첩 반복문이다.
V-1번 반복하고, E번 반복하므로, O(V x E)의 시간복잡도를 갖는다.
V는 10의 3제곱 E는 10의 4제곱이므로 총 10의 7제곱이다.
현대 컴퓨터가 10^8승 1억을 1초만에 수행한다고 알려져있으므로
그러므로 대략 0.1초만에 수행 가능하다고 볼 수 있따.
 */


#include <bits/stdc++.h>
using namespace std;


vector<tuple<int, int, int>> edges;
vector<int> MD;
void relax(int V) {
    for (int i = 1; i < V; ++i) {
        for (auto [u, v, w] : edges) {
            if (MD[u] != INT_MAX &&
                MD[v] > MD[u] + w) {
                MD[v] = MD[u] + w;
            }
        }
    }

};

bool check_nega(int i) {
    for (auto [u, v, w] : edges) {
        if (MD[u] != INT_MAX &&
            MD[v] > MD[u] + w) {
            return true;
        }
    }
    return false;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int V, E;
    cin >> V >> E;

    MD.resize(V+1, INT_MAX);
    MD[1] = 0;

    //벨만포드는 간선리스트가 필요해 간선마다 반복하니깐.
    //출발노드 도착노드 가중치

    //간선 리스트 입력받았어.
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.emplace_back(u, v, w);
    }

    //간선완화하려면 파라미터 뭐 필요하지. 일단 해봐 V 필요
    relax(V);

    //V-1번 relax하고 나서도 갱신이 발생하면 음수 사이클
    bool is_nega = check_nega(V);

    if (is_nega) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}
