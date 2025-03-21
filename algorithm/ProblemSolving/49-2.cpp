#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

void BFS();
static unordered_map<char, int> capacity_ABC;  // A, B, C 물통의 용량
static bool visited[201][201];  // A와 B 물의 양으로 방문 체크
static bool answer[201];  // A가 비었을 때 C에 남아 있을 수 있는 물의 양 기록
// 각 물통 이동 규칙을 정의 ('A' -> 'B', 'A' -> 'C', 'B' -> 'A', 'B' -> 'C', 'C' -> 'A', 'C' -> 'B')
static unordered_map<int, pair<char, char>> moves = {
    {0, {'A', 'B'}}, {1, {'A', 'C'}}, {2, {'B', 'A'}},
    {3, {'B', 'C'}}, {4, {'C', 'A'}}, {5, {'C', 'B'}}
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    // A, B, C 물통의 용량 입력 받음
    cin >> capacity_ABC['A'] >> capacity_ABC['B'] >> capacity_ABC['C'];
    BFS();

    // 답 출력
    for (int i = 0; i < 201; i++) {
        if (answer[i]) cout << i << " ";
    }
}

void BFS() {
    queue<unordered_map<char, int>> Queue;  // 각 물통의 상태(A, B, C)를 저장하는 맵
    Queue.push({ {'A', 0}, {'B', 0}, {'C', capacity_ABC['C']} });  // 초기 상태: A, B는 0, C는 가득 참
    visited[0][0] = true;
    answer[capacity_ABC['C']] = true;  // 처음에는 C 물통이 가득 찬 상태이므로 정답 저장

    while (!Queue.empty()) {
        auto node = Queue.front();
        Queue.pop();

        int A = node['A'];
        int B = node['B'];
        int C = node['C'];

        // 6개의 이동 케이스 처리
        for (int k = 0; k < 6; k++) {
            char from = moves[k].first;   // 물을 보내는 물통
            char to = moves[k].second;    // 물을 받는 물통
            auto nextNode = node;  // 현재 상태 복사

            // 물 옮기기
            nextNode[to] += nextNode[from];  // 받는 물통에 물을 더함
            nextNode[from] = 0;  // 보내는 물통은 물을 비움

            if (nextNode[to] > capacity_ABC[to]) {  // 만약 물통이 넘치면
                nextNode[from] = nextNode[to] - capacity_ABC[to];  // 넘친 물은 다시 보냄
                nextNode[to] = capacity_ABC[to];  // 대상 물통을 최대치로 채움
            }

            if (!visited[nextNode['A']][nextNode['B']]) {  // A와 B의 물의 양으로 방문 체크
                visited[nextNode['A']][nextNode['B']] = true;
                Queue.push(nextNode);

                if (nextNode['A'] == 0) {  // A가 비었을 때 C의 물의 양을 정답에 저장
                    answer[nextNode['C']] = true;
                }
            }
        }
    }
}
