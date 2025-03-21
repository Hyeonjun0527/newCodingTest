/*
기존의 그래프 문제에서는 노드가 추상적인 공간에서 존재하여 자유롭게 연결되었을 수 있지만,
지금의 문제는 2차원 미로라는 구체적인 공간에서 노드들이 좌표로 표현됨
이를 통해 노드들이 2차원 공간 안에서 제한된 방식으로만 연결될 수 있게 된 것.
기존의 노드는 추상적이고 자유롭게 연결될 수 있는 개념이었지만,
2차원 미로에서의 노드는 물리적인 좌표로 제한되며,
상하좌우 인접 노드로만 연결되는 방식으로 축소
 */

#include <iostream>
#include <queue>
#include <vector>
using namespace std;

vector<int> dx = {0, 1, 0, -1}; // 동, 남, 서, 북
vector<int> dy = {1, 0, -1, 0};
vector<vector<int>> adj_list(101, vector<int>(101)); // 누적 거리를 기록 (뎁스)
vector<vector<bool>> visited(101, vector<bool>(101, false)); // 방문 기록
int v, query_count;
void BFS(int node_x, int node_y);
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> v >> query_count;

    for (int i = 0; i < v; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < s; j++) {
            adj_list[i][j] = s[j] - '0';
        }
    }

    BFS(0, 0);
    cout << adj_list[v-1][query_count-1] << "\n";
}
// 방문 출력 순회
//푸시 방문 팝 출력 순회

//BFS라는건 한 노드의 인접노드가 다다다닥 있으면 걔내 전부다 우선순위 큐에 넣고
//큐에서 나오면
void BFS(int node_x, int node_y) {  // BFS 구현
    queue<pair<int, int>> myQueue ;
    myQueue.push(make_pair(node_x, node_y));
    visited[node_x][node_y] = true;

    while (!myQueue.empty()) {
        // now 배열 대신 nodeX와 nodeY로 사용
        int currentNodeX = myQueue.front().first;
        int currentNodeY = myQueue.front().second;
        myQueue.pop();

        for (int direction = 0; direction < 4; direction++) {
            int nextNodeX = currentNodeX + dx[direction];
            int nextNodeY = currentNodeY + dy[direction];

            if (nextNodeX >= 0 && nextNodeY >= 0 && nextNodeX < v && nextNodeY < query_count) { // 좌표 유효성 검사
                if (adj_list[nextNodeX][nextNodeY] != 0 && !visited[nextNodeX][nextNodeY]) { // 미방문 정점 검사
                    visited[nextNodeX][nextNodeY] = true;
                    adj_list[nextNodeX][nextNodeY] = adj_list[currentNodeX][currentNodeY] + 1; // depth update
                    myQueue.push(make_pair(nextNodeX, nextNodeY));
                }
            }
        }
    }
}
