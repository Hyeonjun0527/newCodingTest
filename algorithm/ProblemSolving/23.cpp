/*
6 5
1 2
2 5
5 1
3 4
4 6


 */
//백준 11724번
#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj_list;
vector<bool> visited;
void DFS(int node);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N, M;
    cin >> N >> M;

    adj_list.resize(N + 1);
    visited = vector<bool>(N + 1, false);

    for (int i = 0; i < M; i++) {
        int s, e;
        cin >> s >> e;
        adj_list[s].push_back(e);
        adj_list[e].push_back(s);
    }

    int count = 0;
    for (int i = 1; i < N + 1; i++) {
        if (!visited[i]) {
            count++;
            DFS(i);
        }
    }
    cout << count << "\n";
}

/*
푸시하기
확인하기
방문처리하기
하나씩 순회하기(다하고 팝)
 */
void DFS(int node) {
    //확인하고
    if (visited[node]) return;
    visited[node] = true;
    for (int nextNode : adj_list[node]) {
        DFS(nextNode);
    }
}