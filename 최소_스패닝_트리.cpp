/* 
3 3(vertex edge개수)
1 2 1(start end weight)
2 3 2
1 3 3

*/
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<int> mom;

int find(int a) {
    return a==mom[a] ? a : (mom[a] = find(mom[a]));
}

void uni(int a, int b) {
    a = find(a);
    b = find(b);
    if(a != b) {
        mom[b] = a;
    }
}

bool check_same(int a, int b) {
    if (find(a) == find(b)) {
        return true;
    } else {
        return false;
    }
}

struct Edge{
    int start,end, w;
    Edge(int start, int end, int w):start(start), end(end), w(w){};
    bool operator<(const Edge& other) const {
        return w > other.w;//pq 오름차순
    }
};

int main() {
    int v, e;
    cin >> v >> e;

    mom.resize(v+1);
    priority_queue<Edge> pq;

    for (int i = 1; i <= v; i++) {
        mom[i] = i;
    }

    for (int i = 0; i < e; i++)
    {
        int s, e, w;
        cin >> s >> e >> w;
        pq.emplace(s,e,w);
    }
    
    int count = 0;
    int sum = 0;
    while(count < v - 1 && !pq.empty()) {
        auto [start, end, w] = pq.top(); pq.pop();
        if (check_same(start, end)) continue;
        uni(start, end);
        count++;
        sum += w;
    }

    if (count == v - 1) {
        cout << sum;
    } else {
        cout << -1;
    }
}