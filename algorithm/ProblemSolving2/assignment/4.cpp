/*
mask가 011이라고 하면 노드0과 노드 1번(i번)이 사용된다는 것이다.
그리고 가능한 순서는 노드 0번이 시작이거나 노드 1번이 시작이다.
그래서 i번을 반복한다.
그리고 j번은 0~k중 비트마스크 상태를 확인했을 때 방문하지 않은 노드들이 된다.즉 노드 2번이다.
mask 는 2^k - 1가지의 종류가 있고,
i와 j가 k번 반복된다.

여기서 보면 i루프가 k번 반복되면 j는 모두 continue가 된다.

최악의 시간복잡도의 상황은 i가 k/2번 반복되는 상황이 된다.

그래서 (2^k - 1) * (k/2) * (k/2) 만큼의 함수가 실행되고 시간복잡도는 O(2^k * k^2)이다.
 */

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

// dist 배열: start에서 여러 도시까지의 최단 거리
vector<int> dist;
//인접리스트
vector<vector<int>> graph;
//필수 방문 도시
vector<int> must_visit;
vector<int> bfs(int start) {
    fill(dist.begin(), dist.end(), INT_MAX);
    queue<int> q;
    dist[start] = 0;
    q.push(start);

    while (!q.empty()) {
        int current_node = q.front();
        q.pop();

        for (int next_node : graph[current_node]) {
            if (dist[next_node] == INT_MAX) {
                dist[next_node] = dist[current_node] + 1;
                q.push(next_node);
            }
        }
    }
    return dist;
}

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    dist.resize(n + 1, INT_MAX);
    graph.resize(n + 1);
    must_visit.resize(k);
    //초기화
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    for (int i = 0; i < k; ++i) {
        cin >> must_visit[i];
    }

    // 필수 방문 도시 i에서 필수 방문 도시 j까지의 최단 거리 미리 계산
    vector<vector<int>> distances(k, vector<int>(k, INT_MAX));
    for (int i = 0; i < k; ++i) {
        vector<int> dist_result = bfs(must_visit[i]);
        dist = bfs(must_visit[i]);//필수도시i에서 다른 모든 도시의 최단거리.
        for (int j = 0; j < k; ++j) {
            distances[i][j] = dist_result[must_visit[j]];//필수도시i에서 필수도시 j까지의 최단거리.
        }
    }

    // 필수 방문 도시를 전부 방문하지 못함ㅁ
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < k; ++j) {
            if (distances[i][j] == INT_MAX) {
                cout << -1 << endl; // 연결되지 않았을때
                return 0;
            }
        }
    }

    //필수 도시 최단거리 계산해야댐(+DP마스크로 상태 표시해야댐)
    int all_visited = (1 << k) - 1; // k=4라면 0000~1111 이런 모든 경우
    vector<vector<int>> dp(1 << k, vector<int>(k, INT_MAX));

    // 초기화 시작점 0~k-1
    for (int i = 0; i < k; ++i) {
        dp[1 << i][i] = 0; // 도시 0,1,2...k-1만 방문했을 때가 초기화임.
    }

    // 비트마스크를 이용하여 모든 상태 탐색
    for (int mask = 0; mask <= all_visited; ++mask) {
    // k = 3이면 mask는 000~111,   011 : 도시 0,1을 방문한 상태 라고 한다면
        for (int i = 0; i < k; ++i) { // i는 현재까지 방문한 마지막 도시. i=0 => 도시1 방문후 도시 0방문
            if (!(mask & (1 << i))) continue;//방문하지 않은 도시는 스킵이야. i=2는 스킵.

            for (int j = 0; j < k; ++j) { // 다음 방문할 도시 j 탐색
                if (mask & (1 << j)) continue; // 마스크가 011이므로 j = 0스킵/  j= 1 스킵/ j= 2를 방문 가능

                int next_mask = mask | (1 << j); // 도시 j를 방문 상태에 추가

                int new_cost = dp[mask][i] + distances[i][j];
                dp[next_mask][j] = min(dp[next_mask][j], new_cost); // 비용 갱신
                //new 비용 = dp[011][0] + distances[0][2]
                //new 비용 = 도시 0,1을 방문한 상태(011상태) 인데 마지막 도시가 0이야. 즉 1->0이야. 거기서 0 -> 2로 가기.
                //new 비용의 후보는 어떻게 만들어질까...?
                //111인 상태에서 마지막 방문 도시가 2일 때의 최소 비용 = min(기존비용 , new 비용 )


                // Ak[i][j] = min(Ak-1[i][j], Ak-1[i][k] +Ak-1[k][j]
                //왜 Ak가 D로만 표현되고 k는 표현이 안되도 될까? 덮어쓰기 때문이야.
                // A0 A1 A2 A3... Ak를 직접 저장하지 않고 하나의 공간을 계속 재활용하는거야.
                //각 단계에서 이전상태와 현재상태만 고려하면 되는 경우는 하나의 공간을 계속 재활용할 수 있어.
                ////각 단계에서 이전상태와 현재상태만 고려하면 되는 경우는 중간 결과를 계속 덮어쓰며 갱신하여 최종 결과를 얻어 내.
            }
        }
    }

    // 모든 도시를 방문한 상태에서 최소 거리 계산
    int result = INT_MAX;
    for (int i = 0; i < k; ++i) {
        //마지막에 채우고자 하는 건 111인 상태에서 마지막 방문 도시가 0,1,2일때의 최소 비용 3개중에 가장 최소
        result = min(result, dp[all_visited][i]);
    }

    cout << result << endl;
    return 0;
}
