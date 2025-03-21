/*
4 4 2 1
1 2
1 3
2 3
2 4

4

모든 도로의 길이는 1이야.
도시개수 도로개수 거리정보 출발도시번호
N       M      K       X
4       4       2       1
M개 줄.
단방향
최단거리가 K인 도시를 전부 출력(오름차) 없으면 -1

 */


#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

void BFS(int node,int k);

static vector<vector<int>> adj_list;
static vector<int> answer;
static vector<int> visited;//방문여부와 최단거리 저장

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    long N, M, K, X;
    cin >> N >> M >> K >> X;
    adj_list.resize(N + 1);
    visited.resize(N + 1);
    for (int i = 0; i < M; i++) {
        int node1, node2;
        cin >> node1 >> node2;
        adj_list[node1].push_back(node2);
    }
    for (int i = 0; i <= N; i++) {
        visited[i] = -1;
    }
    BFS(X, K);
    // for (int i = 0; i <= N; i++) {
    //     if (visited[i] == K) {
    //         answer.push_back(i);
    //     }
    // } BFS로 옮겼음


    if (answer.empty()) {
        cout << -1 << "\n";
    }else {
        sort(answer.begin(), answer.end());
        for (int temp : answer) {
            cout << temp << "\n";
        }
    }

    return 0;
}

void BFS(int node, int k) {
    queue<int> queue;
    queue.push(node);
    visited[node] = 0;//출발 노드는 거리가 0이야.

    while (!queue.empty()) {
        int currentNode = queue.front();
        queue.pop();
        for (int nextNode : adj_list[currentNode]) {
            if (visited[nextNode] == -1) {
                visited[nextNode] = visited[currentNode] + 1;

                if (visited[nextNode] == k) {
                    answer.push_back(nextNode);
                }

                queue.push(nextNode);
            }
        }
    }
}