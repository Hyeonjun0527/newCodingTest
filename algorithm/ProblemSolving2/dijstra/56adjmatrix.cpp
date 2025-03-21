/*
5 6 1
1 2 2
1 3 3
2 3 4
2 4 5
3 4 6
5 1 1

 */

#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
using namespace std;
/*
 *visited 가 필요한건 BFS DFS 프림알고리즘이네

다엑스트라가 필요한건 뭐야? 다엑스트라란? 한 노드에서 다른 노드까지의 최소거리 모두 구하기.

### 방법

1. 선언
노드수, 간선수, 시작노드 / 간선정보 / 큐 / 최소거리배열 / 순서기록배열
(인접리스트는 인접노드,가중치 / 큐는 인접노드 / 인접행렬은 가중)

2. 초기화
간선정보, 큐, 최소거리배열, 순서기록 배열

3. 꺼내고 탐색
꺼내기 : current_node
탐색하기 : next_node, weight, ( 기존 경로 > 새로운 경로 => 최소거리 + 순서기록 + 큐)
(이게 최적가중치 구하는 과정 최소거리 = 최적 가중치)

4. 출력
i, 최소거리, 순서기록

### 특징
인접행렬 vs 인접리스트 : 인접리스트는 인접노드만 돌 수 있어. 인접행렬은 전체노드에서 인접노드 찾아야대.
즉, 인접행렬은 인접리스트와 다르게 인접노드를 찾는 과정이 추가된다.
한 노드를 대상으로 다시 순회(인접노드 순회)하는 일은 없다. 우선순위 큐를 사용하면 그렇다.
인접행렬이 수정되진 않고, (최소거리 + 순서기록 + 큐)가 수정된다.



*/
static int vertices_num, edges_num, start_node;
typedef pair<int, int> Edge; // Edge 타입 정의: 가중치와 노드를 저장하는 pair
static vector<vector<int>> adj_matrix; // 인접 행렬
static priority_queue<Edge, vector<Edge>, greater<Edge>> my_priority_queue; // 우선순위 큐에 Edge 타입 사용
static vector<int> min_distances; // 최소 거리 테이블
static vector<int> previous_node;  // 이전 노드를 저장할 벡터


//여기 우선순위 큐가 굳이 최적가중치를 저장할 필요가 있을까?
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> vertices_num >> edges_num >> start_node;

    // 최소 거리 테이블 초기화 / 0 무시하고 노드번호 1부터 시작해서 vertex + 1만큼 크기 줌.
    // 0번째 column, row는 다 수행끝날 때도 INT_MAX.
    adj_matrix.resize(vertices_num + 1, vector<int>(vertices_num + 1, INT_MAX));
    // 대각선은 0으로 초기화 (자기 자신까지의 거리)
    for (int i = 1; i <= vertices_num; i++) {
        adj_matrix[i][i] = 0;
    }
    // 간선 정보 입력 (방향 그래프)
    for (int i = 0; i < edges_num; i++) {
        int N1, N2, weight;
        cin >> N1 >> N2 >> weight;
        adj_matrix[N1][N2] = weight; // N1에서 N2로의 가중치를 weight로 설정
    }
    // 시작 노드에 대한 초기화
    my_priority_queue.push(start_node); // Edge 타입을 사용해 pair 생성

    min_distances.resize(vertices_num + 1, INT_MAX);
    min_distances[start_node] = 0;

    previous_node.resize(vertices_num + 1, -1); // 초기값 -1로 설정
    //4개를 다 초기화한다고 생각하면 되고 다 초기화 했어.

    while (!my_priority_queue.empty()) {
        //꺼내기 : current_node
        // 큐에서 최소 가중치 노드 꺼내기
        int current_node = my_priority_queue.top();
        my_priority_queue.pop();

        //인접노드 탐색 : next_node, weight
        // 현재 노드의 인접 노드 탐색 am[a][b] 가 a에서 b로가는 가중치. a고정 b는 전부.
        for (int next_node = 1; next_node <= vertices_num; next_node++) {
            //현재노드에서 다음노드로 가는 가중치 = 현재 한 다리 가중치
            int weight = adj_matrix[current_node][next_node];
            // 인접노드 찾고, 기존경로 > 현재경로 업데이트
            if (weight != INT_MAX &&
                min_distances[next_node] > min_distances[current_node] + weight) {
                //최소거리
                min_distances[next_node] = min_distances[current_node] + weight;
                //순서기록 : 다음 노드의 이전 노드는 현재 노드야.
                previous_node[next_node] = current_node; // 이전 노드 저장
                //큐 : 최적가중치, 인접노드(다음 노드 가야지)
                my_priority_queue.push(next_node);
            }
        }
    }

    // 결과 출력 : i, min_distance, previous_node
    // i, min_distance, previous_node 출력해야지
    for (int i = 1; i <= vertices_num; i++) {
        if (min_distances[i] == INT_MAX) {
            //못가는 곳이면 순서기록 배열은 의미가 없어.
            /*
            시작노드가 1일때 previous_node[1]도 -1이고
            시작노드1에서 노드5를 못가면 previous_node[5]도 -1이야
             */
            cout << "1 to " << i << ": INF\n";
        } else {
            cout << "1 to " << i << ": " << min_distances[i] << "\n";
            cout << "순서: ";
            int node = i;
            while (node != -1) {
                cout << node << " ";
                node = previous_node[node];
            }
            cout << "\n";
        }
    }
}
