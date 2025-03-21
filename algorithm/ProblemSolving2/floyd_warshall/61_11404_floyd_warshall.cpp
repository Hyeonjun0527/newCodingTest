/*
5
14
1 2 2
1 3 3
1 4 1
1 5 10
2 4 2
3 4 1
3 5 1
4 5 3
3 5 10
3 1 8
1 4 2
5 1 7
3 4 2
5 2 4

0 2 3 1 4
12 0 15 2 5
8 5 0 1 1
10 7 13 0 3
7 4 10 6 0
*/
/*
인접행렬을 초기화 할 때 N^2의 시간복잡도가 걸린다.
하지만 플루이드 워셜 알고리즘을 돌릴때 3중 중첩 루프가 있다. 그러므로 시간복잡도는 N^3이다.
*/



#include <iostream>
#include <vector>
#include <limits.h>
#include <tuple>
using namespace std;
int N, M;
long D[101][101];//i에서 j로 가는 모든 최단거리.
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> M;

    //대각선 같은거만 0이고 나머지는 전부 높은수로 초기화.
    for (int i = 1; i <= N; i++) { // 인접 행렬 초기화
        for (int j = 1; j <= N; j++) {
            if (i == j)
                D[i][j] = 0;//노드1에서 노드1로 가는건 0이야
            else
                D[i][j] = LONG_MAX; // 나머지는 충분히 큰 수로 초기화
        }
    }

    for (int i = 0; i < M; i++) {
        int s, e, v;
        cin >> s >> e >> v;
        //1 4 1들어가고 1 4 2들어갔어. 그러면 1 4 1만 있으면 돼.
        //D[s][e]==기존경로. 더 짧은거 찾으면 저장.
        //업데이트식으로 입력받아
        if (D[s][e] > v) D[s][e] = v;
    }
    for (int k = 1; k <= N; k++) { // 플로이드 워셜 알고리즘 수행
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                D[i][j] = min(D[i][j],D[i][k] + D[k][j]);
                // Ak[i][j] = min(Ak-1[i][j], Ak-1[i][k] +Ak-1[k][j]
                //왜 Ak가 D로만 표현되고 k는 표현이 안되도 될까? 덮어쓰기 때문이야.
                // A0 A1 A2 A3... Ak를 직접 저장하지 않고 하나의 공간을 계속 재활용하는거야.
                //각 단계에서 이전상태와 현재상태만 고려하면 되는 경우는 하나의 공간을 계속 재활용할 수 있어.
                ////각 단계에서 이전상태와 현재상태만 고려하면 되는 경우는 중간 결과를 계속 덮어쓰며 갱신하여 최종 결과를 얻어 내.
            }
        }
    }
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (D[i][j] == 10000001) cout << "INF ";
            else cout << D[i][j] << " ";
        }
        cout << "\n";
    }
}