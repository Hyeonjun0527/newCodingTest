/*
이분 그래프
2
3 2 >> 정점수 간선수
1 3 >> 간선정보
2 3 >> 간선정보
4 4 >> 정점수 간선수
1 2 >> 간선정보
2 3 >> 간선정보
3 4 >> 간선정보
4 2 >> 간선정보

YES
NO
K개의 줄에 걸쳐 입력으로 주어진 그래프가 이분 그래프이면 YES, 아니면 NO를 순서대로
출력한다
사이클이 발생하지 않으면 이분 그래프로 나눌 수 있음
• 사이클 : 특정 노드에서 출발하여 다시 같은 노드로 돌아오는 경로

DFS를 실행할 때 현재 노드에서 연결된 노드 중 이미 방문한
노드가 이 전 노드와 같은 집합이면 이분 그래프가 아님

같은 그룹의 노드들끼리 연결이 있으면 안 되는 것이 이분 그래프의 규칙
이분 그래프의 정의를 색칠 문제로 표현하면:
이분 그래프는 두 개의 집합으로 나눌 수 있는 그래프입니다. 즉, 빨강 그룹과 파랑 그룹으로 나눌 수 있는 그래프입니다.
그래프의 **모든 변(간선)**이 빨강 그룹의 꼭짓점과 파랑 그룹의 꼭짓점을 연결합니다.
같은 색의 꼭짓점들끼리는 서로 연결되지 않고, 항상 다른 색의 꼭짓점들끼리만 연결됩니다.
이 조건을 만족하는 그래프가 이분 그래프입니다.

v1 -- v2
|     |
v4 -- v3
이런것도 이분그래프야. 왜냐면 네 네모 저거를 비튼다고 생각해봐
v1    v3
| \  / |
|   /\ |
|  / \  |
v4    v2 이런 모양 되겠지. 이런 모양이면 이분그래프잖아.
A 한쪽에 두고 B 저쪽에 두고 선 쭉쭉 연결한거 이분그래프

 */

#include <iostream>
#include <vector>
using namespace std;

void DFS(int node);

static vector<vector<int>> adj_list;
static vector<bool> check;
static vector<bool> visited;
static bool IsEven;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N;
    cin >> N;

    for (int t = 0; t < N; t++) {
        int V, E;
        cin >> V >> E;
        adj_list.resize(V + 1);
        visited.resize(V + 1);
        check.resize(V + 1);
        IsEven = true;
        for (int i = 0; i < E; i++) {
            int S, E;
            cin >> S >> E;
            adj_list[S].push_back(E);
            adj_list[E].push_back(S);
        }

        for (int i = 1; i <= V; i++) {
            if (!visited[i]) {
                DFS(i);
            }
            if (!IsEven) break;
        }

        if (IsEven) {
            cout << "YES" << "\n";
        } else {
            cout << "NO" << "\n";
        }

        for (int i = 0; i <= V; i++) {
            adj_list[i].clear();
            visited[i] = false;
            check[i] = false;
        }
    }
}

void DFS(int node) {
    visited[node] = true;
    for (int nextNode : adj_list[node]) {
        if (!visited[nextNode]) {
            check[nextNode] = !check[node]; // 현재 노드와 다른 그룹으로 할당
            // check[nextNode] = (check[node] + 1) % 2;//1 0 1 0 이렇게 들어가겠지.
            //이건 check가 int라면.. 만약 3가지 집합으로 하거나 그런 경우에 3그룹으로 나눌 수 있곘다
            DFS(nextNode);
        } else if (check[node] == check[nextNode]) {  // 같은 그룹인데 연결되어 있으면 이분 그래프가 아님
            IsEven = false;
        }
    }
}
