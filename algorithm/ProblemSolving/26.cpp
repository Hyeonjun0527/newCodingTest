
/*
4 5 1
 1 2
 1 3
 1 4
 2 4
 3 4

1 2 4 3
1 2 3 4
N,M,Start, s,e 양방향, 작은 번호부터 방문
*/

#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

vector<vector<int>> adj_list;
vector<bool> visited;

void DFS(int node);
void BFS(int node);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N, M, Start;
    cin >> N >> M >> Start;
    adj_list.resize(N + 1);
    visited.resize(N + 1, false);

    // 그래프 초기화, 양방향이니까 두번씩 넣어줌
    for (int i = 0; i < M; i++) {
        int start, end;
        cin >> start >> end;
        adj_list[start].push_back(end);
        adj_list[end].push_back(start);
    }


    // 번호 작은 것부터 방문해야 해. 그러러면 정렬
    // 노드 번호가 1부터 시작한다.
    for (int node = 1; node <= N; node++) {
        sort(adj_list[node].begin(), adj_list[node].end());
    }


    DFS(Start);

    cout << "\n";
    fill(visited.begin(), visited.end(), false);

    BFS(Start);
    return 0;
}

// DFS 구현 (스택 기반)
// 재귀함수는 원래 스택을 사용하는데 반대로 사용해. 재귀를 스택으로 구현하려면 반대가 되어야해.
//왜냐면 재귀함수는 A B C를 순서대로 방문해.
//함수 호출이 곧 스택에 노드를 푸시하는 것과 같아.
//스택으로 하려면 C B A를 넣어야 A B C를 순서대로 방문해. 꺼낼때 방문하니까.

//1쨰 while문 : 1방문처리. 1의 인접노드인 2 스택에 넣기.
//2째 while문 : 2방문처리. 2의 인접노드인 1스킵, 4스택에 넣기
//3째 while문 : 4방문처리. 4의 인접노드 없으니 pop
//4쨰 while문 : 2선택. 방문처리스킵. 2의 인접노드 없느니 pop
//5째 whlie문 : 1선택. 방문처리스킵. 1의 인접노드인 3 스택에 넣기
//원래 방문했는지 여부 검사는 중복적으로 발생해.
//1방문했니? 1방문했니? 1방문했니?
/*스택
 * 1
 * 1 2
 * 1 2 4
 * 1 2
 * 1 3
 */


//(푸시) (확인하고 방문처리) (하나씩 인접노드 순회 - 다돌면 꺼냄)

//푸시하고 확인하고 방문처리하고 하나씩 인접노드 순회한다. 다돌면 꺼낸다.
//DFS는 푸시하고 나서 cout하고 BFS는 팝하고 나서 cout 한다.
void DFS(int node) {
    //1. 푸시
    stack<int> nodeStack;
    nodeStack.push(node);

    //2.  방문처리

    /*
     1 > 2 3 4
     2 > 1 4
     3 > 1 4
     야.
     Start = 1이니까. 1방문하고 2
     */
    while (!nodeStack.empty()) {
        //컬너트노드
        int currentNode = nodeStack.top();//현재 상태

        //1을 방문해 현재노드를 방문하고
        if (!visited[currentNode]) {
            visited[currentNode] = true; // 방문 처리
            cout << currentNode << " ";
        }

        //2,3,4를 순회 해. 2를 푸시해. 다음 노드를 방문해.
        bool isAllVisited = true;//다 방문했니?
        //3. 하나씩 순회
        for (int nextNode : adj_list[currentNode]) {
            //이 if문이 실행하면 pop을 하지 않고 넘어가.
            //다음 처리 ::
            if (!visited[nextNode]) {
                nodeStack.push(nextNode);//다음상태로 넘어가기
                isAllVisited = false;//다 방문하지 않았음을 알림.
                break; // 한 번에 하나의 자식 노드만 스택에 푸시
            }
        }

        // 방문하지 않은 자식 노드가 없으면(모두 방문했다면) 스택에서 팝
        if (isAllVisited) {
            nodeStack.pop();
        }
    }
}


/*
푸시하고 / 확인하고 방문처리 / 하나씩 인접노드 순회 - 다 돌면 꺼냄
1 > 2 3 4
2 > 1 4
3 > 1 4
4 > 1 2 3

## [0. 공집합]
1을 스택에 푸시하고 확인하고 방문처리
## [1. DFS(1)]
1의 인접노드인 2를 스택에 푸시
## [2. DFS(1) DFS(2)]
2를 방문처리하고 2에서 1은 이미 방문했으니 푸시안함
## [3. DFS(1) DFS(2)]
2에서 4를 스택에 푸시
## [4. DFS(1) DFS(2) DFS(4)]
4를 방문처리하고 4에서 인접노드 모두 방문했으니 4를 팝한다.
## [5. DFS(1) DFS(2)]
2에서 모든 인접노드 방문했으니 2를 팝한다.
## [6. DFS(1)]
1의 인접노드인 3을 스택에 푸시
## [7. DFS(1) DFS(3)]
3을 방문처리하고 3의 인접노드 모두 방문했으니 3을 팝한다.
## [8. DFS(1)]
1의 인접노드인 4를 스택에 푸시
## [9. DFS(1) DFS(4)]
4의 인접노드 모두 방문 했으니 4를 팝한다.
## [10. DFS(1)]
1의 인접노드 모두 방문 했으니 1을 팝한다.
## [11. 공집합]

결론 : 방문 순서는 1 > 2 > 4 > 3 이다. 첫 푸시 = 방문순서

5.DFS(1) DFS(2)
DFS(1) DFS(3)
DFS(1) DFS(3)
푸시하기
확인하기 V
방문처리하기 V
꺼내기 V
하나씩 순회하기V

재귀함수에서 for문으로 재귀함수 호출하면 하나씩 Deep하게 순회하는거야.

 */

//재귀함수는 호출이 끝나면 자동으로 이전 함수 호출
    //push와 pop을 제어
// (푸시) (확인하고 방문처리) (하나씩 인접노드 순회 - 뎁스끝까지 가고 꺼냄(뎁스 끝까지 가고 스택메모리해제))
//이 파라미터의 node가 nodeStack.top()인거야. currentNode가 파라미터인거야.
//그리고 재귀함수에 있다는게 while문 안에 있는거야.
void DFS2(int node) {
    //(확인)
    if (visited[node]) return;
    //(방문처리 방문하면 출력 처음으로 방문하자마자 출력)
    visited[node] = true;
    cout << node << " ";
    for (int nextNode : adj_list[node]) {
        // if (!visited[nextNode])    DFS(nextNode);//푸시 하나씩 순회
        //if를 여기 넣어도 되고 저기 넣어도 됨.
        DFS2(nextNode);
    }
}

// BFS 구현
/*
 1 > 2 3 4
 2 > 1 4
 3 > 1 4
 야.
 Start = 1이니까. 1방문하고 2
 */

/*
[간선정보]
1 > 2 3 4
2 > 1 4
3 > 1 4
4 > 1 2 3
[큐]
1
2 3 4
3 4
4
x
[심층 분석]
큐 : 공집합
1을 푸시하고 방문처리 해.
큐 : 1
1을 꺼내고 출력해.
큐 : 공집합
1의 인접노드 2 3 4를 확인해. 방문 안한 2와 3과 4를 푸시하고 방문처리해.
큐 : 2 3 4
2를 꺼내고 출력해.
큐 : 3 4
2의 인접노드 1과 4를 확인해. 푸시하고 방문처리할 게 없어.
큐 : 3 4
3을 꺼내고 출력해
큐 : 4
3의 인접노드 1과 4를 확인해. 푸시하고 방문처리할 게 없어.
큐 : 4
4를 꺼내고 출력해.
큐 : 공집합
4의 인접노드를 1과 2와 3을 확인해. 푸시하고 방문처리할 게 없어.
 */

//(푸시하고) (확인하고 방문처리) (하나씩 인접노드 순회) (다 돌면 꺼냄)
//(푸시하고 즉시 방문처리) (꺼내고 출력하고) (한번에 인접노드 순회)


//DFS :: 푸시하고 /확인/방문 및 출력// 다돌면 꺼내   / 하나씩 인접노드 순회
//BFS :: 푸시하고 /미리 방문처리/꺼내고 출력해      / 한번에 인접노드 순회.


//BFS는 큐에 넣을때 방문처리하고, 꺼낼때 출력해. DFS는 방문처리할때 출력해.

//BFS는 방문 순서가 레벨이잖아. 그러니까 큐에 인접노드 싹 다 넣어. 그리고 인접노드 아직 방문 안했지만, 싹다 방문처리해.
//지금 방문 계획을 세우기 위해 방문처리해놓는거야. 큐에 넣으면 어차피 무조건 방문할거니까 미리 방문처리해도 문제 없겠지.
//큐에 넣을 때 방문처리를 해야 뭘 방문할 지 계획을 세울 수 있겠지. 큐에 넣는 걸 방문할거니까, 방문계획은 큐에 넣을 때 해야 되는거야.
//큐는 방문 계획이야. 실제로 꺼낼 때 방문하는 거기는 해.

//중요한 특징 : DFS BFS는 중복방문이 없어.

//나는 큐에 넣은걸 꺼낼때마다 이동(방문)할거야. 그래서 큐에 넣을때 중복해서 안들어가게 visited[true] 방문했다고 표시를 먼저 해.
void BFS(int node) {
    queue<int> node_queue;
    node_queue.push(node);
    visited[node] = true;
    //DFS랑 다르게 모든 노드를 한번만 푸시해. DFS는 여러번 노드를 푸시.
    //그래서 DFS는 방문처리하기 전에 if문이 필요해.

    while (!node_queue.empty()) {
        int current_node = node_queue.front();//현재 상태
        node_queue.pop();
        cout << current_node << " ";

        // 한방에 2,3,4를 큐에 넣어. 싹다 방문처리해.
        // 2꺼내고 2의 인접노드 1 4 싹다 방문처리 확인해.
        // ...
        // 인접 노드들을 탐색 (작은 번호부터 방문)
        for (int next_node : adj_list[current_node]) {
            if (!visited[next_node]) {
                node_queue.push(next_node);//다음 상태로 넘어가기
                visited[next_node] = true;
            }
        }
    }
}

// DFS 재귀 : 1. 방문하고 출력 2. 하나씩 순회해.
// BFS     : 1. 푸시하고 방문 2. (현재상태) 팝하고 출력해. 3. 한번에 순회
//    방문   출력 순회
//푸시 방문 팝 출력 순회


//DFS는 여러번 푸시 / 첫 푸시하는 순서가 방문 순서 / 첫 푸시 = 방문
//BFS는 한번만 푸시 / 팝하는 순서가 방문 순서 / 푸시 = 방문 약속, 계획

//초기 필요 정보 : A, visited

//--------------------------------------------------------------------------
// DFS는 스택에 넣을떄 방문출력을 하고
// BFS는 큐에서 꺼낼때 방문출력을 하네?
// DFS는 계획이 없고 BFS는 계획이 있네?