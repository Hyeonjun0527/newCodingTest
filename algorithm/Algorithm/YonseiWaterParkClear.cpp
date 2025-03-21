#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

vector<long long> Tree; vector<long long> DP; vector<long long> K;
// void set_tree(int size) { // 1 based Tree
//     for (int i = size - 1; i >= 1; i--) {
//         Tree[i] = Tree[2 * i] + Tree[2 * i + 1];// [i] = [2i] + [2i + 1]
//     }
// }
long long get_max(int size, int l, int r) {
    long long max_value = LLONG_MIN;
    l += size;
    r += size;
    while (l <= r) {
        if (l % 2) max_value = max(max_value, Tree[l++]);
        if (!(r % 2)) max_value = max(max_value, Tree[r--]);
        l /= 2;
        r /= 2;
    }
    return max_value;
}
void update(int size, int i, long long value) {
    i += size;
    Tree[i] = value;
    while (i > 1) {
        i /= 2;
        Tree[i] = max(Tree[i * 2], Tree[i * 2 + 1]);
    }
}
int main() {
    int n, d;
    cin >> n >> d;
    int size = 1;
    while (size < n) size *= 2;
    Tree.resize(2 * size, LLONG_MIN);
    K.resize(n);
    DP.resize(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> K[i];
        DP[i] = K[i];
    }
    long long result = LLONG_MIN;
    for (int i = 0; i < n; i++) {
        long long max_prev = 0;

        //0은 예외 i-d ~ i-1까지 세그먼트트리로 max 구하기
        if (i > 0) max_prev = get_max(size, max(0, i - d), i - 1);

        DP[i] = max(K[i], K[i] + max_prev);
        update(size, i, DP[i]);
        result = max(result, DP[i]);
    }
    cout << result << "\n";
    return 0;
}

//get_max는 항상 이미 업데이트된 범위에서만 쿼리날리므로 setTree할 필요 없음.
//즉, 0~3까지의 쿼리를 날리려면 범위 0~3까지만의 세그먼트 트리 정보만 있으면 됨. 그러므로 set_tree 안해도 댐.