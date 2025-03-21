//백준 53번


/*
3 2
1 3
2 3

1 2 3
 */
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int v, query_count;
vector<vector<int>> adj_list;// 다음 노드를 담는 adj_list이다. 만약 다익스트라였으면 가중치도 저장한 Edge 객체.
vector<int> indegree;
void BFS() {
    queue<int> q;
    for (int i = 1; i <= v; i++) if (indegree[i] == 0) q.emplace(i);
    while (!q.empty()) {
        int current_node = q.front(); q.pop();
        cout << current_node << " ";
        for (int next_node : adj_list[current_node]) {
            indegree[next_node]--;
            if (indegree[next_node] == 0) q.emplace(next_node);
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> v >> query_count;
    adj_list.resize(v + 1);
    indegree.resize(v + 1);
    for (int imm = 0; imm < query_count; imm++) {
        int start, end;
        cin >> start >> end;
        adj_list[start].emplace_back(end);
        indegree[end]++; // 진입차수 배열 데이터 저장하기
    }
     // 위상 정렬 수행 먼저 디그리 0인거 넣어.
    BFS();
}

/*
이웃노드의 진입차수를 하나 줄여. 왜냐하면 그렇게 되다가 진입차수가 0이 되면 그 노드를 방문할 수 있는 선행조건이 완료된거야.
그리고 큐에 넣어. 큐에 넣는게 방문한다는 거야.
이 문제는 사이클 없는 방향그래프에서 선행순서를 위반하지 않으면서 모든 노드를 순서대로 정렬하는거야.
* */