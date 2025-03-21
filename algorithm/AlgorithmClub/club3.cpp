#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <limits>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    vector<long long> x_list(T);
    long long x_min = numeric_limits<long long>::max();
    long long x_max = numeric_limits<long long>::min();
    // 입력된 각 테스트 케이스의 좌표를 저장하고, 최소값과 최대값을 계산
    for (int i = 0; i < T; ++i) {
        cin >> x_list[i];               // 각 테스트 케이스의 좌표 입력
        x_min = min(x_min, x_list[i]);  // 최소값 업데이트
        x_max = max(x_max, x_list[i]);  // 최대값 업데이트
    }
    // 민서가 이동해야 할 가장 멀리 떨어진 좌표의 절대값을 구함
    long long max_abs_x = max(abs(x_min), abs(x_max));// 민서가 이동해야 할 가장 멀리 떨어진 목적지의 거리

    // max_abs_x에 도달하기 위해 필요한 최대 이동 횟수를 계산
    long long n_max = 2 * ceil(log2(max_abs_x + 1)) + 2;

    vector<long long> D; // 각 이동의 목적지를 저장하는 벡터
    vector<long long> P; // 민서가 매 이동마다 위치하게 될 좌표를 순서대로 저장하는 벡터 1, -1, 2, -2, 4,-4 이렇게 저장해.
    vector<long long> T_i; // 각 위치에 도달하는 데 걸린 누적 시간을 저장하는 벡터
    D.reserve(n_max + 1);
    P.reserve(n_max + 1);
    T_i.reserve(n_max + 1);//reserve는 안해도 되지만 성능 최적화한다고 한다.

    P.push_back(0); // 초기 위치는 0
    T_i.push_back(0); // 초기 위치에 도달하는 데 걸린 시간은 0

    // 각 목적지와 그에 도달하는 누적 시간을 계산
    for (long long i = 0; i <= n_max; ++i) {
        long long power = static_cast<long long>(pow(2, i / 2)); // 현재 이동 거리 계산 (1, -1, 2, -2, 4, -4...의 패턴)
        long long D_i = (i % 2 == 0) ? power : -power; // 짝수일 때는 양수, 홀수일 때는 음수로 방향을 결정
        D.push_back(D_i); // 목적지를 D에 추가

        long long prev_P = P.back(); // 이전 위치
        long long prev_T = T_i.back(); // 이전까지의 누적 시간
        long long T_curr = prev_T + abs(D_i - prev_P); // 현재 위치까지 이동하는 데 걸린 시간 계산
        P.push_back(D_i); // 현재 위치를 P에 추가
        T_i.push_back(T_curr); // 현재 위치까지의 누적 시간을 T_i에 추가
    }


    // 결과 저장 벡터, 처음에는 최대로 초기화
    vector<long long> results(T, numeric_limits<long long>::max());
    for (int idx = 0; idx < T; ++idx) {
        long long x = x_list[idx]; // 각 테스트 케이스의 목표 좌표 x
        long long min_time = numeric_limits<long long>::max(); // 목표 좌표에 도달하는 최소 시간을 초기화

        // 목적지 구간을 탐색하여 목표 좌표 x가 포함된 구간을 찾고, 해당 구간의 도달 시간을 계산
        for (size_t i = 1; i < P.size(); ++i) {
            long long s = min(P[i - 1], D[i - 1]); // 이전 위치와 현재 목적지의 작은 값 (구간의 시작)
            long long e = max(P[i - 1], D[i - 1]); // 이전 위치와 현재 목적지의 큰 값 (구간의 끝)

            // x가 구간 [s, e]에 포함되어 있는지 확인
            if (x >= s && x <= e) {
                long long time = T_i[i - 1] + abs(x - P[i - 1]); // 목표 좌표 x까지의 도달 시간 계산
                if (time < min_time) { // 가장 짧은 도달 시간을 찾기 위해 비교
                    min_time = time;
                }
            }
        }
        results[idx] = min_time; // 각 테스트 케이스에 대한 결과를 results에 저장
    }

    // 각 테스트 케이스의 결과 출력
    for (long long res : results) {
        cout << res << '\n';
    }

    return 0;
}
