//LCM은 GCD구하고 a*b를 GCD로 나눈값이야
#include <iostream>
#include <cmath>
using namespace std;

int gcd(int a, int b);
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        int a, b;
        cin >> a >> b;
        int result = a * b / gcd(a, b);
        cout << result << "\n";
    }
}

int gcd(int a, int b) {
    if (b == 0)
        return a;
    else
        return gcd(b, a % b);
}