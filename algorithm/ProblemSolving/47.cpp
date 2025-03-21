


/*
answer배열은 신뢰도배열이야.
이 배열에서 가장 높은 값을 가진 인덱스를 출력해야대.
그런데 배열에서 가장 높은 값을 가진 인덱스가 여러개일 수 있어서 여러개 출력해야대 오름차순으로.

그건 그렇고 중요한건 왜 각 노드마다 BFS탐색을 하고,
그 중에 방문할때마다 더해서 신뢰도 배열을 만드냐야.

각 노드마다 간선방향으로 탐색을 하게 하고 가장 많이 방문된게 신뢰도 높은거야.

단방향이면 DFS BFS가 하나도 탐색을 못할 수도 있다는 거도 배웠다.

5 4
3 1 3을 1을 신뢰한다.
3 2
4 3
5 3

5가 3을 신뢰한다. 3이 1을 신뢰한다.
4가 3을 신뢰한다. 3이 1을 신뢰한다.
4 -> 3 이런 단방향 그래프라고 볼 수 있어.


1 2 ( 가장 많은 컴퓨터 해킹할 수 있는 컴퓨터 번호 출력)
방문되었다는건 신뢰도가 높다는 얘기야. 다른 노드에서 도착했다는거니까.

각 노드를 시작점으로 BFS를 돌려서
그 노드가 얼마나 많은 다른 노드에 도달할 수 있는지를 계산합니다.
왜 각 노드마다 BFS를 돌리는가:
그래프가 단방향이기 때문에

양방향 그래프에서는 특정 노드에서 탐색을 한 번만 수행해도
다른 모든 노드에 대한 연결 가능성을 충분히 파악

단방향 그래프에서 각 노드마다 BFS를 돌리고, 그 결과를 기반으로 answer 배열에 신뢰도를 누적

단방향 : 출발점에 따라 탐색범위가 달라짐 방향성 때문에 노드마다 돌려야함.
양방향 : 커넥티드 그래프가 아니라면 각 노드마다 돌려야함.

단방향은 언제나 각 노드마다 돌려야 모든 정보를 얻을 수 있고,
양방향은 커넥티드 그래프라면 한 노드만으로 모든 정보를 얻을 수 있어?

1. 신뢰도 누적
2. 최대 depth 깊이 저장
이렇게 풀 수 있지 않나? 그렇게 풀 수 없다.
최대 깊이 3짜리가 1을 신뢰한다고 하자.
그렇다고 하더라도 최대 깊이 1짜리 4개가 2를 신뢰한다면 2가 더 신뢰도가 높다.

신뢰도 높다 = 많은 노드에서 그 노드로 도달할 수 있다 = 즉 깊이와 관련이 없다.
 */


#include <bits/stdc++.h>
using namespace std;

void BFS(int node);

vector<vector<int>> adj_list;
vector<int> answer;
vector<bool> visited;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    long N, M;
    cin >> N >> M;
    adj_list.resize(N + 1);
    answer.resize(N + 1);
    visited.resize(N + 1);

    for (int i = 0; i < M; i++) {
        int node1, node2;
        cin >> node1 >> node2;
        adj_list[node1].push_back(node2);
    }

    for (int i = 0; i <= N; i++) {
        fill(visited.begin(),visited.end(),false);
        BFS(i);
    }
    int maxVal = 0;
    for (int i = 1; i <= N; i++) {
        maxVal = max(maxVal, answer[i]);
    }
    for (int i = 1; i <= N; i++) {
        if (answer[i] == maxVal) {
            cout << i << " ";
        }
    }
}
//방문 출력 순회
//1. 푸시 2. 방문 3. 팝 4. 출력 5. 순회
void BFS(int node) {
    queue<int> queue;
    queue.push(node);
    visited[node] = true;

    while (!queue.empty()) {
        int currentNode = queue.front();
        queue.pop();
        for (int nextNode : adj_list[currentNode]) {
            if (!visited[nextNode]) {
                visited[nextNode] = true;
                answer[nextNode]++;
                queue.push(nextNode);
            }
        }
    }

}
