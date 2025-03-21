/*
10 2
2 7 -5 -4 10 -5 -5 -5 30 -10
 */


#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cmath>
#include <windows.h> // Windows 전용
using namespace std;

vector<long long> Tree;
vector<long long> DP;
vector<long long> K;

long long get_max(int size, int l, int r) {
    long long max_value = LLONG_MIN;
    l += size;
    r += size;
    while (l <= r) {
        if (l % 2) max_value = max(max_value, Tree[l++]);
        if (!(r % 2)) max_value = max(max_value, Tree[r--]);
        l /= 2;
        r /= 2;
    }
    return max_value;
}

void update(int size, int i, long long value) {
    i += size;
    Tree[i] = value;
    while (i > 1) {
        i /= 2;
        Tree[i] = max(Tree[i * 2], Tree[i * 2 + 1]);
    }
}
// Windows 색상 설정 함수
void setColor(HANDLE hConsole, int color) {
    SetConsoleTextAttribute(hConsole, color);
}

void print_tree_structure(int size) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // 콘솔 핸들
    int height = log2(size);  // 트리의 높이
    int max_width = (1 << height) * 10;  // 루트 레벨의 최대 출력 너비 (노드당 최대 10칸)
    cout << "트리 구조:\n";

    for (int level = 0, start = 1; start < 2 * size; level++) {
        int node_count = (1 << level); // 현재 레벨의 노드 수
        int space_between = max_width / node_count; // 노드 간 간격
        int space_before = space_between / 2; // 첫 노드 앞 스페이스

        // 레벨 출력
        cout << "[" << level + 1 << "]: ";
        for (int i = 0; i < space_before / 2; i++) cout << " "; // 첫 노드 앞 스페이스
        for (int i = start; i < start + node_count && i < 2 * size; i++) {
            if (Tree[i] == LLONG_MIN) {
                cout << "[ -∞ ]";
            } else {
                setColor(hConsole, 9); // 파란색
                cout << "[ " << i << ": " << Tree[i] << " ]";
                setColor(hConsole, 7); // 기본 색으로 복원
            }
            for (int j = 0; j < space_between / 4 + 5; j++) cout << " "; // 노드 간 공백
        }
        cout << "\n";
        start += node_count; // 다음 레벨의 시작 노드
    }
}

int main() {
    int n, d;
    cin >> n >> d;

    int size = 1;
    while (size < n) size *= 2;

    Tree.resize(2 * size, LLONG_MIN);
    K.resize(n);
    DP.resize(n, 0);

    for (int i = 0; i < n; i++) {
        cin >> K[i];
        DP[i] = K[i];
    }

    long long result = LLONG_MIN;
    for (int i = 0; i < n; i++) {
        long long max_prev = 0;

        // i-d ~ i-1 범위에서 최대값 구하기
        if (i > 0) max_prev = get_max(size, max(0, i - d), i - 1);

        // DP 갱신
        DP[i] = max(K[i], K[i] + max_prev);

        // Tree 갱신
        update(size, i, DP[i]);

        // 결과 갱신
        result = max(result, DP[i]);

        // 로그 출력
        cout << "i = " << i << ", K[" << i << "] = " << K[i]
             << ", max_prev = " << max_prev
             << ", DP[" << i << "] = " << DP[i] << "\n";
        print_tree_structure(size);
    }

    cout << "최종 결과: " << result << "\n";
    return 0;
}
