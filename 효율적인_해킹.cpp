#include <iostream>
#include <queue>
#include <set>
#include <vector>
using namespace std;

vector<vector<int>> adj_list;
vector<bool> visited;

int bfs(int node) {
    queue<int> q;
    q.push(node);
    // set<int> s;
    int cnt = 1;
    visited[node] = true;
    while (!q.empty()) {
        int cn = q.front();
        // s.emplace(cn);
        q.pop();
        for (int nn : adj_list[cn]) {
            // if (s.find(nn) != s.end())
            //     s.emplace(nn);
            if (visited[nn])
                continue;
            cnt++;
            visited[nn] = true;
            q.push(nn);
        }
    }
    return cnt;
}

int main() {

    int n, m;
    cin >> n >> m;
    adj_list.resize(n + 1);
    visited.resize(n + 1);

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj_list[b].emplace_back(a);
    }
    vector<int> sol;
    int max_k = -1;

    for (int i = 1; i <= n; i++) {
        fill(visited.begin(), visited.end(), false);
        int k = bfs(i);
        sol.push_back(k);
        max_k = max(k, max_k);
    }
    for (int i = 0; i < sol.size(); i++) {
        if (sol[i] == max_k) {
            cout << i + 1 << " ";
        }
    }
}

// 가장 많이 신뢰되는 애를 찾으면 되는거야. 가장 많이 bfs 돌리고 새로운 컴퓨터
// 얼마나 찾앗는지 cnt해 . 그리고 그거 최대인애들 찾아. list로 보관해.