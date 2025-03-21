/*

7
 1 6
 6 3
 3 5
 4 1
 2 4
 4 7
 */

#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
using namespace std;

static int v;
static vector<int> answer;
static vector<bool> visited;
static vector < vector <int> > adj_tree;
void DFS(int number, int number2);

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> v;

    visited.resize(v + 1);
    adj_tree.resize(v + 1);
    answer.resize(v + 1);

    for (int i = 1; i < v; i++) {
        int n1, n2;
        cin >> n1 >> n2;
        adj_tree[n1].push_back(n2);
        adj_tree[n2].push_back(n1);
    }

    DFS(1,0);	// 루트 노드에서 DFS 실행
    for (int i = 2; i <= v; i++) {
        cout << answer[i] << "\n";
    }
}

void DFS(int currentNode,int parentNode) {
    if (visited[currentNode]) return; // 이미 방문한 경우 종료
    visited[currentNode] = true;      // 방문 처리
    answer[currentNode] = parentNode; // 부모노드 기록하기
    // cout << currentNode << " ";
    for (int nextNode : adj_tree[currentNode]) {
        DFS(nextNode, currentNode); // 방문하지 않은 인접 노드에 대해 재귀 호출
    }
}
