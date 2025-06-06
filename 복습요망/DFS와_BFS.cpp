#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

vector<vector<int>> adj_list;
vector<int> visited;

void dfs(int v) {
    if (visited[v]) return;
    visited[v] = true;
    cout << v << " ";
    for (int nv : adj_list[v]) {
        dfs(nv);
    }
}

void bfs(int v) {//vertex
    queue<int> vq;//vertex queue;
    vq.push(v);
    visited[v] = true;
    while (!vq.empty()) {
        int cv = vq.front(); vq.pop();//current vertex;
        cout << cv << " ";

        for (int nv : adj_list[cv]) { // nv : next_node(adj) vertex;
            if(visited[nv]) continue;
            visited[nv] = true;
            vq.push(nv);
        }
    }
}

int main() {
    int v, e, s;
    cin >> v >> e >> s;

    visited.resize(v + 1, false);
    adj_list.resize(v + 1);

    for (int i = 1; i <= e; i++) {
        int ss, e;//start end
        cin >> ss >> e;
        adj_list[ss].emplace_back(e);
        adj_list[e].emplace_back(ss);
    }


    for (int i = 1; i <= v; i++) {
        sort(adj_list[i].begin(), adj_list[i].end());
    }

    dfs(s);

    cout << "\n";

    fill(visited.begin(), visited.end(), false);

    bfs(s);
    
}