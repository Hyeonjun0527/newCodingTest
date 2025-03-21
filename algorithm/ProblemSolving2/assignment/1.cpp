/*
트리를 초기화 : O(size)=>O(n)
get max : O(log n)
update : O(log n)
get max 쿼리가 q번 작동될 것이다.
그러므로 총 시간 복잡도는 O(n + q * log n)이다.
 */


#include <bits/iterator_concepts.h>
#include <bits/stdc++.h>
using namespace std;

vector<int> A;
vector<long> tree;

void set_tree(int size) {
    for (int i = size - 1; i > 0; i--) {
        tree[i] = max(tree[i * 2], tree[i * 2 + 1]);
    }
}

long get_max(int size, int s, int e) {
    s += size - 1;
    e += size - 1;
    long max_value = LLONG_MIN;
    while (s <= e) {
        if (s & 1) max_value = max(max_value, tree[s++]);
        if (!(e & 1)) max_value = max(max_value, tree[e--]);
        s /= 2;
        e /= 2;
    }
    return max_value;
}

void update(int size, int i, long value) {
    i += size - 1;
    tree[i] = value;

    while (i > 1) {
        i /= 2;
        tree[i] = max(tree[2 * i], tree[2 * i + 1]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, q;
    cin >> n >> q;
    //size : n보다 크거나 같은데 2의 거듭 제곱 중 가장 큰 값
    //log2씌우고 올림하고 pow하기
    int size = pow(2,ceil(log2(n)));
    /*int size = 1;
    while (size < n) {
        size *= 2;
    }*/
    tree.resize(size * 2, LLONG_MIN);

    for (int i = 0; i < n; i++) {
        cin >> tree[size + i];
    }
    set_tree(size);

    for (int i = 0; i < q; i++) {
        int a, b, c;
        cin >> a >> b >> c;

        if (a == 1) {
            update(size, b, c);
        } else if (a == 2) {
            cout << get_max(size, b, c) << "\n";
        }
    }
    return 0;

    //세그먼트 트리 만드는 방법 트리 만들어서... 배열로 만들어. 트리를 그리고. get_max, update 만들어.

}
