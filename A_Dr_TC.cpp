#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main() {
    int t;
    int n;
    cin >> t;
    for (int i = 0; i < t; i++) {
        cin >> n;
        vector<string> slist(n);
        string a; // a의 사이즈 n
        cin >> a;
        string b;
        for (int j = 0; j < n; j++) {
            b = a;
            if (a[j] == '0') {
                b[j] = '1';
            } else {
                b[j] = '0';
            }
            slist[j] = b;
        }
        int cnt = 0;
        for (string k : slist) {
            for (char r : k) {
                if (r == '1')
                    cnt++;
            }
        }
        cout << cnt;
        cout << "\n";
    }
}