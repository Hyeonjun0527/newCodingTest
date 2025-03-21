#include <bits/stdc++.h>
using namespace std;
//공통조상 LCA문제야
int N, e;
int level = 1;
int now_count = 0;
int now_max_count = 1;

vector<vector<int>> adj_list;
vector<bool> visited;
vector<int> depth;
vector<int> mom;
void BFS(int node) {
    queue<int> q;
    q.emplace(node);
    visited[node] = true;
    while (!q.empty()) {
        int current_node = q.front(); q.pop();
        for (int next_node : adj_list[current_node]) {
            if (visited[next_node]) continue;
            visited[next_node] = true;
            mom[next_node] = current_node;
            depth[next_node] = level;
            q.emplace(next_node);
        }
        now_count++;
        if (now_count == now_max_count) {
            now_count = 0;
            now_max_count = q.size();
            level++;
        }
    }
}
int find_lca(int a, int b) {
    if (depth[a] < depth[b]) {
        int temp = a;
        a = b;
        b = temp;
    }
    while (depth[a] !=depth[b]) a = mom[a];
    while (a != b) {
        a=mom[a];
        b=mom[b];
    };
    return a;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;

    adj_list.resize(N + 1,vector<int>());
    visited.resize(N + 1, false);
    depth.resize(N+1, 0);
    mom.resize(N + 1, 0);

    for (int i = 1; i <= N-1; i++) {
        int u, v;
        cin >> u >> v;
        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }
    int query_count = 0;
    cin >> query_count;
    BFS(1);

    for (int i = 1; i <= query_count; i++) {
        int a, b;
        cin >> a >> b;
        cout << find_lca(a, b) << endl;
    }
    return 0;
}
