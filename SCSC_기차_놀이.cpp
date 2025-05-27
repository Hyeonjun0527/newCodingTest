#include <iostream>
using namespace std;
int main() {
    char p = '['; //
    int n = 0;
    cin >> n;
    long long cnt = 0;
    char t;
    cin >> t;
    for (int i = 1; i < n; i++) {
        char k;
        cin >> k;

        if (p == '[' && k == ']') {
            cnt += 1;
        } else if (p == '[' && k == '[') {
            cnt += 1;
        } else if (p == '[' && (k == '5' || k == '2')) {
            cnt += 2; // 2개만들엇으니까2점이야
        } else if (p == ']' && k == ']') {
            cnt += 1;
        } else if (p == '5' && k == '5') {
            cnt += 2;
        } else if (p == '5' && (k == '2' || k =='[') {
            cnt += 1;
        } else if (p == '2' && k == '2') {
            cnt += 2;
        } else if (p == '2' && k == '5') {
            cnt += 1;
        }

        p = k;
    }
    cout << cnt;
}