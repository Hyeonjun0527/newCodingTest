#include <bits/stdc++.h>
#define INF 1e9

using namespace std;

int n, m, start;
vector<pair<int, int> > graph[30001];
int d[30001];

void dijkstra(int start) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.emplace(0, start);
    d[start] = 0;
    while (!pq.empty()) { // 큐가 비어있지 않다면

        int dist = -pq.top().first; // 현재 노드까지의 비용, 최단시간
        int now = pq.top().second; // 현재 노드번호
        pq.pop();

        if (d[now] < dist) continue;
        for (auto [fst, snd] : graph[now]) {
            if (int cost = dist + snd; cost < d[fst]) {
                d[fst] = cost;
                pq.emplace(-cost, fst);
            }
        }
    }
}

int main() {
    cin >> n >> m >> start;

    for (int i = 0; i < m; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        graph[x].emplace_back(y, z);
    }
    fill_n(d, 30001, INF);
    dijkstra(start);
    int count = 0;
    int maxTime = 0;
    for (int i = 1; i <= n; i++) {
        // 도달할 수 있는 노드인 경우
        if (d[i] != INF) {
            count += 1;
            maxTime = max(maxTime, d[i]);
        }
    }

    cout << count - 1 << ' ' << maxTime << '\n';
}