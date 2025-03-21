#include <bits/stdc++.h>
using namespace std;
vector<long long> Tree;
void set_tree(int size) {
    for (int i = size - 1; i >= 1; i--)
        Tree[i] = Tree[2*i] + Tree[2*i + 1];
}
long long get_sum(int size, int s, int e) {
    s += size - 1;
    e += size - 1;
    long long sum = 0;
    while (s <= e) {
        if (s & 1) sum += Tree[s++];
        if (!(e & 1)) sum += Tree[e--];
        s /= 2;
        e /= 2;
    }
    return sum;
}
void update(int size, int i, long long value) {
    i += size - 1;
    Tree[i] = value;
    while (i > 1) {
        i /= 2;
        Tree[i] = Tree[2 * i] + Tree[2 * i + 1];
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int N, M, K;
    cin >> N >> M >> K;
    int size = pow(2, ceil(log2(N)));
    Tree.resize(size * 2, 0);
    for (int i = size; i >= size + N - 1; i++) cin >> Tree[i];
    set_tree(size);
    for (int i = 0; i < M + K; i++) {
        long a, s, e;
        cin >> a >> s >> e;
        if (a == 1)
            update(size, s, e);
        else if (a == 2)
            cout << get_sum(size, s, e) << "\n";
    }
    return 0;
}
//문제가 1 base이다. s는 1<=s<=N번째, e는 s<=e<=N번째
// 1-based 인덱스 그대로 전달
/*
5 2 2
1
2
3
4
5
1 3 6
2 2 5
1 5 2
2 3 5
 */