
/*
 *
5 6
5 1 1
1 2 -2
1 3 3
2 3 -4
2 4 5
3 4 6
 */
//못가는건 -1로 출력해.  사이클 있으면 -1만 출력해. 가는건 최소경로 출력해.
//백준 11657
//얘는 1차원이였다는거
#include <iostream>
#include <vector>
#include <limits.h>
#include <tuple>
using namespace std;
vector<long> MD;
int v, e, s;
struct Edge {
    int start, end, w;
    Edge(int start, int end, int w) : start(start), end(end), w(w) {}
};
vector<Edge> edge_list;
bool cycle = false;
void algo() {
    MD[s] = 0;// 아래처럼 단일 문장으로 가능해
    for (int imm = 1; imm <= v - 1; imm++)
        for (auto& [start, end, w] : edge_list)
            if (MD[start] != LONG_MAX &&
                MD[end] > MD[start] + w)
                MD[end] = MD[start] + w;
}
void find_cycle() { // 얘도 단일 문장으로 가능해.
    for (auto& [start, end, w] : edge_list)
        if (MD[start] != LONG_MAX &&
            MD[end] > MD[start] + w)
            cycle = true;
}
int main()
{
    ios::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    cin >> v >> e; s = 1;
    MD.resize(v + 1, LONG_MAX);
    for (int i = 0; i < e; i++) {
        int start, end, w;
        cin >> start >> end >> w;
        edge_list.emplace_back(start, end, w);
    }
    algo();
    find_cycle();
    if (!cycle) {
        for (int i = 2; i <= v; i++) {
            if (MD[i] == LONG_MAX) {
                cout << LONG_MAX << "\n";
            }
            else {
                cout << MD[i] << "\n";
            }
        }
    }else {
        cout << -1 << "\n";
    }
    return 0;
}
// edge_list.resize(v + 1, Edge(0, 0, 0)); 얘는 명시적 초기화 안해도 돼. 그런데 vector<vector<Edge>> adj_list는 명시적 초기화 해줘야 돼. 왜냐하면 adj_list[?]는 동적으로 할당 못해주거든.