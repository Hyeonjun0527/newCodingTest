#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int x;
    cin >> x;

    // for (int year = 1000; year <= 9999; year++) {
    //     if (year == (year/100+ year%100) * (year/100+ year%100)) {
    //         cout << year << "\n";
    //     }
    // }

    if (x < 2025) {
        cout << 2025;
    } else if (x < 3025) {
        cout << 3025;
    } else if (x < 9801) {
        cout << 9801;
    } else {
        cout << -1;
    }
}