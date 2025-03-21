

/*

5 5
0 1
1 2
2 3
3 0
1 4

1

• 입력
• 첫째 줄에 사람의 수 N (5 ≤ N ≤ 2000)과 친구 관계의 수 M (1 ≤ M ≤ 2000)
이 주어진다.
 • 둘째 줄부터 M개의 줄에는 정수 a와 b가 주어지며, a와 b가 친구라는 뜻이다.
(0 ≤ a, b ≤ N-1, a ≠ b) 같은 친구 관계가 두 번 이상 주어지는 경우는 없다.
 • 출력
• 문제의 조건에 맞는 A, B, C, D, E가 존재하면 1을 없으면 0을 출력한다.

즉 depth = 5 인 것 찾으라는거야. DFS

일부 사람들 간의 친구 관계가 주어졌을 때, 이 관계들이 사실상 하나의 연
결된 그래프를 형성하는지를 판별하는 문제.
• 사람은 그래프의 정점, 친구 관계는 그래프의 간선.
 • A는B와친구다.
 • B는C와친구다.
 • C는D와친구다.
 • D는E와친구다.
 • 이는 A-B-C-D-E가 연결된 하나의 그래프임. 깊이(depth)가 5인 경로를 찾는
것이 목적이며, 이를 찾으려면 그래프 탐색 알고리즘을 사용해야 함
• 깊이를 계산하는 문제이지만, 모든 경로를 탐색할 필요가 없는 문제임
• 깊이 5인 경로가 있는지 여부를 확인하는 문제이므로 BFS 보다 DFS가 더 많이 사용됨.

재귀파라미터 depth
depth를 전역변수로 놓는다는건 수동적으로 관리하겠다는거야.
마치 재귀를 사용하지 않고
스택을 사용해서 현재상태와 다음상태를 수동적으로 관리했던것처럼 말이다.

 */

#include <iostream>
#include <vector>
using namespace std;

static vector < vector <int> > adj_list;
static vector<bool> visited;
static bool arrive;//이건 정답이야.
void DFS(int node, int depth);

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N, M;
    arrive = false;
    cin >> N >> M;

    adj_list.resize(N);
    // visited = vector<bool>(N, false);
    visited.resize(N);

    for (int i = 0; i < M; i++) {
        int s, e;
        cin >> s >> e;
        adj_list[s].push_back(e);
        adj_list[e].push_back(s);
    }

    for (int i = 0; i < N; i++) {
        DFS(i, 1);
        //백트래킹으로 visited 전부 초기화 자동으로 된다.
        if (arrive)
            break;
    }

    if(arrive) cout << 1 << "\n";
    else  cout << 0 << "\n";

}

void DFS(int node, int depth) {
    // if (depth == 5 || arrive) { // 깊이가 5가되면 프로그램 종료
    if (visited[node]) return;
    if (depth == 5) {
        arrive = true;
        return;
    }
    visited[node] = true;
    for (int nextNode : adj_list[node]) {
        DFS(nextNode, depth + 1);
    }
    visited[node] = false;
}
/*
0 > 1 3
1 > 0 2 4
2 > 1 3
3 > 2 0
4 > 1
이거면 DFS를 사용하면 원래
[0]
[0, 1]
[0, 1, 0]           // visited[0] == true, 리턴
[0, 1, 2]
[0, 1, 2, 1]        // visited[1] == true, 리턴
[0, 1, 2, 3]
[0, 1, 2, 3, 2]     // visited[2] == true, 리턴
[0, 1, 2, 3, 0]     // visited[0] == true, 리턴
[0, 1, 2, 3]        // DFS(3) 종료
[0, 1, 2]           // DFS(2) 종료
[0, 1, 4]
[0, 1, 4, 1]        // visited[1] == true, 리턴
[0, 1, 4]           // DFS(4) 종료
[0, 1]              // DFS(1) 종료
[0, 3]              // visited[3] == true, 리턴
[0]                 // DFS(0) 종료

백트래킹을 넣어주면
0 > 1 3
1 > 0 2 4
2 > 1 3
3 > 2 0
4 > 1
[0]
[0, 1]
[0, 1, 0]           // visited[0] == true, 리턴
[0, 1, 2]
[0, 1, 2, 1]        // visited[1] == true, 리턴
[0, 1, 2, 3]
[0, 1, 2, 3, 2]     // visited[2] == true, 리턴
[0, 1, 2, 3, 0]     // visited[0] == true, 리턴
[0, 1, 2, 3]        // DFS(3) 종료, visited[3] = false
[0, 1, 2]           // DFS(2) 종료, visited[2] = false
[0, 1, 4]
[0, 1, 4, 1]        // visited[1] == true, 리턴
[0, 1, 4]           // DFS(4) 종료, visited[4] = false
[0, 1]              // DFS(1) 종료, visited[1] = false
[0, 3]
[0, 3, 2]
[0, 3, 2, 1]
[0, 3, 2, 1, 0]     // visited[0] == true, 리턴
[0, 3, 2, 1, 2]     // visited[2] == true, 리턴
[0, 3, 2, 1, 4]
[0, 3, 2, 1, 4, 1]  // visited[1] == true, 리턴
[0, 3, 2, 1, 4]     // DFS(4) 종료, visited[4] = false
[0, 3, 2, 1]        // DFS(1) 종료, visited[1] = false
[0, 3, 2, 3]        // visited[3] == true, 리턴
[0, 3, 2]           // DFS(2) 종료, visited[2] = false
[0, 3, 0]           // visited[0] == true, 리턴
[0, 3]              // DFS(3) 종료, visited[3] = false
[0]                 // DFS(0) 종료, visited[0] = false

....
 */