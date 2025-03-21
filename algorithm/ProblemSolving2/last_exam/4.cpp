#include <bits/stdc++.h>
using namespace std;

//다익스트라 알고리즘 어케 짜냐
int V,E,K;
vector<int> MD;
struct Edge {
    int next_node, w;
    Edge(int next_node, int w) : next_node(next_node) ,w(w) {};
    bool operator<(const Edge& other) const {
        return w > other.w;
    }
};
vector<vector<Edge>> adj_list;
priority_queue<Edge> pq;
vector<int> visited;

void algo() {
    MD[K] = 0;
    pq.emplace(K,0);
    while (!pq.empty()) {
        Edge current = pq.top(); pq.pop();
        if(visited[current.next_node]) continue;
        int current_node = current.next_node;
        visited[current_node] = true;
        for (auto& [next_node, w] : adj_list[current_node]) {
            if (MD[next_node] > MD[current_node] + w) {
                MD[next_node] = MD[current_node] + w;
                pq.emplace(next_node,MD[next_node]);
            }
        }
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> V >> E >> K;

    MD.resize(V + 1, INT_MAX);
    adj_list.resize(V + 1);
    visited.resize(V+1, false);

    for (int i = 1; i <= E; i++) {
        int start, end, w;
        cin >> start >> end >> w;
        adj_list[start].emplace_back(end, w);
    }
    algo();

    for (int i = 1; i <= V; i++) {
        if (MD[i] != INT_MAX){
            cout << MD[i] << "\n";
        } else {
            cout << "INF\n";
        }
    }
}
