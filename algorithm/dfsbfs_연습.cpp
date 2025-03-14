#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
vector<vector<int>> adj_list;
vector<bool> visited;
void dfs(int v) {
    if (visited[v]) return;
    visited[v] = true;
    cout << v << " ";
    for (int nv : adj_list[v]) {
        dfs(nv);
    }
}
void bfs(int v) {
    queue<int> q;
    q.push(v);
    visited[v] = true;
    while (!q.empty())
    {
        int cv = q.front(); q.pop();
        cout << cv << " ";
        for (int nv : adj_list[cv]) {
            if (visited[nv]) continue;
            visited[nv] = true;
            q.push(nv);
        }
    }
}
int main() {
    int v,e,s;
    cin >> v >> e >> s;
    adj_list.resize(v + 1);
    visited.resize(v + 1, false);
    for (int i = 0; i < e; i++) {
        int s, e;
        cin >> s >> e;
        adj_list[s].emplace_back(e);
        adj_list[e].emplace_back(s);
    }
    for (int i = 1; i <= v; i++) {
        sort(adj_list[i].begin(), adj_list[i].end());
    }
    dfs(s);
    cout << "\n";
    fill(visited.begin(), visited.end(), false);
    bfs(s);
}