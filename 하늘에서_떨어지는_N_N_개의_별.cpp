#include <iostream>
#include <vector>
using namespace std;
int main() {
    int n, d, k;
    cin >> n >> d >> k;
    vector<int> s(n);    // 떨어지는 점이 개수
    vector<int> m(n, 0); // 별누적할거야
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    int maxv = -1;
    int idx = 0;
    for (int i = 0; i < n; i++) {
        if (maxv < s[i]) {
            maxv = s[i];
            idx = i;
        }
    }
    // cout << maxv << "\n";
    maxv = 0;
    int cnt = 0;
    for (int e = 0; e < d; e++) {
        // cout << e << "일차\n";
        maxv += s[idx];
        if (maxv > k) { // 청소해

            maxv = s[idx];

            cnt++;
        }
        // cout << maxv << " \n";
        // cout << "cnt :: " << cnt << "\n";
        // cout << m[i] << " ";
        // cout << "\n";
    }
    cout << cnt;
}
// K일이되었는지 계속 검사하면 댐