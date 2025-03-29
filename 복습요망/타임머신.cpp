#include <iostream>
#include <climits>
#include <vector>

using namespace std;

long v, e, s = 1;

struct Edge{
    long start;
    long end;
    long w;
    Edge(long start, long end, long w): start(start), end(end), w(w) {};
};

vector<Edge> edge_list;
vector<long> MD;
bool cycle = false;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> v >> e;

    for (long i = 0; i < e; i++)
    {
        long start, end, w;
        cin >> start >> end >> w;
        edge_list.emplace_back(start, end, w);
    }
    MD.resize(v+1,LONG_MAX);
    MD[s] = 0;

    for (long i = 0; i < v-1; i++)
    {
        for (auto &[start, end, w] : edge_list)
        {
            if (MD[start] != LONG_MAX && MD[end] > MD[start] + w)
            {
                MD[end] = MD[start] + w;
            }
        }
    }
    //1번 >> 2번~v번노드

    for (auto &[start, end, w] : edge_list)
    {
        if (MD[start] != LONG_MAX && MD[end] > MD[start] + w)
        {
            cycle = true;
        }
    }

    if(!cycle){
        for (int i = 2; i <= v; i++)
        {
            if (MD[i] == LONG_MAX) {
                cout << -1 << "\n";
            } else {
                cout << MD[i] << "\n";
            }
        }
    } else {
        cout << "-1";
    }
}