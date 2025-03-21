
/*
a,b와 0,0이야
a=0, b=0 은 없대
a=0 or b = 0 이면 1이야
둘다 0 아니면 2야
이거 훼이크 아니야?
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int a , b, x, y;
    cin >> a >> b >> x >> y;

    if (a == 0 or b == 0) {

        if (x == 0 && a == 0 && y < b || y == 0 && b == 0 && x < a) {
            cout << 3;
        } else {
            cout << 1;
        }

    } else if (a !=0 and b!=0) {
        cout << 2;
    }
    
}
