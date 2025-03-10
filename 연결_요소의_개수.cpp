#include <iostream>
#include <vector>
using namespace std;
vector<vector<int>> adj_list;
vector<bool> visited;
void dfs(int v) {
  if (visited[v])
    return;
  visited[v] = true;
  for (int nv : adj_list[v]) {
    dfs(nv);
  }
}

int main() {
  int n, m;
  cin >> n >> m;
  adj_list.resize(n + 1);
  visited.resize(n + 1, false);
  for (int i = 0; i < m; i++) {
    int s, e;
    cin >> s >> e;
    adj_list[s].emplace_back(e);
    adj_list[e].emplace_back(s);
  }
  int cnt = 0;
  for (int i = 1; i <= n; i++) {
    if (!visited[i]) {
      dfs(i);
      cnt++;
    }
  }
  cout << cnt;
}