#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; // 테스트케이스 수
    cin >> T;
    while (T--) {
        int N;
        cin >> N;

        vector<string> name(N + 1);
        for (int i = 1; i <= N; ++i)
            cin >> name[i];

        vector<int> pathLen(N + 1);
        pathLen[1] = (int)name[1].size(); // 루트

        for (int i = 2; i <= N; ++i) {
            int parent = i >> 1; // i / 2
            pathLen[i] = pathLen[parent] + 1 + (int)name[i].size();
        }

        for (int i = 1; i <= N; ++i)
            cout << pathLen[i] << '\n';
    }
    return 0;
}
