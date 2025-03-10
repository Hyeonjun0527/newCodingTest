#include <iostream>
#include <limits.h>
#include <vector>
#include <queue>
using namespace std;
int v,e,s;
vector<int> visited;
vector<int> md;
vector<int> pre_node;
struct Edge{
    int nn,w;
    Edge(int nn, int w):nn(nn), w(w) {};
    bool operator<(const Edge& other) const {
        return w > other.w;
    }
};
vector<vector<Edge>> adj_list;
priority_queue<Edge> pq;

void algo() {
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
    if (node = -1) return;
    print_path(pre_node[node]);
    cout << node << " ";
}

int main() {

}