#include <iostream>
using namespace std;
int main() {
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        int sum = 0;
        int n;
        cin >> n;
        for (int j = 0; j < n; j++) {
            int d;
            cin >> d;
            sum += d;
        }
        cout << sum << "\n";
    }
}