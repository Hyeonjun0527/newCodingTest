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

int v, e, query_count;
int level = 1;
int now_count = 0;
int now_max_count = 1;
vector<vector<int>> adj_tree;
vector<int> depth;
vector<int> mom;
vector<bool> visited;
void BFS(int node) {
    queue<int> q;
    q.emplace(node);
    visited[node] = true;
    while (!q.empty()) {
        int current_node = q.front(); q.pop();
        for (int next_node : adj_tree[current_node]) {
            if (visited[next_node]) continue;
            visited[next_node] = true;
            q.emplace(next_node);
            mom[next_node] = current_node;  //부모 노드 저장
            depth[next_node] = level; //노드 depth 저장
        }
        now_count++;
        if (now_count == now_max_count) {
            now_count = 0;
            now_max_count = q.size();
            level++;
        }
    }
}
int find_lca(int a, int b) {
    if (depth[a] < depth[b]) {
        int temp = a;
        a = b;
        b = temp;
    }// 두 노드의 Depth 맞춰주기// 같은 조상이 나올 때까지 한칸씩 올려주기
    while (depth[a] != depth[b]) a = mom[a];
    while (a != b) a = mom[a], b = mom[b];
    return a;
}

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
