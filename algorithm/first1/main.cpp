#include <iostream>
#include <vector>
using namespace std;

int main() {

    // cout << "HELLO1" << endl;

    int n,m;
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    int A[n+1] = {0};
    int S[n+1] = {0};
    for (int i = 1; i < n; ++i) {
        cin >> A[i];
        S[i] = S[i-1] + A[i];
    }
    int i,j;
    for (int j = 0; j < m; ++j) {
        cin >> i >> j;
        cout << S[j] - S[i-1];
    }
}


/*
5 3
5 4 3 2 1
1 3
2 4
5 5
 */