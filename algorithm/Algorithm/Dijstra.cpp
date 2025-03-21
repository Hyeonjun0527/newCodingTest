#include <iostream>
#include <vector>
#include <limits>

using namespace std;

struct Edge {
    int start;
    int end;
};

// 다익스트라 알고리즘 구현
void dijkstra(int numNodes, const vector<vector<double>>& weights, vector<Edge>& shortestPathTree) {
    int nearestNode;
    vector<int> previousNode(numNodes + 1);  // 최단 경로에서 현재 노드에 도달하기 직전의 노드
    vector<double> minDistance(numNodes + 1); // 시작 노드로부터 각 노드까지의 최소 거리
    const double INF = numeric_limits<double>::infinity();

    shortestPathTree.clear(); // 최단 경로 트리 결과 집합 초기화

    // 초기화
    for (int i = 2; i <= numNodes; i++) {
        previousNode[i] = 1;                // 1번 노드에서 출발
        minDistance[i] = weights[1][i];     // 1번 노드에서 각 노드로 가는 초기 거리
    }

    // (numNodes - 1)번 반복
    /*
    왜 numNodes - 1번 반복이야?
    다익스트라 알고리즘이 시작 노드에서 다른 모든 노드로 가는 최단 경로를 찾을 때
    (전체 노드 수 - 1)개의 간선만 추가하면 충분하기 때문

     */
    for (int step = 0; step < numNodes - 1; step++) {
        double min = INF;//min은 매 반복마다 최소값을 찾기 위해 INF로 초기화됩니다
        //이 루프가 끝날 때는 이번 반복에서 방문할 가장 가까운 노드까지의 거리를 가져.
        // 방문하지 않은 노드 중 최소 거리를 가진 노드를 찾기
        //아직 방문하지 않은 노드들 중에서 시작 노드로부터 가장 가까운 노드를 찾는 과정
        //방문한 노드는 minDistance 값이 -1로 설정돼. 그래서 0이상이라는 말은. 아직 방문하지 않았다는 말이야.

        //가장 가까운 노드를 찾는 과정은 모든 노드를 대상으로 탐색해야 합니다. 그 이유는 각 노드까지의 최단 거리가 계속 업데이트되기 때문에, 모든 노드를 확인하지 않으면 가장 가까운 노드를 놓칠 수 있기 때문입니다.

        
        for (int i = 2; i <= numNodes; i++) {
            //방문했는지 아닌지 && 현재까지 발견된게 min이고, minDistance[i]는 지금
            if (minDistance[i] >= 0 && minDistance[i] < min) {//min은 처음에 무조건 무한이야. 그런데 한번 for문 돌면.
                //지금까지의 minDistance겠지. 즉,
                min = minDistance[i];
                nearestNode = i;
            }
        }
        // 최단 경로 트리에 추가할 간선 생성
        Edge edge;
        edge.start = previousNode[nearestNode];
        edge.end = nearestNode;
        shortestPathTree.push_back(edge);

        // minDistance와 previousNode 배열 업데이트
        for (int i = 2; i <= numNodes; i++) {
            if (minDistance[nearestNode] + weights[nearestNode][i] < minDistance[i]) {
                minDistance[i] = minDistance[nearestNode] + weights[nearestNode][i];
                previousNode[i] = nearestNode;
            }
        }
        minDistance[nearestNode] = -1; // 방문한 노드로 표시
    }
}

int main() {
    int numNodes = 5; // 노드 수
    vector<vector<double>> weights(numNodes + 1, vector<double>(numNodes + 1, numeric_limits<double>::infinity()));

    // 가중치 행렬 weights 초기화 (예시 그래프 예시그래프는 무방향그래프로 주어졌어.)
    weights[1][2] = 3; weights[1][3] = 10;
    weights[2][1] = 3; weights[2][4] = 5;
    weights[3][1] = 10; weights[3][4] = 6; weights[3][5] = 15;
    weights[4][2] = 5; weights[4][3] = 6; weights[4][5] = 4;
    weights[5][3] = 15; weights[5][4] = 4;

    // 무방향 그래프이므로 가중치 행렬을 대칭으로 설정
    // 이미 예시가 무방향이라 이거 필요없는 코드긴 해.
    for (int i = 1; i <= numNodes; i++) {
        for (int j = 1; j <= numNodes; j++) {
            if (weights[i][j] != numeric_limits<double>::infinity()) {
                weights[j][i] = weights[i][j];
            }
        }
    }

    vector<Edge> shortestPathTree;
    dijkstra(numNodes, weights, shortestPathTree);

    // 결과 출력
    cout << "Shortest Path Tree Edges:\n";
    for (const auto& edge : shortestPathTree) {
        cout << edge.start << " -> " << edge.end << "\n";
    }

    return 0;
}
