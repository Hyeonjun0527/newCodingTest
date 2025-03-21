/*
구구단이 있어 5가 구구단표에 있니 이거야.
그러면 어케 푸냐 다 arraylist에 넣어
 */

#include <bits/stdc++.h>
using namespace std;

vector<int> gugu(100);
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    for (int i = 1; i <= 9; i++) {
        gugu.push_back(i);
        for (int j = 1; j <= 9; j++) {
            gugu.push_back(j * i);
        }
    }

    int N;
    cin >> N;

    int ans = 0;
    for (int num : gugu) {
        if (N == num) ans = 1;
    }

    cout << ans << endl;
    
}
