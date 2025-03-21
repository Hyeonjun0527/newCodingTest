#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N;
    cin >> N;
    vector<int> T;
    vector<int> P;
    T.resize(N+1);
    P.resize(N+1);
    for (int i = 1; i <= N; i++) {
        cin >> T[i] >> P[i];
    }
    vector<int> DP;
    DP.resize(N+1,0);

    for (int i = 2; i <= N; i++) {
        if (T[i] + i <= N) {
            DP[i] = max(DP[i-T[i]], DP[i-T[i]] + P[i]);
        } else {
            DP[i] = DP[i-1];
        }
    }
    cout << DP[N];
}
