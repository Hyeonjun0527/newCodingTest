#include <iostream>
#include <queue>
#include <vector>
using namespace std;

vector<vector<int>> adj_list;
vector<bool> visited;
vector<int> dist;

void bfs(int v) {
    queue<int> q;
    q.push(v);
    visited[v] = true;
    dist[v] = 0;
    while (!q.empty()) {
        int cv = q.front();
        q.pop();
        for (int nv : adj_list[cv]) {
            if (visited[nv])
                continue;
            visited[nv] = true;
            dist[nv] = dist[cv] + 1;
            q.push(nv);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    adj_list.assign(n + 1, {});
    visited.assign(n + 1, false);
    dist.assign(n + 1, -1);

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj_list[a].push_back(b);
        adj_list[b].push_back(a);
    }

    bfs(1);

    // 가장 먼 거리(maxDist)를 찾기
    int maxDist = 0;
    for (int i = 1; i <= n; i++)
        if (dist[i] > maxDist)
            maxDist = dist[i];

    // 그 거리와 같은 헛간들 중 가장 번호가 작은 헛간(minIdx)과그 개수(cnt)를
    // 구한 세 값을 출력합니다.
    int minIdx = 0, cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (dist[i] == maxDist) {
            if (minIdx == 0 || i < minIdx)
                minIdx = i;
            ++cnt;
        }
    }

    cout << minIdx << ' ' << maxDist << ' ' << cnt << '\n';
    return 0;
}
