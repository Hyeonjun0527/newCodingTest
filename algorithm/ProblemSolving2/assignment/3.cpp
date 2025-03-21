/*
인접행렬을 초기화 할 때 N^2의 시간복잡도가 걸린다.
플루이드 워셜 알고리즘을 돌릴때 3중 중첩 루프가 있다.
전부 1~N까지 순회하므로
총 시간복잡도는 N^3이다.
그러므로 10의 6제곱정도로 수행하기에 문제가 없다.
*/



#include <iostream>
#include <vector>
#include <limits.h>
#include <tuple>
using namespace std;
static int v, query_count;
static long MD[101][101];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> v >> query_count;

    for (int i = 1; i <= v; i++) { // 인접 행렬 초기화
        for (int j = 1; j <= v; j++) {
            if (i == j)
                MD[i][j] = 0;//노드1에서 노드1로 가는건 0이야
            else
                MD[i][j] = 10000001; // 나머지는 충분히 큰 수로 초기화
        }
    }

    for (int i = 0; i < query_count; i++) {
        int s, e, v;
        cin >> s >> e >> v;
        //1 4 1들어가고 1 4 2들어갔어. 그러면 1 4 1만 있으면 돼.
        //D[s][e]를 기존경로로 봐보면? 더 짧은거 찾으면 저장해야되니까..
        if (MD[s][e] > v) MD[s][e] = v;
    }
    for (int k = 1; k <= v; k++) { // 플로이드 워셜 알고리즘 수행
        for (int i = 1; i <= v; i++) {
            for (int j = 1; j <= v; j++) {
                MD[i][j] = min(MD[i][j],MD[i][k] + MD[k][j]);
            }
        }
    }
    for (int i = 1; i <= v; i++) {
        for (int j = 1; j <= v; j++) {
            if (MD[i][j] == 10000001) cout << "INF ";
            else cout << MD[i][j] << " ";
        }
        cout << "\n";
    }
}