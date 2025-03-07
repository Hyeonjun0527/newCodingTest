
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
vector<int> visited;
vector<vector<int>> adj_list;

void dfs(int v) {
    if(visited[v]) return;
    visited[v] = true;
    cout << v << " ";
    for (int nv : adj_list[v]) {
        dfs(nv);
    }
};

void bfs(int v) {
    queue<int> vq;
    vq.push(v);
    visited[v] = true;

    while(!vq.empty()) {
        int cv = vq.front(); vq.pop();
        cout << cv << " ";

        for (int nv : adj_list[cv]) {
            if (visited[nv]) continue;
            vq.push(nv);
            visited[nv] = true;
            
        }
    }
}



int main() {
    int v, e, s;

    cin >> v >> e >> s;

    visited.resize(v + 1, false);
    adj_list.resize(v + 1);

    for (int i = 0; i < e; i++) {
        int ss, e;
        cin >> ss >> e;
        adj_list[ss].emplace_back(e);
        adj_list[e].emplace_back(ss);
    }

    for (int i = 1; i <= v; i++) {
        sort(adj_list[i].begin(), adj_list[i].end());
    }

    dfs(s);

    cout << "\n";

    fill(visited.begin(), visited.end(),false);

    bfs(s);

}


/* 

4 5 1
1 2
1 3
1 4
2 4
3 4


*/

