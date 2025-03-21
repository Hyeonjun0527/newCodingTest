#include <array>
#include <iostream>
#include <queue>
#include <unordered_set>
#include <cmath>
#include <chrono>
using namespace std;
using namespace chrono;

struct PairHash {
    size_t operator()(const pair<int, int>& p) const {
        return static_cast<size_t>(p.first) * 31 + p.second;
    }
};

int bound(int x, int y, int ex, int ey) {
    return abs(ex - x) + abs(ey - y);
}

system_clock::time_point start_time;
struct Node {
    int f; // f = g + w * h
    int g;
    int x, y;

    bool operator<(const Node& other) const {
        return f > other.f;
    }
};

int is_possible(vector<array<int, 2>> &traps, int start[2], int exit[2]) {
    start_time = high_resolution_clock::now();
    unordered_set<pair<int, int>, PairHash> visited_set;
    unordered_set<pair<int, int>, PairHash> trap_set;

    const double w = 1.2;

    for (auto &t : traps) {
        trap_set.insert({t[0], t[1]});
    }

    priority_queue<Node> pq;
    pq.push({bound(start[0], start[1], exit[0], exit[1]), 0, start[0], start[1]});

    int dx[8] = {1, -1, 0, 0, 1, 1, -1, -1};
    int dy[8] = {0, 0, 1, -1, 1, -1, 1, -1};



    while (!pq.empty()) {

        auto current_time = high_resolution_clock::now();
        auto elapsed = duration_cast<milliseconds>(current_time - start_time).count();
        if (elapsed > 9000) return 0;

        auto current = pq.top(); pq.pop();
        int current_g = current.g;
        int current_x = current.x, current_y = current.y;

        pair<int, int> current_pos = {current_x, current_y};
        if (visited_set.count(current_pos)) continue;
        visited_set.insert(current_pos);

        if (current_x == exit[0] && current_y == exit[1]) {
            return 1;
        }

        // 대각선 우선 이동
        for (int i = 4; i < 8; i++) {
            int nx = current_x + dx[i];
            int ny = current_y + dy[i];

            if (nx < 0 || nx > 999999 || ny < 0 || ny > 999999) continue;

            pair<int, int> new_pos = {nx, ny};

            // 대각선 이동 가능한지 확인
            pair<int, int> check1 = {current_x + dx[i], current_y};
            pair<int, int> check2 = {current_x, current_y + dy[i]};
            if (trap_set.count(check1) || trap_set.count(check2)) continue;

            if (trap_set.count(new_pos)) continue;

            if (!visited_set.count(new_pos)) {
                int new_g = current_g + 1;
                int h = bound(nx, ny, exit[0], exit[1]);
                int new_f = new_g + static_cast<int>(w * h);
                pq.push({new_f, new_g, nx, ny});
            }
        }

        for (int i = 0; i < 4; i++) {
            int nx = current_x + dx[i];
            int ny = current_y + dy[i];

            if (nx < 0 || nx > 999999 || ny < 0 || ny > 999999) continue;

            pair<int, int> new_pos = {nx, ny};

            if (trap_set.count(new_pos)) continue;

            if (!visited_set.count(new_pos)) {
                int new_g = current_g + 1;
                int h = bound(nx, ny, exit[0], exit[1]);
                int new_f = new_g + static_cast<int>(w * h);
                pq.push({new_f, new_g, nx, ny});
            }
        }
    }

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

    int result = is_possible(traps, start, exit_pos);
    cout << result << "\n";

    auto end_time = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end_time - start_time);
    cout << "Elapsed time: " << duration.count() << " ms\n";

    return 0;
}
