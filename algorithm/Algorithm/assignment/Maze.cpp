#include <bits/stdc++.h>
using namespace std;

// int A[10][10];
int dx[4] = {-1,0,1,0};
int dy[4] = {0,1,0,-1};

int BFS(int maze[10][10]) {
    queue<tuple<int, int, int>> my_queue;
    bool visited[10][10] = {false};
    my_queue.emplace(0, 0, 0);//x y count_
    visited[0][0] = true;
    //나를 넣고 꺼내서 자신의 이웃노드를 넣어야 해.
    while (!my_queue.empty()) {
        auto [current_x, current_y, count_] = my_queue.front();
        my_queue.pop();

        if (current_x == 9 && current_y == 9) {
            return count_;
        }

        for (int i = 0; i < 4; i++) {
            auto next_x = current_x + dx[i];
            auto next_y = current_y + dy[i];

            if (next_x >= 0 && next_x <= 9 && next_y >=0 && next_y <= 9 &&
                maze[next_x][next_y] && !visited[next_x][next_y]) {

                visited[next_x][next_y] = true;
                my_queue.emplace(next_x, next_y, count_ + 1);

            }
        }
    }
    return -1;
}

int minimum_move(int maze[10][10]) {
    int count_ = BFS(maze);

    cout << count_ << endl;
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    minimum_move(A);

}
