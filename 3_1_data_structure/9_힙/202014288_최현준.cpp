#include <bits/stdc++.h>
using namespace std;
struct Node {
    int end_time; // 비는 시간
    int id;       // 0~n-1
    bool operator<(const Node &o)
        const { // < 일떄 me > other 하면 큐에선 오름차 배열에선 내림차
        if (end_time != o.end_time) {
            return end_time > o.end_time;
        } else {
            return id > o.id;
        }
    }
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n, m;
    cin >> n >> m;
    vector<int> money(n, 0); // 계산대마다의 돈

    priority_queue<Node> pq;
    for (int i = 0; i < n; ++i) {
        pq.emplace(0, 1);
    }

    int mx = 0;

    for (int i = 0; i < m; ++i) {
        int time, price; // 시간 가격
        cin >> time >> price;
        Node asdf = pq.top();
        pq.pop();
        // 계산끝날때 구하기
        int s = asdf.end_time; // 시작시간
        int e = s + time;

        money[asdf.id] += price;
        mx = max(mx, e);

        pq.push({e, asdf.id});
    }

    cout << mx << '\n';
    for (int i = 0; i < n; ++i) {
        cout << money[i] << '\n'
    };
}
