#include <iostream>
#include <queue>
#include <vector>
using namespace std;
int n, m, k, l;
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
struct Node {
    int x;
    int y;
    bool visited;
    int t;
};
struct NN {
    int x;
    int y;
};

void bfs() {
    queue<Node> q;
    while (!q.empty()) {
        auto [cx, cy, visited] = q.front();
        q.pop();
        if (visited)
            continue;
        for (int i = 0 i < 4; i++) {
            nx = cx + dx[i];
            ny = cy + dy[i];
            if (nx < 0 && nx > n && ny < 0 && ny > m)
                continue;

            q.push(nx, ny)
        }
    }
}

int calc_t(vector<NN> K, Node node) {
    int sum = 0;
    for (int i = 0; i < K.size(); i++) {
        sum += abs(node.x - K[i].x) + abs(node.y - K[i].y);
    }
    return sum;
} // 맨해튼거리도출

int main() {

    cin >> n >> m >> k >> l;
    vector<NN> K(k);
    for (int i = 0; i < k; i++) {
        int x;
        int y;
        cin >> x;
        cin >> y;
        K[i] = {x, y}; ////TODO
    }
}