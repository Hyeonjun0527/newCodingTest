#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

typedef pair<int, int> edge;
static vector < vector <edge> > A;
static vector<bool> visited;
static vector<int> m_distance;
void BFS(int node);

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N;
    cin >> N;
    A.resize(N + 1);

    for (int i = 0; i < N; i++) {
        int S;
        cin >> S;
        while (true)
        {
            int E, V;
            cin >> E;
            if (E == -1)break;
            cin >> V;
            A[S].push_back(edge(E, V));
        }
    }

    m_distance = vector<int>(N + 1, 0);
    visited = vector<bool>(N+1, false);
    BFS(1);
    int Max = 1;
    for (int i = 2; i <= N; i++) {
        if (m_distance[Max] < m_distance[i])
            Max = i;
    }
    fill(m_distance.begin(), m_distance.end(), 0); // 거리 배열 초기화
    fill(visited.begin(), visited.end(), false); // 방문 배열 초기화
    //시작 노드에서 제일 먼저 가장 먼 점을 찾아. depth 길이 가장 긴거 찾아.
    //시작 노드에서 제일 가장 먼 점은 지름이 아니야. 하지만 찾았던 제일 가장 먼 점은 반드시 끝단에 있지.
    //그 특성을 이용하면 그 제일 가장 먼 점이랑 그 점의 제일 먼 점을 찾아. 그럼 걔도 끝단에 있어.
    //그래서 그 depth를 리턴하면 답이야
    //그리고 그 점에서 제일 먼 점을 찾기 가장 디스턴스 먼 Max번호의 노드를 찾았어.
    BFS(Max);
    sort(m_distance.begin(), m_distance.end());
    cout << m_distance[N] << "\n";
}

//푸시 방문 팝 출력 재귀
void BFS(int index) {  // BFS구현
    queue<int> myqueue;
    myqueue.push(index);
    visited[index] = true;

    while (!myqueue.empty()) {
        int currentNode = myqueue.front();
        myqueue.pop();
        for (edge nextNode : A[currentNode]) {//A : first - 정점 번호, second 가중치
            if (!visited[nextNode.first]) {
                visited[nextNode.first] = true;
                myqueue.push(nextNode.first);
                m_distance[nextNode.first] = m_distance[currentNode] + nextNode.second;
            }
        }
    }
}