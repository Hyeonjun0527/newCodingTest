#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
using namespace std;


int v, e, s;
vector<int> md;
vector<int> visited;
vector<int> pre_node;
struct Edge{
    int nn, w;
    Edge(int nn, int w) : nn(nn), w(w){};
    bool operator< (const Edge& other) const {
        return w > other.w;
    }
};
priority_queue<Edge> pq;
vector<vector<Edge>> adj_list;
void algo(){
    md[s] = 0;
    while (!pq.empty())
    {
        auto [nn, _] = pq.top(); pq.pop();
        if (visited[nn]) continue;
        visited[nn] = true;
        int cn = nn;
        for (auto& [nn, w] : adj_list[cn]) {
            if (md[nn] > md[cn] + w) {
                md[nn] = md[cn] + w;
                pre_node[nn] = cn;
                pq.emplace(nn, md[nn]);
            }
        }
    }
}

void print_path(int node) {
    if (node == -1) return;
    print_path(pre_node[node]);
    cout << node << " ";
}

int main() {
    cin >> v >> e >> s;
    visited.resize(v+1, false);
    md.resize(v+1, INT_MAX);
    pre_node.resize(v+1, -1);
    adj_list.resize(v+1, vector<Edge>());
    for (int i = 0; i < e; i++) {
        int s,e,w;
        cin >> s >> e >> w;
        adj_list[s].emplace_back(e,w);
    }
    algo();
    for (int i = 1; i <= v; i++) {
        if (visited[i]) {
            cout << md[i] << "\n";
        } else {
            cout << -1 << "\n";
        }
    }
};