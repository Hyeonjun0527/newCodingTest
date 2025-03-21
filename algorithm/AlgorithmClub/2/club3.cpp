// #include <bits/stdc++.h>
// using namespace std;
//
//
// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(NULL);
//     cout.tie(NULL);
//     int N, M;
//     cin >> N >> M;
//
//     const int N_max = 10;
//     bool treasure[N_max + 1][N_max + 1];
//
//     for (int a = 1; a <= N; a++) {
//         for (int b = 1; b <= N; b++) {
//             treasure[a][b] = true;
//         }
//     }
//
//     for (int i = 0; i < M; i++) {
//         int x = 0, y = 0, k = 0;
//         cin >> x >> y >> k;
//         treasure[x][y] = false;
//
//         for (int a = 1; a <= N; a++) {
//             for (int b = 1; b <= N; b++) {
//                 if (!treasure[a][b]) continue;
//
//                 if (k == 1) {
//                     if (a >= x || b != y)
//                         treasure[a][b] = false;
//                 } else if (k == 2) {
//                     if (a >= x || b <= y)
//                         treasure[a][b] = false;
//                 } else if (k == 3) {
//                     if (a != x || b <= y)
//                         treasure[a][b] = false;
//                 } else if (k == 4) {
//                     if (a <= x || b <= y)
//                         treasure[a][b] = false;
//                 } else if (k == 5) {
//                     if (a <= x || b != y)
//                         treasure[a][b] = false;
//                 } else if (k == 6) {
//                     if (a <= x || b >= y)
//                         treasure[a][b] = false;
//                 } else if (k == 7) {
//                     if (a != x || b >= y)
//                         treasure[a][b] = false;
//                 } else if (k == 8) {
//                     if (a >= x || b >= y)
//                         treasure[a][b] = false;
//                 }
//             }
//         }
//     }
//
//     for (int a =1; a <=N; a++) {
//         for (int b=1; b <=N; b++) {
//             if(treasure[a][b]) {
//                 cout << a << " " << b << endl;
//                 return 0;
//             }
//         }
//     }
// }



#include <iostream>
using namespace std;

int main() {
    int N, M;
    cin >> N >> M;

    const int N_max = 10;
    bool treasure[N_max + 1][N_max + 1];

    // 모든 위치를 true로 초기화
    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= N; ++j)
            treasure[i][j] = true;

    for (int t = 0; t < M; ++t) {
        int x, y, k;
        cin >> x >> y >> k;

        treasure[x][y] = false; // 나침반 사용 위치는 보물이 없음

        for (int i = 1; i <= N; ++i) {
            for (int j = 1; j <= N; ++j) {
                if (!treasure[i][j]) continue; // 이미 제외된 위치

                bool valid = false;
                if (k == 1) {
                    if (i < x && j == y) valid = true;
                } else if (k == 2) {
                    if (i < x && j > y) valid = true;
                } else if (k == 3) {
                    if (i == x && j > y) valid = true;
                } else if (k == 4) {
                    if (i > x && j > y) valid = true;
                } else if (k == 5) {
                    if (i > x && j == y) valid = true;
                } else if (k == 6) {
                    if (i > x && j < y) valid = true;
                } else if (k == 7) {
                    if (i == x && j < y) valid = true;
                } else if (k == 8) {
                    if (i < x && j < y) valid = true;
                }
                if (!valid) {
                    treasure[i][j] = false;
                }
            }
        }
    }

    // 보물의 위치 출력
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            if (treasure[i][j]) {
                cout << i << " " << j << endl;
                return 0;
            }
        }
    }
    return 0;
}

