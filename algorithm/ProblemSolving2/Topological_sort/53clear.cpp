//백준 2252


/*
3 2
1 3
2 3

1 2 3
 */
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int v, query_count;
vector<vector<int>> adj_list;
vector<int> indegree;//그냥 1씩 늘어나는거 뿐이야. 그리고 1씩 줄어드는거 뿐이야. 그리고 0되면 푸시하는거
void BFS() {
    queue<int> q;
    for (int i = 1; i <= v; i++) if (indegree[i] == 0) q.push(i);
    while (!q.empty()) {
        int current_node = q.front(); q.pop();
        cout << current_node << " ";
        for (int next_node : adj_list[current_node]) {
            indegree[next_node]--;
            if (indegree[next_node] == 0) q.push(next_node);
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> v >> query_count;
    adj_list.resize(v + 1);
    indegree.resize(v + 1);
    for (int imm = 0; imm < query_count; imm++) {
        int start, end;
        cin >> start >> end;
        adj_list[start].emplace_back(end);
        indegree[end]++;
    }
    BFS();
}