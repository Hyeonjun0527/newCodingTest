#include <iostream>
using namespace std;
int main() {
    int n;
    cin >> n;
    if (n == 1) {
        cout << 35;
        exit(0);
    } else if (n == 2) {
        cout << 105;
        exit(0);
    } else if (n == 3) {
        cout << 210;
        exit(0);
    } else if (n >= 4) {
        int temp = 210;
        for (int i = 4; i <= n; i++) {
            int a, b, c;
            a = 2; // 개수
            b = 2 * i - 4;
            c = i - 2;
            temp += (28 * a + 7 * b + 21 * c + 14);
        }
        cout << temp;
    }
}
//  14
/*
n=2은 1+3개
5
4 4 2

n=3
일단 1+3+6개 10개
5
4 2 4
4 1
4 1 2 3 1 4
4 1 1 2

4 4
*/