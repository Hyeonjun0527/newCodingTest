#include <iostream>
#include <vector>
using namespace std;

vector<int> a, t;

// 결합 함수: 두 값의 합을 반환 (구간 합을 구하기 위한 연산)
int mrg(int a, int b) { return a + b; }

// --- 세그먼트 트리 구축 (Build) ---
// 노드 n이 배열 a의 구간 [s, e]를 담당하도록 세그먼트 트리를 구축합니다.
int st(int n, int s, int e) {
    // [기저 조건] 구간에 단 하나의 원소만 있는 경우 (리프 노드)
    if (s == e)
        return t[n] = a[s]; // 배열 a의 해당 원소 값을 트리 노드 t[n]에 저장 후 반환

    // [분할] 현재 구간 [s, e]를 두 부분으로 나눕니다.
    int mid = s + (e - s) / 2; // 구간의 중간 인덱스 계산 (overflow를 방지하는 방식)
    
    // [정복] 재귀 호출을 통해 좌측 구간 [s, mid]와 우측 구간 [mid+1, e]에 대한 결과를 구합니다.
    // 두 결과를 결합 함수 mrg로 합산한 값을 현재 노드 t[n]에 저장하고 반환합니다.
    return t[n] = mrg(st(n, s, mid), st(n, mid + 1, e));
}

// --- 구간 질의 (Query) ---
// 노드 n이 담당하는 구간 [s, e] 내에서 질의 구간 [l, r]의 합을 계산합니다.
int qry(int n, int s, int e, int l, int r) {
    // [비교 1] 현재 구간 [s, e]와 질의 구간 [l, r]가 전혀 겹치지 않는 경우
    if (e < l || r < s)
        return 0;  // 겹치는 부분이 없으므로 항등원 0을 반환

    // [비교 2] 현재 구간 [s, e]가 질의 구간 [l, r]에 완전히 포함되는 경우
    if (l <= s && e <= r)
        return t[n];  // 미리 계산된 결과인 t[n]을 그대로 반환

    // [분할] 현재 구간이 질의 구간과 부분적으로만 겹칠 경우,
    // 구간을 반으로 나눠 좌측과 우측에서 각각 질의를 수행합니다.
    int mid = s + (e - s) / 2;
    
    // [정복] 좌측 구간 [s, mid]와 우측 구간 [mid+1, e]의 질의 결과를 결합 함수 mrg로 합산해 반환합니다.
    return mrg(qry(n, s, mid, l, r), qry(n, mid + 1, e, l, r));
}

// --- 업데이트 (Update) ---
// 노드 n이 담당하는 구간 [s, e] 내에서 배열 a의 인덱스 i를 새로운 값 v로 업데이트합니다.
int upt(int n, int s, int e, int i, int v) {
    // [기저 조건 1] 업데이트할 인덱스 i가 현재 구간 [s, e]에 포함되지 않는 경우
    if (i < s || e < i)
        return t[n];  // 아무 변화가 없으므로 현재 노드 t[n]을 그대로 반환

    // [기저 조건 2] 현재 구간이 단일 원소인 경우 (리프 노드)
    if (s == e)
        return t[n] = v;  // 해당 원소를 새로운 값 v로 업데이트하고 반환

    // [분할] 현재 구간 [s, e]를 반으로 나눕니다.
    int mid = s + (e - s) / 2;
    
    // [정복] 좌측 자식(노드 2*n)과 우측 자식(노드 2*n+1)에서 재귀적으로 업데이트를 수행합니다.
    // 두 결과를 결합 함수 mrg로 합산해 현재 노드 t[n]의 값을 갱신한 후 반환합니다.
    return t[n] = mrg(upt(2 * n, s, mid, i, v), upt(2 * n + 1, mid + 1, e, i, v));
}

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    int ROOT = 1, START = 0, END = n - 1;
    
    // 배열과 세그먼트 트리 저장 공간 할당
    a.resize(n);
    t.resize(n * 4); // 최악의 경우에도 충분한 크기를 확보하기 위해 4*n 크기 할당
    
    // 배열 입력
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    // 세그먼트 트리 구축: 전체 구간 [0, n-1]에 대해 구축
    st(ROOT, START, END);
    
    // m + k 번의 연산 수행 (업데이트와 질의)
    for (int i = 0; i < m + k; i++) {
        int type, b, c;
        cin >> type >> b >> c;
        if (type == 1) {
            // 업데이트 연산: 배열의 b번째 원소를 c로 변경 (인덱스 보정: 0부터 시작)
            upt(ROOT, START, END, b - 1, c);
        } else {
            // 질의 연산: 배열의 b번째부터 c번째 원소까지의 구간 합 출력 (인덱스 보정)
            cout << qry(ROOT, START, END, b - 1, c - 1) << "\n";
        }
    }
}
