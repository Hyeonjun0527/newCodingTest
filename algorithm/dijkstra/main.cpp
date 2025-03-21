#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max(); // 무한대 값 설정

// 노드의 개수, 간선의 개수
int n, m;
vector<pair<int, int>> graph[100001]; // 그래프 정보 저장
int min_distance[100001]; // 최단 거리 테이블

void dijkstra(int start) {
    // 우선순위 큐 사용. (거리, 노드 번호)
    //(3,C)는 어디를 얼마나 거쳐가든 상관없이 A에서 C로가는 최소거리가 3이라는거야
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // 시작 노드로 가기 위한 최단 경로는 0으로 설정하고, 큐에 삽입

    pq.push({0, start});
    min_distance[start] = 0;
    cout << "시작 노드: " << start << "\n";

    while (!pq.empty()) {
        // 가장 최단 거리가 짧은 노드에 대한 정보 꺼내기
        int dist = pq.top().first;
        int node = pq.top().second;
        pq.pop();
        cout << "우선순위 큐에서 꺼낸 노드: " << node << " (거리: " << dist << ")\n";

        // 최단 거리 확정
        cout << "노드 " << node << "의 최단 거리가 확정됨: " << dist << "\n";

        // 현재 노드가 이미 처리된 적이 있는 노드라면 무시 (기존 최단거리테이블값 vs 꺼낸거도 시작~거기까지의 최소거리)
        //집에서 상가까지 가는 거리가 10이야. 이미 저장했어. 그런데 집에서 공원갔다가 상가가는 거리가 15야 = dist 그런 경우에 무시해.
        if (min_distance[node] < dist) {
            cout << "노드 " << node << "는 이미 처리됨. (최단 거리: " << min_distance[node] << ")\n";
            continue;
        }

        //
        // 현재 노드와 연결된 다른 인접한 노드들을 확인
        //집에서 상가나 공원으로 갈 수 있으면 둘 다 확인 해.
        //집 > 상가가 10분거리였었어. 그런데 집 > 공원 > 상가가 8분거리야. 그러면 갱신해. 그리고 더 짧은 거리 갱신됐잖아.
        //그러니 상가를 큐에 넣어 그리고 상가에서 어디로 갈 수 있는지 확인해.
        // 현재 노드와 연결된 다른 인접한 노드들을 확인
        for (int nextNode = 0; nextNode < graph[node].size(); nextNode++) {
            int next = graph[node][nextNode].first;
            int cost = dist + graph[node][nextNode].second; // 현재 노드를 거쳐서 다른 노드로 이동하는 거리
            //얘는 현재위치를 통하여 간다고 가정했을때의 최소거리 결과cost야.

            cout << "현재 노드 " << node << " -> 인접 노드 " << next << " (새 경로 거리: " << cost << ")\n";

            if (cost < min_distance[next]) {
                cout << "최단 거리 갱신: " << next << "번 노드까지의 거리 " << min_distance[next] << " -> " << cost << "\n";
                min_distance[next] = cost;
                pq.push({cost, next});
                cout << next << "번 노드를 우선순위 큐에 추가 (거리: " << cost << ")\n";
            }
        }
    }
}

int main() {
    cout << std::unitbuf;//디버그모드로 볼 때 바로 플러시 할 수 있도록 함.
    cin >> n >> m; // 노드 개수와 간선 개수 입력받기
    int start;
    cin >> start; // 시작 노드 번호 입력받기

    // 최단 거리 테이블을 모두 무한대로 초기화
    fill(min_distance, min_distance + 100001, INF);

    // 간선 정보 입력받기
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        graph[a].push_back({b, c});
    }

    // 다익스트라 알고리즘을 수행
    dijkstra(start);

    // 모든 노드로 가기 위한 최단 거리를 출력
    for (int i = 1; i <= n; i++) {
        if (min_distance[i] == INF) {
            cout << "INFINITY" << endl; // 도달할 수 없는 경우
        } else {
            cout << min_distance[i] << endl; // 도달할 수 있는 경우 거리 출력
        }
    }

    return 0;
}

/*
6 11
1
1 2 2
1 3 5
1 4 1
2 3 3
2 4 2
3 2 3
3 6 5
4 3 3
4 5 1
5 3 1
5 6 2

이건 그래프에 들어간다. 우선순위 큐에 그대로 들어가지 않는다.
 */
