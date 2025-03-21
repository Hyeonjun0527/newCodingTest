/*


a+b번 2중반복하고 k < a+b번 반복하네

a+b번 반복하는데

a+b/2

 */


#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int T,a,b;
    cin >> T;
    for (int i = 0; i < T; i++) {
        cin >> a >> b;
        long long m = a+b;
        cout << (m)*(m-1)*(m)/2 << "\n";
    }
}
