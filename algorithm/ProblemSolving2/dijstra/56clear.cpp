/*
생성자 : 위에 잇는거 그대로 다 쓰면 대.
백준 1753
5 6 1
5 1 1
1 2 2
1 3 3
2 3 4
2 4 5
3 4 6

BFS는 큐에 넣을때 visited[] = true를 해 / 큐에서 노드를 꺼낸다는 것은 해당 노드를 방문하고, 그 노드의 인접 노드를 탐색
다익스트라는 큐에서 꺼냈을때 visited[] = true / 큐에서 노드를 꺼낸다는 것은 해당 노드의 최단 거리가 확정되었다는 의미입니다. 더 이상 이 노드는 다른 경로로 업데이트될 필요가 없다
DFS는 노드를 방문한 직후 visited = true
 */
#include <bits/stdc++.h>
using namespace std;
int v, e, s;
vector<int> MD;
vector<int> visite_d;
vector<int> previous_node;
struct Edge {
    int next_node, w;
    Edge(int next_node, int w) : next_node(next_node), w(w) {};
    bool operator<(const Edge& other) const {
        return w > other.w;
    }
};
vector<vector<Edge>> adj_list;
priority_queue<Edge> pq;
void algo() {
    MD[s] = 0;
    pq.emplace(s, 0);//넣을때 visited true안하고 꺼낼 때 해서 안함.
    while (!pq.empty()) {
        auto& [next_node, w] = pq.top(); pq.pop();
        if (visite_d[next_node]) continue;
        int current_node = next_node;
        visite_d[current_node] = true;
        for (auto& [next_node, w] : adj_list[current_node])
            if (MD[next_node] > MD[current_node] + w)
                MD[next_node] = MD[current_node] + w,
                previous_node[next_node] = current_node,
                pq.emplace(next_node,MD[next_node]);
    }
}

void print_path(int node) {
    if (node == -1) return; // Base case for recursion
    print_path(previous_node[node]); // Recursive call
    cout << node << " "; // Print current node
}
int main() {
    ios::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    cin >> v >> e >> s;
    MD.resize(v + 1, INT_MAX);
    adj_list.resize(v + 1, vector<Edge>());
    visite_d.resize(v + 1, false);
    previous_node.resize(v + 1, -1);
    for (int imm = 0; imm < e; imm++) {
        int start, end, w;
        cin >> start >> end >> w;
        adj_list[start].emplace_back(end, w);
    }
    algo();
    for (int i = 1; i <= v; i++) {
        if (visite_d[i]) {
            cout << "Shortest distance to node " << i << ": " << MD[i] << "\n";
            cout << "Path: ";
            print_path(i);
            cout << "\n";
        } else {
            cout << "Shortest distance to node " << i << ": INF\n";
            cout << "Path: INF\n";
        }
    }
}

