#include <iostream>
using namespace std;
typedef long long ll;
int main() {
    ll t, n;
    cin >> t;
    for (ll i = 0; i < t; i++) {
        cin >> n;

        if (n % 2 == 1) {
            cout << 0 << "\n";
        } else {
            ll k = 1;
            for (ll i = 0; i < n / 2; i++) {
                k *= 2;
            }
            cout << k << "\n";
        }
    }
}