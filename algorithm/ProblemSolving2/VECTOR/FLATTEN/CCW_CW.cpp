#include <iostream>
#include <vector>
using namespace std;

// 행렬을 90도 회전
vector<vector<int>> rotate90(const vector<vector<int>>& mat) {
    int k = mat.size();
    vector<vector<int>> result(k, vector<int>(k, 0));
    for (int x = 0; x < k; ++x) {
        for (int y = 0; y < k; ++y) {
            // 시계 방향 90도 회전 (CW)
            result[x][y] = mat[k - 1 - y][x];
        }
    }
    return result;
}

// 행렬 OR 연산 결과가 모두 1인지 확인
bool checkAllOnes(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int k = A.size();
    for (int r = 0; r < k; ++r) {
        for (int c = 0; c < k; ++c) {
            if ((A[r][c] | B[r][c]) != 1) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N; // N개의 행렬
    cin >> N;

    while (N--) {
        // 1) 입력: k, 그리고 1차원 배열
        int k;
        cin >> k; // k를 입력받는다

        vector<int> flat(k * k);
        for (int i = 0; i < k * k; ++i) {
            cin >> flat[i]; // 1차원 배열 k*k개
        }

        // 2) 2차원 행렬로 복원
        vector<vector<int>> matrix(k, vector<int>(k));
        int idx = 0;
        for (int r = 0; r < k; ++r) {
            for (int c = 0; c < k; ++c) {
                matrix[r][c] = flat[idx++];
            }
        }

        // 3) 4가지 회전 결과 구하기
        vector<vector<int>> rot0   = matrix; 
        vector<vector<int>> rot90  = rotate90(rot0); 
        vector<vector<int>> rot180 = rotate90(rot90);
        vector<vector<int>> rot270 = rotate90(rot180);

        // 4) 가능한 6가지 쌍 중 OR 결과가 모두 1인지 검사
        bool isAllOnes = false;

        // 람다식을 이용해 코드 중복 줄임
        auto checkPairs = [&](const vector<vector<int>>& A, const vector<vector<int>>& B) {
            if (checkAllOnes(A, B)) {
                isAllOnes = true;
            }
        };

        // 6가지 쌍 확인
        checkPairs(rot0, rot90);
        checkPairs(rot0, rot180);
        checkPairs(rot0, rot270);
        checkPairs(rot90, rot180);
        checkPairs(rot90, rot270);
        checkPairs(rot180, rot270);

        // 결과 출력
        cout << (isAllOnes ? "true" : "false") << "\n";
    }

    return 0;
}
