/*
플루이드
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

얘는 1 based야.
//처음에는 이렇게 싹다 단순 가중치를 넣어줘. 그런데 업데이트식으로 넣어. 문제조건에서 중복해서 s e 가 들어갈 수 있대나 머라나.


1. 입력 2. 초기화 3. 입력 4. 로직 5. 출력
*/



#include <iostream>
#include <vector>
#include <limits.h>
#include <tuple>
using namespace std;
int v, e;
vector<vector<long>> MD;
int main()
{
    ios::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    cin >> v >> e;
    MD.resize(101);

    for (int i = 1; i <= v; i++)
        for (int j = 1; j <= v; j++)
            if (i == j) MD[i][j] = 0;
            else MD[i][j] = LONG_MAX;

    for (int i = 0; i < e; i++) {
        int s, e, w;
        cin >> s >> e >> w;
        if (MD[s][e] > w) MD[s][e] = w;
    }

    for (int k = 1; k <= v; k++)
        for (int i = 1; i <= v; i++)
            for (int j = 1; j <= v; j++)
                MD[i][j] = min(MD[i][j],MD[i][k] + MD[k][j]);

    for (int i = 1; i <= v; i++)
        for (int j = 1; j <= v; j++)
            if (MD[i][j] == LONG_MAX) cout << "INF \n";
            else cout << MD[i][j] << " \n";

}