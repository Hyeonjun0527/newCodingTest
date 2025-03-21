/*
MST
 */

#include <bits/stdc++.h>
using namespace std;

int v, e;
int count_use_edge = 0;
int sum_weight = 0;
vector<int> mom;

int find(int a) {
    return a == mom[a] ? a : (mom[a] = find(mom[a]));
}
void uni(int a, int b) {
    a = find(a); b = find(b);
    if (a != b) mom[b] = a;
}
bool check_same(int a, int b) {
    if(find(a) == find(b)) return true;
    return false;
}
struct Edge {
    int start, end, w;
    Edge (int start, int end, int w) : start(start), end(end), w(w) {};
    bool operator< (const Edge& other) const {
        return w > other.w;
    }
};
priority_queue<Edge> pq;
void MST() {
    while (count_use_edge < v - 1 && !pq.empty()) {
        Edge current = pq.top(); pq.pop();
        int a = current.start;
        int b = current.end;
        if (check_same(a, b)) continue;
        uni(a, b);
        sum_weight += current.w;
        count_use_edge++;
    }
}
int main() {ios::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

    cin >> v >> e;

    mom.resize(v + 1);
    for (int i = 1; i <= v; i++) {
        mom[i] = i;// 1 based
    }

    for (int i = 0; i < e; i++) {
        int start, end, w;
        cin >> start >> end >> w;
        pq.emplace(start, end, w);
    }

    MST();

    if (count_use_edge < v - 1) cout << "-1";// cout << "MST를 만들 수 없습니다.\n";
    else if (count_use_edge == v - 1) cout << sum_weight;
}
