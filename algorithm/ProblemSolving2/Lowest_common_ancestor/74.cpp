/*트리에서임의의두노드를선택했을때,
두노드가각각자신을포함해거슬러올라가면서탐색할때
처음공통으로만나게되는부모노드를최소공통조상(LCA,
Lowest Common Ancestor)라고 함

1. 트리의 정의
트리는 다음과 같은 특징을 가진 연결 그래프입니다:

**모든 정점(Vertex)**이 연결되어 있습니다. → 연결 그래프
사이클이 존재하지 않습니다.
간선의 개수는 반드시
정점의 수
−
1
정점의 수−1입니다.

15
 1 2
 1 3
 2 4
 2 5
 2 6
 3 7
 3 8
 4 9
 4
 10
 7 1
 1
 7 1
 8
 1
 2
 3
 8
 8
 14
 15
 3
 6 11
 10 9
 2 6
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int v, e, query_count;//v : 노드의 개수
int level = 1;
int now_count = 0;
int now_max_count = 1;
vector<vector<int>> adj_tree;//세그먼트 트리는 1차원이야. 얘는 인접리스트이면서 트리야. 그래서 2차원. 트리니까 e = v - 1; 그리고 사이클 없음 보장
vector<int> depth;
vector<int> mom;
vector<bool> visited;
int find_lca(int a, int b);
void BFS(int node);

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> v;
    e = v - 1;

    adj_tree.resize(v + 1);
    depth.resize(v + 1);
    mom.resize(v + 1);
    visited.resize(v + 1);
    for (int i = 0; i < e; i++) { // A인접리스트 트리에 그래프 데이터 저장
        int start, end;
        cin >> start >> end;
        adj_tree[start].emplace_back(end);
        adj_tree[end].emplace_back(start);
    }
    BFS(1); // depth를 BFS를 통하여 구하기
    cin >> query_count;
    for (int i = 0; i < query_count; i++) {
        // 공통 조상을 구할 두 노드
        int a, b;
        cin >> a >> b;
        int LCA = find_lca(a, b);
        cout << LCA << "\n";
    }
}
/*
 *
* 먼저 루트노드에서탐색해각노드의부모노드와깊이를저장함
• 탐색은DFS와 BFS를 사용하면 됨
depth가 b가 더 크면 a와 b값을 교환해
왜냐? 두 노드 𝑎와 𝑏의 **깊이(depth)**를 맞춰야 할 때
더 깊은 노드를 기준으로 조상을 따라 올라가는 것이 더 간단하기 때문.
1. 즉, a가 항상 더 깊은 노드가 되도록 보장
2. 뎁스 같게 만들어야 함. 그래서 같을때까지 a의 뎁스를 줄여.(a > a의 부모 > a의 부모의 부모 이렇게 a에 덮어씌우면서 depth[a]와 depth[b]비교.
3. 같은 조상 나올때까지 반복하면 됨.

 */

int find_lca(int a, int b) {
    if (depth[a] < depth[b]) {
        int temp = a;
        a = b;
        b = temp;
    }
    while (depth[a] != depth[b]) { // 두 노드의 Depth 맞춰주기
        a = mom[a];
    }
    while (a != b) { // 같은 조상이 나올 때까지 한칸씩 올려주기
        a = mom[a];
        b = mom[b];
    }
    return a;
}
// BFS구현
/*
이 코드는 BFS (너비 우선 탐색) 알고리즘을 사용하여 트리의 노드별 부모 노드와 **깊이(depth)**를 계산하는 함수입니다.
먼저 루트노드에서탐색해 각노드의부모노드와깊이를저장함
• 탐색은DFS와 BFS를 사용하면 됨
mom[] 배열 depth[]을 채워준다.

현재 레벨에 있는 노드를 탐색할 때마다 count를 1 증가시킵니다.
현재 레벨에 있는 모든 노드를 탐색했는지를 확인

now_max_count: 현재 레벨의 노드 개수입니다.
now_count: 현재 레벨의 탐색이 완료된 노드의 개수입니다.
이 조건이 참이면, 현재 레벨의 모든 노드를 처리했다는 의미입니다.

now_size = q.size():
다음 레벨에 있는 노드의 개수를 계산합니다.
현재 큐에 들어있는 노드들은 다음 레벨의 노드들입니다.
 */
void BFS(int node) {
    queue<int> q;
    q.emplace(node);
    visited[node] = true;
    while (!q.empty()) {
        int current_node = q.front();
        q.pop();
        for (int next_node : adj_tree[current_node]) {
            if (!visited[next_node]) {
                visited[next_node] = true;
                q.emplace(next_node);
                mom[next_node] = current_node;  //부모 노드 저장
                depth[next_node] = level; //노드 depth 저장
            }
        }
        now_count++;
        if (now_count == now_max_count) {
            now_count = 0;
            now_max_count = q.size();
            level++;
        }
    }
}


/*
BFS는 큐에 넣을때 visited[] = true를 해 / 큐에서 노드를 꺼낸다는 것은 해당 노드를 방문하고, 그 노드의 인접 노드를 탐색
다익스트라는 큐에서 꺼냈을때 visited[] = true / 큐에서 노드를 꺼낸다는 것은 해당 노드의 최단 거리가 확정되었다는 의미입니다. 더 이상 이 노드는 다른 경로로 업데이트될 필요가 없다
DFS는 노드를 방문한 직후 visited = true

왜 그런 차이가 있을까?
 */