#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    long long x1,x2,x3,y1,y2,y3;

    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
    // long long sol = x1*y2 - x2*y1 - x2*y3 + x3*y2 + x3*y1 - y3*x1;
    long long sol = x1*y2 - x2*y1 +x2*y3 - x3*y2 - x3*y1 +y3*x1;

    if (sol > 0) {
        cout << -1 << "\n";
    } else if (sol < 0) {
        cout << 1 << "\n";
    } else{
        cout << 0 << "\n";
    }
    return 0;
}
