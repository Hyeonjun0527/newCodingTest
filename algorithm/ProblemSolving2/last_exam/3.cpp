
#include <bits/stdc++.h>
using namespace std;

int N, M;
struct Edge {
    int start,end, w;
    Edge(int start, int end, int w) : start(start),end(end),w(w) {};
    bool operator<(const Edge& other) const {
        return w > other.w;
    }
};
priority_queue<Edge> pq;
vector<int> mom;
int find(int a) {
    return a==mom[a] ? a : mom[a] = find(mom[a]);
}
void uni(int a, int b) {
    a = find(a);
    b = find(b);
    if (a != b) mom[b] = a;
}

bool check_same(int a, int b) {
    if (find(a) == find(b)) return true;
    return false;
}
int count_use_edge=0;
int sum_weight =0;
void MSB() {
    while (count_use_edge < N - 1 && !pq.empty()) {
        Edge current = pq.top(); pq.pop();
        int a = current.start;
        int b = current.end;
        if (check_same(a,b)) continue;
        uni(a,b);
        sum_weight += current.w;
        count_use_edge++;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M;
    mom.resize(N + 1);

    for (int i = 1; i <= N; i++) {
        mom[i] = i;
    }

    for (int i = 1; i <= M; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        pq.emplace(a,b,c);
    }
    MSB();

    cout << sum_weight;

}
