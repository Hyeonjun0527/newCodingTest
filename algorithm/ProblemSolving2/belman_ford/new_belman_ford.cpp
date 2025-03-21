#include <iostream>
#include <vector>
#include <limits.h>
#include <queue>
#include <tuple>
// #include <chrono>
using namespace std;
// using namespace chrono;
vector<long> MD;
int v, query_count, s;
struct Edge {
    int start, end, w;
    Edge(int start, int end, int w) : start(start), end(end), w(w) {}

    bool operator< (const Edge& other) const {

        if (start != other.start) {
            return start > other.start;  // start 기준 오름차순
        } else {
            return w < other.w;  // start가 같으면 w 기준 오름차순
        }

    }
};
priority_queue<Edge> edge_list;
priority_queue<Edge> edge_list_backup;
bool cycle = false;

void algo() {
    MD[s] = 0;
    edge_list_backup = edge_list;
    while (!edge_list.empty()) {
        auto [start, end, w] = edge_list.top();
        edge_list.pop();

        if (MD[start] != LONG_MAX && MD[end] > MD[start] + w) {
            MD[end] = MD[start] + w;
        }
    }
    edge_list = edge_list_backup;
}

void find_cycle() {
    while (!edge_list_backup.empty()) {
        auto [start, end, w] = edge_list_backup.top();
        edge_list_backup.pop();

        if (MD[start] != LONG_MAX && MD[end] > MD[start] + w) {
            cycle = true;
        }
    }
}

// system_clock::time_point start_time;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> v >> query_count;
    // start_time = high_resolution_clock::now();
    MD.resize(v + 1, LONG_MAX);

    for (int i = 0; i < query_count; i++) {
        int start, end, time;
        cin >> start >> end >> time;
        edge_list.emplace(start, end, time);
    }

    s = 1;


    //이건 실패작이였어. 역시 그런 건 나오지 않았어. 내 착각으로부터 비롯된 거였어.
    for (int i = 1; i <= 100 ; i++) {
        algo();
    }
    find_cycle();

    if (!cycle) {
        for (int i = 2; i <= v; i++) {
            if (MD[i] == LONG_MAX)
                cout << -1 << "\n";
            else
                cout << MD[i] << "\n";
        }
    } else {
        cout << -1 << "\n";
    }

    // auto end_time = high_resolution_clock::now();
    // auto duration = duration_cast<milliseconds>(end_time - start_time);
    // cout << "Elapsed time: " << duration.count() << " ms\n";

    return 0;
}
