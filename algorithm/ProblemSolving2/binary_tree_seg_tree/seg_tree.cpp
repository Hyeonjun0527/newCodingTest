#include <iostream>
#include <vector>
using namespace std;

vector<long long> arr, segtree; // 데이터 배열과 세그먼트 트리
int n, m, k;                   // 배열 크기 및 쿼리 개수
int l, r, i;                   // 구간 범위 및 업데이트 위치
long long d;                   // 업데이트 변화량

// 전역 변수로 루트 노드와 범위 설정
const int ROOT = 1;
const int START = 0;
int END; // n-1 값을 저장할 변수

long long set_tree(int node, int s, int e) {
    if (s == e) {
        segtree[node] = arr[s];
        return segtree[node];
    }
    int mid = (s + e) / 2;
    segtree[node] = set_tree(node * 2, s, mid) + set_tree(node * 2 + 1, mid + 1, e);
    return segtree[node];
}

long long sum(int node, int s, int e) {
    if (l > e || r < s) return 0; // 범위 밖
    if (l <= s && e <= r) return segtree[node]; // 범위 안
    int mid = (s + e) / 2;
    return sum(node * 2, s, mid) + sum(node * 2 + 1, mid + 1, e);
}

void update(int node, int s, int e) {
    if (i < s || i > e) return; // 범위 밖
    segtree[node] += d; // 변화량만큼 업데이트
    if (s == e) return; // 리프 노드일 경우 종료
    int mid = (s + e) / 2;
    update(node * 2, s, mid);
    update(node * 2 + 1, mid + 1, e);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    // 입력 받기
    cin >> n >> m >> k;
    END = n - 1; // END 값을 설정
    arr.resize(n);
    for (int j = 0; j < n; j++) cin >> arr[j];
    segtree.resize(n * 4);

    // 세그먼트 트리 초기화
    set_tree(ROOT, START, END);

    // 쿼리 처리
    for (int j = 0; j < m + k; j++) {
        long long a, b, c;
        cin >> a >> b >> c;
        if (a == 1) {
            i = b - 1;          // 업데이트 위치
            d = c - arr[i];     // 변화량 계산
            update(ROOT, START, END); // 전역 변수를 사용
            arr[i] = c;         // 원본 데이터 갱신
        } else {
            l = b - 1;          // 쿼리 시작 범위
            r = c - 1;          // 쿼리 끝 범위
            cout << sum(ROOT, START, END) << '\n'; // 전역 변수를 사용
        }
    }

    return 0;
}
