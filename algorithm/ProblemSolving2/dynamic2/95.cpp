/*
 *
 * 2098번
4
0 10 15 20
5 0 9 10
6 13 0 12
8 8 9 0

35

3
0 1 2
1 0 3
2 3 0
 */
#include <iostream>
#include <vector>
#include <cmath>
#include <bitset> // bitset을 사용하기 위한 헤더
using namespace std;

int INF = 1000000 * 16 + 1;
int v;
int W[16][16];
int D[16][(1 << 16)];

// 현재 상태(curr, visited)에서 TSP 최소 비용을 구하는 재귀 함수
int tsp(int curr, int visited) {
    // 모든 도시를 방문한 경우
    if (visited == (1 << v) - 1) {
        // 시작 도시(0)로 돌아가는 비용 확인
        if (W[curr][0] == 0) {
            return INF;
        } else {
            return W[curr][0];
        }
    }

    // 이미 계산했던 상태라면 메모된 값 반환
    if (D[curr][visited] != 0) {
        return D[curr][visited];
    }

    int min_cost = INF;

    // 방문하지 않은 다음 도시 탐색 0이면 1 2겠지. 0=>1이면 2겠지. 0=>2면 1이겠지.

    for (int next = 0; next < v; next++) {
        // next 미방문 & 경로 존재 visited는 비트마스크야. next번 노드 방문했는지 묻는거야.
        if ((visited & (1 << next)) == 0 && W[curr][next] != 0) {
            int next_visited = visited | (1 << next);
            int cost_to_next = tsp(next, next_visited) + W[curr][next];
            //curr이 먼저 0에서 1로가고 1에서 2로 간다. 그렇게 스택 최대로 쌓이고 이 아래가 실행된다.
            //그때 curr은 2 next는
            // 최소 비용 갱신
            if (cost_to_next < min_cost) {
                min_cost = cost_to_next;
            }
        }
    }
    D[curr][visited] = min_cost;

    cout << "D[" << curr << "][" << bitset<3>(visited) << "] = " << min_cost
     << " (결정됨: 최소 비용 계산 결과)\n";
    return D[curr][visited];
}

int main() {
    cin >> v;
    for (int i = 0; i < v; i++) {
        for (int j = 0; j < v; j++) {
            cin >> W[i][j];
        }
    }
    for (int i = 0; i < v; i++) {
        for (int j = 0; j < v; j++) {
            cout << W[i][j] << " ";
        }
        cout << "\n";
    }

    cout << "[탐색 시작]\n";
    int result = tsp(0, 1); // 시작 도시:0, 시작 상태:1
    cout << "[결과] 최소 비용: " << result << "\n";
}



/*
D[c][v]=min(W[c][i]+D[i][v∣(1≪i)]) i :: 미방문도시
D[next][next_visited] = min(D[next][next_visited], D[curr][visited] + W[curr][next]);
D[curr][visited] = min(D[
현재 위치에서

D[0][1]은 시작점(도시 0)에서 출발하여 모든 도시를 한 번씩 방문하고 다시 시작점으로 돌아오는 최소 비용
[1]은 도시 0만 방문했다는뜻이야. 00001이니까.

우리는 이걸 구하고자 함이야. 그런데 이걸 한번에 구하기 힘들잖아.
그래서 쉬운거부터 구해보자는거야. 그게머냐


처음에 구해지는 D는 이거야
D[1][011]은 현재 위치가 도시 1이고 방문 상태가
011(즉, 도시 0과 도시 1을 이미 방문한 상태)일 때,
남은 도시를 모두 방문하고 출발 도시(0)로 돌아오는 최소 비용이 5
라는 거다.


 */