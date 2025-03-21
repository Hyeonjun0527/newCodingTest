/*
백준 11657번 assignment 5번도 확인하기

5 6
5 1 1
1 2 2
1 3 3
2 3 4
2 4 5
3 4 6

3 4
1 2 4
1 3 3
2 3 -1
3 1 -2

4
3

3 4
3 1 -2
1 3 3
2 3 -1
1 2 4

--------------------------
3 4
1 2 4
1 3 3
2 3 -4
3 1 -2

-1
-----------------------------
3 2
1 2 4
1 2 3

3
-1
------------------------
3 3
1 2 4
1 3 3
2 3 -1

5 8
1 3 2
1 2 4
2 3 5
2 5 8
2 4 10
3 4 3
4 5 1
5 3 -4

5 12
1 2 4
1 3 2
1 4 -5
2 4 10
2 5 -2
3 5 5
3 2 -3
2 3 3
3 4 3
3 1 4
4 5 1
5 3 7
1 3 -4
2 1 1
------------------------
3 4
1 2 4
1 3 3
2 3 -4
3 1 -2


4 4
1 2 5
2 3 2
3 4 1
1 4 20

 */

#include <iostream>
#include <vector>
#include <limits.h>
#include <tuple>
#include <chrono>
using namespace std;
using namespace chrono;


struct Edge {
    int start;
    int end;
    int w;
    Edge(int start_node, int end_node, int w) : start(start_node), end(end_node), w(w) {}
};

static int v, query_count;//노드개수, 간선 개수
static vector<long> MD; // 최단 거리 저장하는 배열
static vector <Edge> edge_list; // 전체 간선 리스트 //출발노드, 도착노드, 가중치
system_clock::time_point start_time;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> v >> query_count;
    start_time = high_resolution_clock::now();
    //일단 배열을 최댓값으로 초기화 해.
    MD.resize(v + 1, LONG_MAX);

    for (int i = 0; i < query_count; i++) { // 간선 리스트에 데이터 저장하기
        int start, end, time;
        cin >> start >> end >> time;
        edge_list.emplace_back(start, end, time);
    }


    MD[1] = 0;
    cout << "Initial min_dist: ";
    for (int i = 1; i <= v; i++) cout << MD[i] << " ";
    cout << "\n";


    for (int i = 1; i < v; i++) {  //N보다 하나 적은 수만큼 반복
        cout << "\n--- Iteration " << i << " ---\n";

        // auto [start, end, time] = edges[0]; 이런식으로 구조적 바인딩 가능하다 알아두기
        // auto [a, b, c] = 변수 a,b,c가 있는 struct 인스턴스; 이런식으로도 가능함.
        for (auto [start,end,time] : edge_list) {
            // for (int j = 1; j < M; j++) {
            // auto m_edge = edges[j];
            // int start = get<0>(m_edge);
            // int end = get<1>(m_edge);
            // int time = get<2>(m_edge);
            // 더 작은 최단거리 가 있는 경우 갱신
            //minDist[end] == LONG_MAX인 경우는 처음인 경우고 정상이야.
            //지금까지 구한 end위치로 가는 최소경로 == 무한대 는 정상이야
            //무한대라는건 못간다는거야. 단순히 start에서 end로 못간다는거야.
            //지금까지 구한 start위치로 가는 최소경로 + start에서 end로 가는 현재 경로
            //와 지금까지 구한 end위치로 가는 최소경로를 비교하고 end 위치로 가는 최소경로 갱신
            //start로 가는 경로가 없는데 start를 통해서 end로 가는 경로는 논리적으로 말이 안돼
            cout << "Checking edge (" << start << " → " << end << ") with weight " << time << "\n";
            //못가지 않아. 그리고 시간 더 최소야. 그러면
            if (MD[start] != LONG_MAX &&
                MD[end] > MD[start] + time) {
                MD[end] = MD[start] + time;
                cout << "ℹ️Updated min_dist[" << end << "] = " << MD[end] << "\n";
            } else {
                cout << "❤️No update for min_dist[" << end << "]\n";
            }
        }
    }
    bool mCycle = false;
    //이미 n-1번 반복했는데 여기서 한번 더 반복했을 때 갱신되면 음수사이클
    cout << "\n--- Iteration One More Time" << " ---\n";
    for (auto [start_node, end_node, edge_weight] : edge_list) { // 음수 cycle 확인
        if (MD[start_node] != LONG_MAX && MD[end_node] > MD[start_node] + edge_weight) {
            mCycle = true;
            cout << "Negative cycle detected due to edge (" << start_node << " → " << end_node << ") with weight " << edge_weight << "\n";
        }
    }
    // 최종 출력
    if (!mCycle) { // 음의 cycle이 없는 경우
        for (int i = 2; i <= v; i++) {
            if (MD[i] == LONG_MAX)
                cout << "1번 도시에서 " << i << "번 도시로 가는 최소거리 : " << -1 << "\n";
            else
                cout << "1번 도시에서 " << i << "번 도시로 가는 최소거리 : " << MD[i] << "\n";
        }
    } else { // 음의 cycle이 있는 경우
        cout << -1 << "\n";
    }
    auto end_time = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end_time - start_time);
    cout << "Elapsed time: " << duration.count() << " ms\n";
    return 0;
}


/*
벨만포드알고리즘은 한 정점에서 다른 정점으로 가는 최단경로를 찾는 알고리즘이야. 근데 음의 가중치도 처리할 수 있어.
모든 간선을 확인하면서 각 정점으로 가는 최단거리를 업데이트 해.
min_dist[x]는 시작점에서 노드 x로 가는 최단거리야. 인덱스 x=1~n가 되는 배열이고, 이를 업데이트 할거야.

벨만포드는 모든 간선을 한번씩 순회해서 min_dist[x]를 업데이트 해. 이걸 work라고 하자.

이 work를 n-1번 반복을 해. 그렇게 work1 work2 work3 ... work n-1 반복하겠지.

이 work1에서는 두 홉 이상으로 결정되는 최단경로를 전부 고려하지 못해. 일부만 고려할 수 있어. 1->2->3은 고려하겠지만, 3->1->2는 고려를 못했었지?
work2에서는 두 홉 이상으로 결정되는 최단경로를 전부 고려할 수 있어.
하지만 세 홉 이상으로 결정되는 최단경로를 전부 고려하지 못해. 일부는 고려할 수 있어.

그렇기 때문에 n-1번 반복을 해.
그리고 벨만포드알고리즘은 기존에 계산했던 min_dist[x]정보를 무조건적으로 신뢰하고 이를 이용하여 업데이트해.

내가 루프를 돌다가 3에서 1로 가는 간선으로 min_dist[1]을 갱신하려고 하는 상황이라고 하자.
이때 기존에 계산했던 min_dist[3]를 이용하여 min_dist[1]을 갱신하겠지?
그런데 min_dist[3]은 이미 1번 노드를 사용한 경로로 구했을 수가 있어.
즉 1에서 3번으로 가는 간선으로 min_dist[3]을 업데이트 했을 수 있어. 그런경우에 무한루프가 생길거야.


하지만 기존의 min_dist[x]정보로

그래서 음수 무한 사이클이 생길 수 있어. 3->1->2가 제일 좋네 하고 min_dist[2]정보를 저장했어.

min_dist[x]는 시작점에서 노드 x로 가는 최단거리야. 하지만 이게 음수 무한 사이클이 생길때 이 의미가 깨져.

이걸 바탕으로 min_dist[3]을 구할 때


이 때

1.그러면 두 개 이상의 간선을 지나야 최단경로가 완성되는 경우의 일부도 첫번째 반복에서 갱신되기는 하네? O

2. 하지만 두개이상의 간선을 지나야 최단경로가 완성되는 경우 전체가 갱신되는건 두번째 반복에서부터네? O
왜냐하면 시작때문인가?

N개라면 간선이 N-1개잖아요. N-1개 반복해. N-1반복을 하는 이유가 N-1개의 간선을 지나야 최단경로가 완성되는경우 N-1번 반복해야 됌


3. 시작점이 1인데 min_dist[1]이 음수라는건 무한사이클이라는거네. O

4. 사이클 크기가 v-1일 수가 있어. 그래서 최악의 경우 v-1번 돌아야 하는 거임.
 */