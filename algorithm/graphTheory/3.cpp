#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 특정 원소가 속한 집합을 찾기 (경로 압축 기법 사용)
//특정 원소가 속한 집합을 찾는다. 루트노드는 => x=parent[x]야. 루트노드면 재귀 마지막이어야 해 return 해
// !루트노드 => 루트노드로 접근해야하니까 find_parent(parent,parent[x])할 수 밖에 없어.
//경로압축기법으로 마지막N번쨰 재귀호출의 리턴값을 parent[n-1]에 담아. 그걸 쭉 반복...
int find_parent(vector<int>& parent, int x) {
    if (parent[x] != x) {
        parent[x] = find_parent(parent, parent[x]);
    }
    return parent[x];
}

// 두 원소가 속한 집합을 합치기
void union_parent(vector<int>& parent, int a, int b) {
    a = find_parent(parent, a);
    b = find_parent(parent, b);
    if (a < b) {
        parent[b] = a;
    } else {
        parent[a] = b;
    }
}

int main() {
    int v, e;
    cin >> v >> e;

    // 부모 테이블 초기화
    vector<int> parent(v + 1);
    for (int i = 1; i <= v; i++) {
        parent[i] = i;
    }

    // 간선 정보 입력받기
    vector<tuple<int, int, int>> edges;
    int result = 0;

    for (int i = 0; i < e; i++) {
        int a, b, cost;
        cin >> a >> b >> cost;
        edges.push_back({cost, a, b});
    }

    // 간선을 비용 순으로 정렬
    sort(edges.begin(), edges.end());

    int last = 0; // 최소 신장 트리에 포함된 간선 중에서 가장 비용이 큰 간선

    // 간선들을 하나씩 확인하면서 최소 신장 트리 구성
    for (auto edge : edges) {
        int cost, a, b;
        tie(cost, a, b) = edge;

        // 사이클이 발생하지 않는 경우에만 집합에 포함
        if (find_parent(parent, a) != find_parent(parent, b)) {
            union_parent(parent, a, b);
            result += cost;
            last = cost; // 가장 최근에 추가한 간선의 비용
        }
    }

    // 최소 신장 트리에서 가장 큰 간선을 제외한 결과 출력
    cout << (result - last) << endl;

    return 0;
}
