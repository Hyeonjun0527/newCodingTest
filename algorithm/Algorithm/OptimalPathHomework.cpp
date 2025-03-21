/*
옵티멀 패스 문제

최고의 경로를 찾는 문제야
비용이 최적인걸 찾으면 돼.

노드와 가중치가 있나?
[n][5]형태로만 주어져.

현재위치에서 노드 00 01 02 이런 노드위치
그리고 그 노드로 가는 비용들..

이렇게 관점을 볼 수 있어.

단순하게 배열에 비용이 들어가 있잖아.

인접배열이 주어진거라고 볼 수 있어.

다익스트라 알고리즘을 사용하는 거 같아. 한 노드에서 다른 모든 목표노드로 가기 위한 최소비용

방향그래프가 되겠다. 01의 인접노드는 10 11 12잖아.

먼저 그래프를 구성해야겠네.

간선을 어떻게 처리하지?

 */


#include <bits/stdc++.h>
using namespace std;

int v;

int start_node;
typedef pair<int, int> Edge; // 인접 노드, 가중치 (int)
vector<vector<Edge>> adj_list; // 인접 리스트
priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> my_priority_queue; // 누적 거리 (long long), 노드 인덱스
vector<long long> min_distance; // 최소 거리 (long long)
vector<int> previous_node; // 이전 노드 인덱스 (int)

int convert_index(int i, int j, int n) {
    return j * n + i + 1;
}

pair<int, int> convert_reverse_index(int k, int n) {
    k = k - 1;
    int i = k % n;
    int j = k / n;
    return make_pair(i, j);
}

vector<int> get_optimal_path(int n, vector<vector<int> > &net) {
    v = n * 5 + 1;
    start_node = 0;

    adj_list.assign(v,vector<Edge>());
    // 간선 정보 입력
    for (int i = 0; i <= n - 1; i++) {
        for (int j = 0; j <= 4; j++) {
            int current_node = convert_index(i, j, n);
            if (i == 0) {
                adj_list[0].emplace_back(current_node, net[i][j]);
            }
            if (i != n - 1) {
                if (j == 0) {
                    adj_list[current_node].emplace_back(current_node + 1, net[i + 1][j]);          // 중간
                    adj_list[current_node].emplace_back(current_node + n + 1, net[i + 1][j + 1]);  // 아래
                } else if (j == 4) {
                    adj_list[current_node].emplace_back(current_node - n + 1, net[i + 1][j - 1]);  // 위
                    adj_list[current_node].emplace_back(current_node + 1, net[i + 1][j]);          // 중간
                } else {
                    adj_list[current_node].emplace_back(current_node - n + 1, net[i + 1][j - 1]);  // 위
                    adj_list[current_node].emplace_back(current_node + 1, net[i + 1][j]);          // 중간
                    adj_list[current_node].emplace_back(current_node + n + 1, net[i + 1][j + 1]);  // 아래
                }
            }
        }
    }

    my_priority_queue.push(make_pair(0LL, start_node));

    min_distance.assign(v, LLONG_MAX);
    min_distance[start_node] = 0;

    previous_node.assign(v, -1);

    // 다익스트라 알고리즘 실행
    while (!my_priority_queue.empty()) {
        auto current = my_priority_queue.top();
        long long current_dist = current.first;
        int current_node = current.second;
        my_priority_queue.pop();

        if (current_dist > min_distance[current_node]) continue;

        for (auto& neighbor : adj_list[current_node]) {
            int next_node = neighbor.first;   // 인접 노드
            int weight = neighbor.second;     // 가중치
            if (min_distance[next_node] > min_distance[current_node] + weight) {
                min_distance[next_node] = min_distance[current_node] + weight;
                previous_node[next_node] = current_node;
                my_priority_queue.push(make_pair(min_distance[next_node], next_node));
            }
        }
    }

    long long final_min = LLONG_MAX;
    vector<int> final_positions;
    for (int j = 0; j < 5; ++j) {  // 마지막 행의 모든 열을 확인
        int last_row_node = convert_index(n - 1, j, n);
        if (final_min > min_distance[last_row_node]) {
            final_min = min_distance[last_row_node];
            final_positions.clear();
            final_positions.push_back(last_row_node);
        } else if (final_min == min_distance[last_row_node]) {
            final_positions.push_back(last_row_node);
        }
    }


    vector<vector<int>> solutions;

    for (int final_position : final_positions) {
        vector<int> solution;
        int temp_position = final_position;
        while (temp_position != start_node) {
            pair<int, int> pos = convert_reverse_index(temp_position, n);
            int j = pos.second;
            solution.push_back(j);
            temp_position = previous_node[temp_position];
        }
        reverse(solution.begin(), solution.end());
        solutions.push_back(solution);
    }

    vector<int> answer = *min_element(solutions.begin(), solutions.end());

    return answer;
}


int main() {

    int n = 3;

    vector<vector<int>> net = {
        {3, 1, 5, 8, 4},
        {6, 7, 2, 3, 9},
        {4, 5, 6, 7, 2}
    };

    vector<int> sol = get_optimal_path(n, net);

    for (int temp : sol) {
        cout << temp;
    }
    cout << endl;

    return 0;
}
