/*
어디 PDF : 11.pdf 최소스패닝트리
어디 백준 : 다리만들기 2 17472번

이 문제를 보면

모든 섬을 다리로 연결하래

모든 섬을 다리로 연결하는거래. 다리의 비용 최소로 연결.

모든 노드를 최소로 가중치로 연결하는 게, 바로 MST 최소 스패닝 트리이다.
크루스칼알고리즘은 모든 간선을 최소로 정렬하고, 모든 간선을 한번 순회하는 알고리즘이야
ElogE의 시간복잡도야.
우선순위 큐를 써도 힙은 완전이진트리구조야. 트리 높이는 logE야. 그래서 한번 삽입할때
자기 원소의 위치를 찾아야지 트리높이 다 비교해야지. 그래서 한 번 삽입할 때 logE 시간 복잡도 걸려.
 */

#include <bits/stdc++.h>
using namespace std;

void my_union(int a, int b);
int find(int a);
void BFS(int node_x, int node_y);

int dx[] = { -1, 0, 1, 0 };
int dy[] = { 0, 1, 0, -1 };
int my_map[101][101];//지도
bool visited[101][101] = { false, };//지도의 방문 여부 DFS/BFS할 때 사용
vector<int> parent;//parent[i]는 i가 속한 집합의 대표 노드를 가리키며, find와 union 연산에 사용
int N, M, island_num;
vector < vector <pair<int, int>> > all_island;
vector <pair<int, int>>  island;

typedef struct Edge 	// 에지정보 struct 생성, 가중치 값 기준 오름차순 정렬로 설정
{
    int startNode, endNode, weight;
    bool operator< (const Edge& temp) const {
        return weight > temp.weight;
    }//가중치 최소힙 우선순위 큐.
};

// static priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
priority_queue<Edge> all_bridge;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> M;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> my_map[i][j]; 	// 맵 정보 저장
        }
    }
    island_num = 1;

    //N x M번 반복을 해
    //먼저 섬을 분리할거야. 섬만을 찾을거야.
    for (int i = 0; i < N; i++) { 	// 각 자리에서 BFS 탐색을 이용하여 섬들을 분리하여 줍니다.
        for (int j = 0; j < M; j++) {//bfs함수는 총 섬의 개수만큼 실행됨.
            if (my_map[i][j] != 0 && visited[i][j] != true) {
                BFS(i, j);
                island_num++;
                all_island.push_back(island);//각 1,2,3,4번 섬에 대한 좌표(x,y)를 저장
                //섬은 노드야. 모든 노드를 모아. 그리고 탐색알고리즘으로 간선을 만들거야.
            }
        }
    }

    // island_num--;

    // 섬의 각 지점에서 만들 수 있는 모든 간선을 저장
    for (int i = 0; i < all_island.size(); i++) {	//1번섬 2번섬 3번섬...
        vector<pair<int, int>> my_island = all_island[i];
        //하나의 섬의 모든 땅 개수만큼 반복할거야. 모든 땅에 대하여 반복할거야.
        for (int j = 0; j < my_island.size(); j++) { //1번섬의 모든 노드에 대해서 반복..
            int nodeX = my_island[j].first;
            int nodeY = my_island[j].second;
            int node_island_num = my_map[nodeX][nodeY];//현재 주인공 노드의 island_num
            for (int direction = 0; direction < 4; direction++) { 	// 4방향 검색
                int nextNodeX = nodeX + dx[direction];
                int nextNodeY = nodeY + dy[direction];
                int bridge_length = 0;
                // 맵의 경계를 벗어나지 않는 동안 반복 앞으로 가서 다리지어봐...
                while (nextNodeX >= 0 && nextNodeX < N && nextNodeY >= 0 && nextNodeY < M) {
                    //같은 섬이면 바로 멈춰야지. 바다를 향해서 건너야지.
                    if (my_map[nextNodeX][nextNodeY] == node_island_num) 	// 같은 섬이면 간선을 만들 수 없음
                        break;
                    //바다가 아니야. 같은 섬도 아니야. 그러면 다른 섬이지. 그러면 다리 완성인거지.
                    if (my_map[nextNodeX][nextNodeY] != 0) { 	// 같은 섬이 아니고 바다가 아니면
                        if (bridge_length > 1) 	// 다른 섬 -> 길이가 1 이상일 때 간선으로 추가
                            all_bridge.push(Edge{ node_island_num, my_map[nextNodeX][nextNodeY], bridge_length });
                        break;
                    }
                    // 바다라면 다리 길이를 연장
                    bridge_length++;
                    // 다음 위치로 이동
                    nextNodeX += dx[direction];
                    nextNodeY += dy[direction];
                }
            }

        }
    }

    //여기서 island_num은 마지막 섬의 번호야. 동시에 섬의 개수를 의미해.
    parent.resize(island_num);//섬의 개수만큼 공간이 필요해. 섬 4개니까 4개의 공간 필요함.//
    for (int i = 0; i < parent.size(); i++) {
        parent[i] = i;
    }//처음엔 모두 자기 자신이 대표.
    int used_Edge = 0;
    int result = 0;
    //간선은 우선순위큐로 자동정렬되었음.
    while (!all_bridge.empty()) {  	// 최소 신장 트리 알고리즘을 수행하여 줍니다.
        Edge currentEdge = all_bridge.top();
        all_bridge.pop();
        // 같은 부모가 아니라면 -> 연결 가능
        if (find(currentEdge.startNode) != find(currentEdge.endNode)){
            my_union(currentEdge.startNode, currentEdge.endNode);
            result = result + currentEdge.weight;//weight는 여러 다리들 있었잖아. 그 다리의 길이임.
            used_Edge++;
        }
    }
    // 배열에서 쉬운 index 처리를 위해 island_num을 1부터 시작하였으므로
    // 현재 island_num의 값이 섬의 개수보다 1 많은 상태임
    // 때문에 1작은 수가 아닌 2작은 수와 사용 에지를 비교하여 줍니다.
    //섬의 개수 - 2 == 사용된 edge
    //섬의 개수 10개면 used_Edge = 9여야 해. 섬의 개수 10개면 island_num = 11이야.
    if (used_Edge == island_num - 2) {
        cout << result << "\n";
    }
    else {//모든 섬을 연결하는데 실패한 경우
        cout << -1 << "\n";
    }

}

void my_union(int a, int b) { 		// union 연산 : 대표 노드끼리 연결하여 줌
    a = find(a);//a의 대표
    b = find(b);//b의 대표
    if (a != b) {
        parent[b] = a;
        //b의 대표의 대표를 a로 만든다? 어차피 b와 find(b)는 같은 그룹이야.
        //그 그룹의 대표 노드를 a로 만들거야.
    }
}
int find(int a) { 	// find 연산
    if (a == parent[a])//a의 대표를 찾으려고 햇어 근데 a가 대표야. 내가 대표네?
        return a;//그러면 대표 리턴
    else//내가 대표가 아니야 그러면 나의 대표의 대표를 또! find하고 그걸 나의 대표로 저장해.
        //즉 a의 대표가 b고 b의 대표가 c야. 그러면 a의 대표를 c로 하는거지 그게 경로압축.
        return parent[a] = find(parent[a]); 	// 재귀함수의 형태로 구현 -> 경로 압축 부분
}
/*
노드    1 2 3 4 5 6
대표노드 1 1  1 1 1 5
인데 union(4,6)하면 되기는 해 그런데 6의 대표노드 5로 되잇는데 이거 줄줄이 연결되자나
그거 찾아야대? 그게 실치 그래서 5를 1로 바꿔줘 그걸 경로압축.
 */

//nodeX와 nodeY가 반드시 하나의 섬의 일부야. 0이 아니었으니까. 땅이야.
void BFS(int node_x, int node_y) {	 // BFS를 통하여 연결된 섬을 찾아줍니다.
    queue<pair<int, int>> my_queue;
    island.clear();
    //초기화작업으로 첫 노드를 큐에 넣을거야. BFS는 한 노드를 딱 한번 만 푸시하고 팝해.
    my_queue.push(make_pair(node_x, node_y));//처음것은 반드시 처음 방문하는 땅의 일부야.
    island.push_back(make_pair(node_x, node_y));//처음건 무조건 땅이야. 땅 기록.
    //BFS 탐색이 완료되면 mlist에는 하나의 섬을 구성하는 모든 좌표가 들어있습니다.
    visited[node_x][node_y] = true;
    my_map[node_x][node_y] = island_num;//섬의 번호야. 번호를 붙이는 일이야. 1번 섬들은 전부 1로 표시 2번 섬들은 전부 2로 표시.

    while (!my_queue.empty()) {
        //큐에서 꺼낼거야.
        int currentNodeX = my_queue.front().first;
        int currentNodeY = my_queue.front().second;
        my_queue.pop();

        // 4방향으로 인접한 칸을 탐색 노드의 인접노드는 4방향이 다야.
        for (int direction = 0; direction < 4; direction++) {
            int nextNodeX = currentNodeX + dx[direction];
            int nextNodeY = currentNodeY + dy[direction];

            // 경계를 벗어나지 않고, 방문하지 않았으며, 같은 섬의 땅인 경우 list.add
            //맵이 0부터야. 0부터 N-1, 0부터 M-1
            if (nextNodeX >= 0 && nextNodeX < N && nextNodeY >= 0 && nextNodeY < M) {
                if (my_map[nextNodeX][nextNodeY] != 0 && !visited[nextNodeX][nextNodeY]) {
                    //섬이면 해야할 일 : 방문기록하기, 맵에 island_num 기록하기, island만들기, 큐에 넣기
                    visited[nextNodeX][nextNodeY] = true;
                    my_map[nextNodeX][nextNodeY] = island_num;
                    island.push_back(make_pair(nextNodeX, nextNodeY));
                    my_queue.push(make_pair(nextNodeX, nextNodeY));
                }
            }
        }
    }

}