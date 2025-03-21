#include <iostream>
#include <queue>
#include <unordered_set>
#include <cmath>
#include <chrono>
using namespace std;
using namespace chrono;

static long long encode_to_position(int x, int y) {
    return static_cast<long long>(x) * 1000000LL + static_cast<long long>(y);
}

bool isValid(int x, int y, unordered_set<long long> &traps) {
    if (x < 0 || x > 999999 || y < 0 || y > 999999) return false;
    if (traps.find(encode_to_position(x, y)) != traps.end()) return false;
    return true;
}

int bound(int x, int y, int ex, int ey) {
    return abs(ex - x) + abs(ey - y);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int sx, sy, ex, ey;
    cin >> sx >> sy >> ex >> ey;

    int T;
    cin >> T;

    unordered_set<long long> traps;
    for (int i = 0; i < T; i++) {
        int tx, ty;
        cin >> tx >> ty;
        traps.insert(encode_to_position(tx, ty));
    }

    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};

    auto cmp = [](const pair<int, long long> &a, const pair<int, long long> &b) {
        return a.first > b.first;
    };
    priority_queue<pair<int, long long>, vector<pair<int, long long>>, decltype(cmp)> pq(cmp);
    unordered_set<long long> visited;

    pq.push({bound(sx, sy, ex, ey), encode_to_position(sx, sy)});
    visited.insert(encode_to_position(sx, sy));

    auto start_time = high_resolution_clock::now();

    while (!pq.empty()) {
        auto current = pq.top();
        pq.pop();

        long long curKey = current.second;
        int currentX = (int)(curKey / 1000000);
        int currentY = (int)(curKey % 1000000);

        if (currentX == ex && currentY == ey) {
            cout << 1 << "\n";
            auto end_time = high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(end_time - start_time);
            cout << "Elapsed time: " << duration.count() << " ms\n";
            return 0;
        }

        for (int i = 0; i < 4; i++) {
            int nx = currentX + dx[i];
            int ny = currentY + dy[i];

            if (!isValid(nx, ny, traps)) continue;

            long long nextKey = encode_to_position(nx, ny);
            if (visited.find(nextKey) == visited.end()) {
                visited.insert(nextKey);
                int nextHeuristic = bound(nx, ny, ex, ey);
                pq.push({nextHeuristic, nextKey});
            }
        }
    }

    cout << 0 << "\n";
    auto end_time = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end_time - start_time);
    cout << "Elapsed time: " << duration.count() << " ms\n";

    return 0;
}



/*
0 0 999999 999999
5
500000 500000
400000 400000
600000 600000
700000 300000
300000 700000
 */