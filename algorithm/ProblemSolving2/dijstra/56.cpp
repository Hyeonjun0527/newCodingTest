/*
BFS는 각 노드를 큐에 한번만 넣어.
즉, 대상 노드에 대해서 인접노드를 다시 순회하는 일이 없어.
네, 다익스트라 알고리즘도 BFS처럼 방문이 완료된 노드는
인접 노드를 다시 방문하지 않습니다.
다만, 이는 우선순위 큐를 사용하는 다익스트라 알고리즘의 특성 덕분에
가능한 최적화입니다.
정점의 개수 간선의 개수
시작 정점 번호
백준 1753
5 6
1
5 1 1
1 2 2
1 3 3
2 3 4
2 4 5
3 4 6

0
2
3
7
INF
첫째 줄부터 V개의 줄에 걸쳐, i번째 줄에 i번 정점으로의 최단 경로의 경로값을 출력한다.
시작점 자신은 0으로 출력하고, 경로가 존재하지 않는 경우에는 INF를 출력하면 된다.

5 6
1
1 2 1
1 3 2
1 4 3
2 5 6
3 5 4
4 5 2
 */

#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
using namespace std;


struct Edge {
    int next_node;//pq에서 꺼낼때 next_node, adj에서 꺼낼때도 next_node
    int w;//이건 pq한테는 누적 가중치(지금까지 기록한 누적거리)
    Edge(int next_node, int w) : next_node(next_node), w(w) {}
    bool operator<(const Edge& other) const {
        return w > other.w;
    }
};
//인접리스트의 인덱스가 대상 노드 내부값으로 Edge(인접노드와 weight)
//다엑스트라다? 그러면 MD AV 봤쓰야. MD:최소거리 A:인접리스트 V:방문배열 v e s: vertex,edge,start_node
vector<int> MD; //최소거리(누적됨)
priority_queue<Edge> pq;
int v, e, s;
vector<vector<Edge>> ad_jlist;//인접리스트(얘는 누적이 아니야)
vector<bool> visited; //방문체크
vector<int> previous_node; // 이전 노드를 저장할 벡터 추가
//큐에 들어가 있는 건 그냥 가중치가 아니라 지금 현재까지 찾은 최적의(optimal) 가중치를 의미하고 있어.
//최적 가중치와 대상노드야.

void printPriorityQueue(priority_queue<Edge> pq) {
    cout << "☺️큐 상태 : [ ";
    while (!pq.empty()) {
        cout << "(" << pq.top().next_node << ", " << pq.top().w << "), ";
        pq.pop();
    }
    cout << "]" << endl;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    //v : 간선수 e : 에지 수
    cin >> v >> e >> s;

    // 최소 거리 테이블 초기화
    // 방문 체크 테이블 초기화
    // 인접 리스트 초기화
    MD.resize(v + 1, INT_MAX);
    ad_jlist.resize(v + 1);
    visited.resize(v + 1, false);
    previous_node.resize(v + 1, -1); // 초기값 -1로 설정


    //노드 1 노드2 간선, 즉 간선정보를 입력받아.
    for (int i = 0; i < e; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        ad_jlist[u].emplace_back(v, w);
    }//u = 1 v = 2 w = 3 1에서 2로가는 간선 가중치가 3이다.

    //큐 첫번째 넣기, MD 최소거리 s에서 s는 0이므로.
    pq.emplace(s, 0);
    MD[s] = 0;
    //다익스트라는 분신술 알고리즘 같아. 큐에 같은 노드가 여러번 들어갈 수 있어. (5,3) (5,6) (5,10) 이런식으로 들갈 수 있어.
    //나루토가 그림자 분신술 팡 썼어. 그리고 분신술한테 말하는거야. 야 너 갈림길 만나면 내가 했던 것처럼 분신 만들어.
    //막다른 길 다다르면 사라져도 돼. 그리고 가면서 방문했음을 알잖아. 그림자 분신이니깐.
    //그리고 가면서 내가 갔던 길을 기억을 하는거지. visited랑 MD가 나루토의 뇌인거야. 나루토가 수학 천재라고 하자.
    //그래서 모든 위치마다 최단거리를 기록해야 돼. 그러러면 내가 V3에서 V4로 왔어. 그러면 V3까지 얼마나 걸렸는지 + V3에서 V4로 얼마나 걸리는지
    //그걸 최단으로 기록하면 되잖아.
    //분신술 팡 쓰면서 큐에 인접노드 3개가 들어가. 분신 3명이 동시에 막 돌아댕기지 않고 한명 씩 가.

    //나루토는 가야할 곳을 먼저 pq로 계획할거야.
    //0.본체는 움직이지 않는다. 1. pq는 공유한다. 2. 모든 분신들과 본체는 서로 상황을 실시간으로 안다. 3. 분신이 분신을 만들 수 있다. 5. 분신 만드는게 pq에 넣는거야.
    //6. 도착할때마다 visited로 기록한다. 7. 한명이 움직이면 나머지는 못움직임. 8. 분신은 한번에 한명씩 만들 수 있음. 8. 분신이 움직일때마다 누적거리 MD 갱신하고 pq에 w로 넣어.
    //나루토가 V1에 도착했어. V1 기록했어. 3개 경로 만났어. pq에 3노드를 담아. 분신 3개 만들어. 그리고 누가 움직일래? 최단 가중치 가진 놈이 움직여.
    //분신은 또 3갈래 길을 만난거야. pq에 또 3개를 담아.
    //
    //먼저 나루토가 v1에 도착했어. v2,v3,v4를 방문해야돼. 그래서 분신을 하나 만들어. 이동하고 누적거리(MD)갱신하고 pq에 분신을 넣었어. x3번 이걸 반복해.
    //pq가 분신을 다 모아놓은거야. 그 pq중에서 가장 누적거리 짧았던 분신 택해. 분신은 누적거리랑 다음 노드 어디로 갈지 알아.
    //
    printPriorityQueue(pq);

    while (!pq.empty()) {
        //큐에서 꺼냈어. 대상 노드를 꺼낸거야.
        //대상노드가 이미 방문했으면 건너뛰어.
        Edge current = pq.top();//넥스트 노드로 간거야. next_node가 current_node가 된거지.
        pq.pop();
        cout << "------------------------------------------";
        cout << "큐에서 뺐습니다 : 뺀 것 : (" << current.next_node << ", " << current.w << ")------------------------------------------" << endl;
        printPriorityQueue(pq);
        if (visited[current.next_node]) continue;//왜 방문한거 건너뛰죠? 인접노드를 전부 반복했으면 또 반복할 필요는 없어.
        int current_node = current.next_node;

        //이 노드에 대한 최단경로를 확정했다는 의미로 큐를 꺼내는거야.
        visited[current_node] = true;

        cout << "노드 " << current_node << "의 인접노드 순회 시작-------\n" << endl;
        for (auto& neighbor : ad_jlist[current_node]) {
            int next_node = neighbor.next_node;
            int weight = neighbor.w;
            // 다음 노드에 대해서 이미 구했던 최소거리보다 더 좋은 길(지금 노드에서 가기)을 찾으면
            if (MD[next_node] > MD[current_node] + weight) {
                MD[next_node] = MD[current_node] + weight;
                cout << "ℹ️ 갱신됨 : MD[" << next_node << "] = " << MD[next_node]
                     << " <==== current_node : " << current_node
                     << ", MD[" << current_node << "] = " << MD[current_node]
                     << " , weight : " << weight << endl;

                // 이전 노드 저장
                previous_node[next_node] = current_node;

                // 큐에 삽입
                pq.emplace(next_node, MD[next_node]);
                cout << "❤️ 큐에 넣었습니다 : 넣은 것 : (" << next_node << ", " << MD[next_node] << ")" << endl;
                printPriorityQueue(pq);
            } else {
                // 갱신되지 않은 경우 로그 출력
                cout << "❌ 갱신 안 됨 : MD[" << next_node << "] = " << MD[next_node]
                     << " >= current_node : " << current_node
                     << ", MD[" << current_node << "] = " << MD[current_node] << " + weight : " << (weight) << endl;
            }
        }

    }

    for (int i = 1; i <= v; i++) {
        if (visited[i]) {
            cout << "Distance to node " << i << ": " << MD[i] << "\n";
            cout << "Path: ";
            int node = i;
            while (node != -1) {
                cout << node << " ";
                node = previous_node[node];
            }
            cout << "\n";
        } else {
            cout << "Distance to node " << i << ": INF\n";
        }
    }


    for (int i = 1; i <= v; i++) {
        if (visited[i])
            cout << MD[i] << "\n";
        else
            cout << "INF\n";
    }
}


/*
/*

엄마 베스가 질문했어. 애들 왔니?
MD
v e s
pq
adj_list
visited

생성자 : 위에 잇는거 그대로 다 쓰면 대.
불러 오빠

 #1#
#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int w;
    int next_node;//pq에서 꺼낼땐 next_node, adj에서 꺼낼땐 next_node
    Edge(int w, int next_node) : w(w), next_node(next_node) {}
    bool operator<(const Edge& other) const {
        return w > other.w;
    }
};
vector<int> MD;
int v, e, s;
priority_queue<Edge> pq;
vector<vector<Edge>> adj_list;
vector<bool> visited;
vector<int> previous_node;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> v >> e >> s;

    MD.resize(v + 1, INT_MAX);
    adj_list.resize(v + 1);
    visited.resize(v + 1);
    previous_node.resize(v + 1, -1);

    for (int i = 0; i < e; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj_list[u].emplace_back(v, w);
    }

    pq.emplace(0, s);
    MD[s] = 0;

    while (!pq.empty()) {
        Edge current = pq.top();
        pq.pop();
        if (visited[current.next_node]) continue;

        int current_node = current.next_node;
        visited[current_node] = true;
        for (auto& neighbor : adj_list[current_node]) {
            int next_node = neighbor.next_node;
            int weight = neighbor.w;
            if (MD[next_node] > MD[current_node] + weight) {
                MD[next_node] = MD[current_node] + weight;
                previous_node[next_node] = current_node;
                pq.emplace(MD[next_node], next_node);
            }
        }
    }
    for (int i = 1; i <= v; i++) {
        if (visited[i])
            cout << MD[i] << "\n";
        else
            cout << "INF\n";
    }

}
*/
