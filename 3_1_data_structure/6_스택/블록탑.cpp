#include <iostream>
#include <stack>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        int n;
        cin >> n;
        stack<int> ms; // min
        stack<int> xs; // max
        stack<int> s;
        for (int j = 0; j < n; j++) {
            int a, b;
            cin >> a;
            if (a == 1) {
                cin >> b;
                s.push(b);
                if (!ms.empty()) {
                    ms.push(min(ms.top(), b));
                } else {
                    ms.push(b);
                }
                if (!xs.empty()) {
                    xs.push(max(xs.top(), b));
                } else {
                    xs.push(b);
                }

                cout << ms.top() << " " << xs.top() << "\n";
                continue;
            }
            if (a == 2) {
                if (!s.empty()) {
                    s.pop();
                    ms.pop();
                    xs.pop();
                }
            }
        }
    }
}