#include <iostream>
using namespace std;

string func(int n) { // 등수
    if (n <= 25) {
        return "World Finals";
    } else if (n <= 1000) {
        return "Round 3";
    } else if (n <= 4500) {
        return "Round 2";
    }
    return "Round 1";
}

int main() {
    int t;
    cin >> t; // 테스트케이스
    for (int i = 0; i < t; i++) {
        int n;
        cin >> n; // 등수
        cout << "Case #";
        cout << (i + 1);
        cout << ": " + func(n) << "\n";
    }

    // 등수 4500 1000 25등 안에 들어야함.
}