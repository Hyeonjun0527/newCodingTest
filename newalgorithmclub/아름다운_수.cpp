#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string a;
        cin >> a;
        set<char> s;
        for (char c : a) {
            if (s.count(c) == 0) {
                s.emplace(c);
            }
        }
        int cnt = 0;
        for (char c : s) {
            cnt++;
        }
        cout << cnt << "\n";
    }
}