#include <iostream>
using namespace std;
int main() {
    string a;
    cin >> a;
    int len = a.size();
    int ispal = 1;
    for (int i = 0; i < (len / 2); i++) {
        if (a[i] != a[len - 1 - i]) {
            ispal = 0;
        }
    }
    cout << ispal;
}