#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<int> dp(N + 1, INF);
    dp[1] = 0; // Base

    for (int x = 2; x <= N; ++x) {         // Order
        dp[x] = min(dp[x], dp[x - 1] + 1); // -1
        if (x % 2 == 0)
            dp[x] = min(dp[x], dp[x / 2] + 1); // /2
        if (x % 3 == 0)
            dp[x] = min(dp[x], dp[x / 3] + 1); // /3
    }
    cout << dp[N] << '\n';

    /*
    D[i] : i에서 1로 만드는 데 걸리는 최소 연산 횟수
     */
}
