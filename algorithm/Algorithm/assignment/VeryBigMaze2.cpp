#include <bits/stdc++.h>
using namespace std;
using namespace chrono;
set<array<int,2>> trap;
int range;
chrono::system_clock::time_point start_time;
bool BFS(int start[2], int exit[2]) {

    queue<pair<int,int>> pq;

    set<pair<int,int>> visited;

    pq.emplace(start[0], start[1]);

    int count = 0;
    while(!pq.empty()) {
        int dx[4] = {-1, 0, 0, 1};
        int dy[4] = {0, -1, 1, 0};

        int current_x = pq.front().first;
        int current_y = pq.front().second;
        pq.pop();

        // 도착함
        if(current_x == exit[0] && current_y == exit[1]) return true;
        // 187 x 187 넘으면 true
        if(count > range) return true;


        for(int i = 0; i < 4; i++) {
            int nx = current_x + dx[i];
            int ny = current_y + dy[i];
            //경계 초과 , 방문 했거나 막혀있음
            if (nx < 0 || nx > 999999 || ny < 0 || ny > 999999) continue;
            if (visited.find({nx, ny}) != visited.end() || trap.find({nx, ny}) != trap.end()) continue;

            pq.emplace(nx, ny);
            visited.insert({nx, ny});

        }
        count++;
    }
    return false;
}
int is_possible(vector<array<int, 2>> &traps, int start[2], int exit[2]) {
    trap.clear();
    for(auto &x : traps) {
        trap.insert(x);
    }

    range = traps.size() * traps.size() / 2;
    bool s = BFS(start, exit);
    bool s2 = BFS(exit, start);

    if (s && s2) return 1;
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int start[2], exit_pos[2];
    cin >> start[0] >> start[1] >> exit_pos[0] >> exit_pos[1];

    int T; cin >> T;

    vector<array<int, 2>> traps(T);
    for (int i = 0; i < T; i++) {
        cin >> traps[i][0] >> traps[i][1];
    }
    start_time = chrono::high_resolution_clock::now();

    int result = is_possible(traps, start, exit_pos);
    cout << result << "\n";

    auto end_time = chrono::high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end_time - start_time);
    cout << "Elapsed time: " << duration.count() << " ms\n";

    return 0;
}
