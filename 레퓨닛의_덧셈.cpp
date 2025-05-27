#include <iostream>
#include <string>
using namespace std;
int main() {
    int x, y;
    cin >> x >> y;
    string a = "";
    string b = "";
    for (int i = 0; i < x; i++) {
        a += "1";
    }
    for (int i = 0; i < y; i++) {
        b += "1";
    }
    long long c = stoll(a);
    long long d = stoll(b);
    cout << c + d;
}