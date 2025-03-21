#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

void BFS();
static int Sender[] = {0, 0, 1, 1, 2, 2};// 0 : A , 1 : B , 2 : C // from_node
static int Receiver[] = {1, 2, 0, 2, 0, 1};//6개의 케이스 정의한거야. // to_node
static bool visited[201][201];  //A B의 무게만 있으면 C의 무게가 고정되므로 2개로만 체크 가능
static bool answer[201]; // A 물통이 비었을 때, C 물통에 남아 있을 수 있는 물의 양
static int capacity_ABC[3]; // A B C 물의 양을 용량

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> capacity_ABC[0] >> capacity_ABC[1] >> capacity_ABC[2];
    BFS();
    
    for (int i = 0; i < 201; i++) {
        if (answer[i]) cout << i << " ";
    }
}

void BFS() {
    queue<pair<int,int>> Queue;// A 물통에 있는 물의 양 B 물통에 있는 물의 양 이게 노드야.
    Queue.push(make_pair(0,0));
    visited[0][0] = true;
    answer[capacity_ABC[2]] = true;
    while (!Queue.empty()) {
        pair <int, int> p = Queue.front();
        Queue.pop();
        int A = p.first;
        int B = p.second;
        int C = capacity_ABC[2] - A - B; // C는 전체 물의 양에서 A와 B를 빼준 것 // A ,B, C도 노드야. 변수명만 바꾼거야.
        for (int k = 0; k < 6; k++) { // A->B, A->C, B->A, B->C, C->A, C->B 6개의 케이스로 이동
            int next[] = { A, B, C };// 현재 A, B, C 물통의 상태를 next[] 배열에 복사해 놓고 물 부을 거야. {숫자,숫자,숫자} 있겠지.
            next[Receiver[k]] += next[Sender[k]];//첫번째 케이스면 next[1]+=next[0]가 되겠지. B에 A를 더하는거야.
            //가독성이 좀 별로야 다른 방법 있을 것 같은데. k를 반복하는게 아니라
            next[Sender[k]] = 0;//
            if (next[Receiver[k]] > capacity_ABC[Receiver[k]]) { // 대상 물통의 용량보다 물이 많아 넘칠 때
                // 초과하는 만큼 다시 이전 물통에 넣어줌
                next[Sender[k]] = next[Receiver[k]] - capacity_ABC[Receiver[k]];
                next[Receiver[k]] = capacity_ABC[Receiver[k]]; // 대상 물통은 최대로 채워줌
            }
            if (!visited[next[0]][next[1]]) { // A와 B의 물의 양을 통하여 방문 배열 체크
                visited[next[0]][next[1]] = true;
                Queue.push(make_pair(next[0], next[1]));
                if (next[0] == 0) {  // A의 물의 양이 0일때 C의 물의 무게를 정답 변수에 저장
                    answer[next[2]] = true;
                }
            }
        }
    }
}