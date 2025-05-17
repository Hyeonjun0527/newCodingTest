#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; // 테스트케이스 수
    if (!(cin >> T))
        return 0;

    while (T--) {
        int N, M;
        cin >> N >> M;
        cin.ignore(); // M 뒤의 '\n' 제거

        // 1) 복원할 문장 읽기
        string line;
        getline(cin, line);
        vector<string> target;
        {
            string w;
            stringstream ss(line);
            while (ss >> w)
                target.push_back(w);
        }

        // 2) 친구 노트 읽기
        vector<vector<string>> note(N);
        for (int i = 0; i < N; ++i) {
            int K;
            cin >> K;
            note[i].resize(K);
            for (int j = 0; j < K; ++j)
                cin >> note[i][j];
        }

        // 3) BFS: 상태 = 각 노트별로 꺼낸 단어 개수
        queue<vector<int>> q;
        unordered_set<string> visited; // 직렬화된 상태 문자열 저장

        // 초기 상태 [0,0,...,0]
        vector<int> init(N, 0);
        q.push(init);

        // 초기 상태 직렬화해서 visited에 추가
        {
            string key;
            for (int i = 0; i < N; ++i)
                key += "0,";
            visited.insert(key);
        }

        // 단어 하나씩 꺼내며 레벨별 BFS
        for (const string &word : target) {
            int sz = q.size();
            if (sz == 0)
                break; // 더 이상 진행 불가 → 실패

            while (sz--) {
                auto cur = q.front();
                q.pop();
                // 친구 i가 이 단어를 꺼낼 수 있으면
                for (int i = 0; i < N; ++i) {
                    if (cur[i] < (int)note[i].size() &&
                        note[i][cur[i]] == word) {
                        auto nxt = cur;
                        ++nxt[i]; // 친구 i 인덱스 하나 증가

                        // nxt를 "x,y,z,..." 문자열로 직렬화
                        string key;
                        for (int j = 0; j < N; ++j)
                            key += to_string(nxt[j]) + ",";

                        // 처음 보는 상태면 큐에 추가
                        if (visited.insert(key).second)
                            q.push(nxt);
                    }
                }
            }
        }

        // 마지막까지 남은 상태가 하나라도 있으면 성공
        bool ok = !q.empty();
        cout << (ok ? 1 : 0) << "\n";
    }

    return 0;
}
