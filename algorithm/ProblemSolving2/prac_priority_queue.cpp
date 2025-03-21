#include <bits/stdc++.h>
using namespace std;

struct Node {
    int edge;
    Node(int edge) : edge(edge) {}

    // 작은 값이 우선되도록 (오름차순)
    bool operator<(const Node& other) const {
        return edge > other.edge;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    // 우선순위 큐 선언
    priority_queue<Node> pq;

    // 값 추가
    pq.push(Node(10));
    pq.push(Node(5));
    pq.push(Node(20));
    pq.push(Node(15));

    // 결과 출력
    cout << "Priority Queue Output:" << endl;
    while (!pq.empty()) {
        cout << pq.top().edge << " "; // 가장 작은 값부터 출력
        pq.pop();
    }

    return 0;
}
