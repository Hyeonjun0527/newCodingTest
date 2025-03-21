/*
//만약에 20이 최대로 주어지면 -32~32까지 가능하므로, 만약에 16이 최대래 그러면
    //n_max는 이동 가능한 횟수래 = 12 라면 11,22,44,88,1616,3232로 2^6=32, -32~32까지 가능해.
 */


#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <limits>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 입력받은 테스트 케이스의 목표 좌표를 저장
    int T;
    cin >> T;
    vector<long long> target_positions(T); // 목표 좌표 목록
    long long min_x = numeric_limits<long long>::max(); // 좌표의 최소값 초기화
    long long max_x = numeric_limits<long long>::min(); // 좌표의 최대값 초기화

    // 테스트 케이스 입력과 최소/최대 좌표값 계산
    for (int i = 0; i < T; ++i) {
        cin >> target_positions[i];
        min_x = min(min_x, target_positions[i]);
        max_x = max(max_x, target_positions[i]);
    }

    // 민서가 도달해야 할 가장 멀리 있는 좌표의 절대값 계산
    long long max_abs_x = max(abs(min_x), abs(max_x));

    // max_abs_x에 도달하기 위한 최대 이동 횟수 추정
    long long max_steps = 2 * ceil(log2(max_abs_x + 1)) + 2;

    // 이동 단계마다 계산된 값들을 저장할 벡터 선언
    vector<long long> destination_positions;  // 각 이동 목표 위치
    vector<long long> accumulated_positions;  // 실제 민서가 누적 이동한 위치
    vector<long long> travel_time;            // 각 위치에 도달하는 데 걸린 누적 시간

    destination_positions.reserve(max_steps + 1);
    accumulated_positions.reserve(max_steps + 1);
    travel_time.reserve(max_steps + 1);

    // 시작 위치 초기화
    accumulated_positions.push_back(0);
    travel_time.push_back(0);

    // 각 이동 단계마다 목표 위치와 누적 시간을 계산
    for (long long i = 0; i <= max_steps; ++i) {
        long long distance = static_cast<long long>(pow(2, i / 2)); // 2의 거듭제곱 형태로 이동 거리 결정
        long long destination = (i % 2 == 0) ? distance : -distance; // 짝수: 오른쪽(+), 홀수: 왼쪽(-)

        destination_positions.push_back(destination);//목표 위치를 저장해

        long long previous_position = accumulated_positions.back();// 이전 위치야
        long long previous_time = travel_time.back();//이전 시간
        long long current_time = previous_time + abs(destination - previous_position);//이전 위치에서 현재 목표 위치까지 이동하는 데 걸리는 시간

        accumulated_positions.push_back(destination);
        travel_time.push_back(current_time);
    }

    // 결과 저장 벡터 초기화 (각 테스트 케이스의 결과)
    vector<long long> results(T, numeric_limits<long long>::max());

    //민서가 각 목표 위치에 도달하는 시간을 미리 계산하여 테이블 형태로 저장했음
    //D : 민서가 각 이동 단계에서 목표로 하는 위치
    //P 벡터  민서가 실제로 지나간 위치를 누적하여 저장 (민서가 이동할 때의 위치를 순서대로 저장)
    // 각 목표 좌표에 대해 도달하는 최소 시간을 계산
    // T_i 벡터 각 위치에 도달하는 데 걸린 누적 시간
    for (int idx = 0; idx < T; ++idx) {
        long long target = target_positions[idx];
        long long min_time_to_target = numeric_limits<long long>::max();

        // 목표 좌표가 포함된 이동 구간을 찾아 해당 구간의 도달 시간을 계산
        //destination_positions[i-1] = accumulated_positions[i] 야. destination이 next고 accumulated 가 current야. 다음위치 현재 위치야.
        //accumulated_positions = [0, 1, -1, 2, -2, 4, -4, 8, ...]
        //destination_positions =   [1, -1, 2, -2, 4, -4, 8, -8, ...] 각 단계의 목표 위치 저장
        //travel_time):             [0, 1, 3, 6, 10, 15, 21]
        for (size_t i = 1; i < accumulated_positions.size(); ++i) {
            long long start = min(accumulated_positions[i - 1], destination_positions[i - 1]);
            long long end = max(accumulated_positions[i - 1], destination_positions[i - 1]);

            //[start, end] = [-2, 4] 내에 target = 3이 포함되므로, 이 구간에서 target에 도달하는 시간을 계산해 봅시다.
            //이전 위치까지의 누적 시간: travel_time[4] = 10 이전 위치(accumulated_positions[4] = -2)에서 target = 3까지 거리
            if (target >= start && target <= end) {
                long long time_to_target = travel_time[i - 1] + abs(target - accumulated_positions[i - 1]);
                min_time_to_target = time_to_target;
                break; // 최초로 도달한 시간을 기록했으므로 더 이상 반복할 필요 없음
            }
        }
        results[idx] = min_time_to_target; // 결과 저장
    }

    // 각 테스트 케이스의 결과 출력
    for (long long result : results) {
        cout << result << '\n';
    }

    return 0;
}
