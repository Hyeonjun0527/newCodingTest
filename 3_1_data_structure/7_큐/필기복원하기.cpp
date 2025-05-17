/*
3개의 큐를 만들어.
하나 읽고 그게 3개의 큐에서 꺼낼수잇는지 확인(반복)
*/

#include <iostream>
#include <queue>
#include <sstream>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        int n, m;
        cin >> n >> m;
        string a;
        // clear
        cin.ignore();
        getline(cin, a);
        vector<queue<string>> qlist;
        for (int j = 0; j < n; j++) { //
            int k;
            cin >> k;
            string s;
            queue<string> st;
            for (int d = 0; d < k; d++) {
                cin >> s;
                st.push(s);
            }
            qlist.push_back(st);
        }
        stringstream ssr(a);
        bool bokwon = true;
        string str;
        while (ssr >> str) {
            bool isOk = false; // 매단어마다 true되어야해
            for (auto &que : qlist) {
                if (!q.empty() && q.front() == str) {
                    que.pop();
                    isOk = true; // 하나라도 되면 괜찮아.
                }
            }
            if (!isOk) {
                bokwon = false;
                break;
            }
        }
        if (bokwon) {
            cout << 1 << "\n";
        } else {
            cout << 0 << "\n";
        }
    }
}
/*
이게 머지 정렬과 비슷해?


*/