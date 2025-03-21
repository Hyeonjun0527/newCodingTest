#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <algorithm> // for max function

using namespace std;

int main() {
    int v;
    cin >> v;

    // 그래프를 담을 구조: 인접 리스트, 진입 차수, 작업 시간을 하나의 튜플로 묶음
    vector<tuple<vector<int>, int, int>> graph(v + 1);

    // 그래프 정보 입력
    for (int i = 1; i <= v; i++) {
        int t;
        cin >> t;  // 각 작업의 시간을 입력 받음
        get<2>(graph[i]) = t;  // 작업 시간 저장 (tuple의 세 번째 요소)

        while (true) {
            int x;
            cin >> x;  // 각 노드에 연결된 간선 정보 입력
            if (x == -1) break; // -1을 입력받으면 종료

            get<0>(graph[x]).push_back(i); // 인접 리스트에 연결된 노드 정보를 추가 (tuple의 첫 번째 요소)
            get<1>(graph[i]) += 1;         // 진입 차수 증가 (tuple의 두 번째 요소)
        }
    }

    // 위상 정렬 함수
    vector<int> result(v + 1, 0); // 결과를 저장할 배열
    queue<int> q;                 // 큐 생성

    //result(강의를 듣기 위한 최소 시간) 초기화 + 큐에 진입차수 0 삽입
    //result테이블은 각각 노드에 대한 강의를 듣기 위한 최소시간이다. 연결된 노드가 없으면 그 자체, 연결된게잇으면 간선 건너기마다 최대강의시간
    for (int i = 1; i < v + 1; i++) {
        result[i] = get<2>(graph[i]);  // 초기값으로 각 작업 시간 설정
        if (get<1>(graph[i]) == 0) {
            q.push(i);
        }
    }

    // 큐가 빌 때까지 반복 위상정렬 - 모든 노드를 방향대로 한번씩 탐색함.
    while (!q.empty()) {
        int now = q.front();
        q.pop();

        // 현재 노드와 연결된 노드들의 진입 차수에서 1 빼기
        // now : 대상 노드 번호 i : 연결된 노드의 번호
        //연결된 노드 번호의 작업시간 + 현재 노드의 작업시간
        for (int i : get<0>(graph[now])) { // 인접 리스트 탐색 연결된 노드를 다 탐색하기
            result[i] = max(result[i], result[now] + get<2>(graph[i])); // 최대값 갱신
            get<1>(graph[i]) -= 1;  // 진입 차수 감소(간선 제거)

            // 새롭게 진입 차수가 0이 되는 노드를 큐에 삽입
            if (get<1>(graph[i]) == 0) {
                q.push(i);
            }
        }
    }

    // 위상 정렬을 수행한 결과 출력
    for (int i = 1; i <= v; i++) {
        cout << result[i] << endl;
    }

    return 0;
}
