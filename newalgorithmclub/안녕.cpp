#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    cin >> n;
    vector<pair<double, int>> lose(n);
    vector<pair<double, int>> get(n);
    for (int i = 0; i < n; i++) {
        int t;
        cin >> t;
        lose[i] = make_pair(0, t);
    }
    for (int i = 0; i < n; i++) {
        int t;
        cin >> t;
        get[i] = make_pair(t / (double)lose[i].second, t);
        lose[i] = make_pair(t / (double)lose[i].second, lose[i].second);
    }

    sort(get.begin(), get.end(), greater<pair<double, int>>());
    sort(lose.begin(), lose.end(), greater<pair<double, int>>());

    // for (int i = 0; i < n; i++) {
    //     cout << get[i].second << " ";
    // }
    // cout << "\n";
    int h = 100;
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        // cout << h << "\n";
        // cout << lose[i].second << "\n";
        // cout << get[i].second << "\n";
        // cout << "끝\n";
        if ((h - lose[i].second) > 0) {
            h -= lose[i].second;
            cnt += get[i].second;
        }
    }
    cout << cnt;
}
// 스스로 정렬할 줄 모름 그래서 매번 sort 씀