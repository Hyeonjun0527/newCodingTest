#include <bits/stdc++.h>
using namespace std;

int f(vector<vector<int>> &w, vector<vector<int>> &v, vector<int> &m, int a,
      int b) {
    int res0 = 0, res1 = 0;
    int t0 = 0, t1 = 0;
    for (int i = 0; i < 10; i++) {
        int cnt0 = 0, cnt1 = 0;
        for (int j = 0; j < 4; j++) {
            if (v[0][i * 4 + j] == 1)
                cnt0++;
            if (v[0][i * 4 + j] == 2)
                cnt1++;
        }
        t0 += w[i][cnt0];
        t1 += w[i][cnt1];
    }
    res0 += t0;
    res1 += t1;

    res0 += m[0] * a / 100;
    res1 += m[1] * a / 100;

    for (int i = 0; i < 40; i++) {
        if (v[2][i] == 1 && v[0][i] == 1)
            res0 -= b;
        if (v[2][i] == 1 && v[0][i] == 2)
            res1 -= b;
    }

    return res0 - res1;
}
void solve() {
    vector<vector<int>> w(10, vector<int>(5, 0));
    for (int i = 0; i < 10; i++) {
        for (int j = 1; j <= 4; j++)
            cin >> w[i][j];
    }
    string s[3];
    cin >> s[0] >> s[1] >> s[2];
    vector<vector<int>> v(3, vector<int>(40));
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 40; j++)
            v[i][j] = s[i][j] - '0';
    }
    vector<int> m(2);
    cin >> m[0] >> m[1];
    vector<int> mm(2);
    cin >> mm[0] >> mm[1];
    int a, b;
    cin >> a >> b;

    int ans1 = f(w, v, m, a, b);
    m[0] += mm[1] - mm[0];
    m[1] += mm[0] - mm[1];
    for (int i = 0; i < 40; i++) {
        if (v[1][i] == 1)
            v[0][i] = 1;
        if (v[1][i] == 2)
            v[0][i] = 2;
    }
    int ans2 = f(w, v, m, a, b);

    if (ans1 <= ans2)
        cout << "YES\n";
    else
        cout << "NO\n";
}

int main() {
    int t;
    t = 1;
    while (t--)
        solve();
}