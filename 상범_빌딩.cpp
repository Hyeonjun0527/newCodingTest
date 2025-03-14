#include <algorithm>
#include <iostream>
#include <queue>
#define M 30
using namespace std;

struct P { // Point
  int f, x, y;
};

struct N { // Node
  int f, x, y, cnt;
};

int l, r, c;
char m[M][M][M];       // map
bool visited[M][M][M]; // visited

P s, e;

// 6방향 이동 정의
int df[] = {0, 0, 0, 0, 1, -1};
int dx[] = {0, 0, 1, -1, 0, 0};
int dy[] = {1, -1, 0, 0, 0, 0};

// 초기화 함수
void initialize() {
  fill(&visited[0][0][0], &visited[0][0][0] + M * M * M, false);
}

// 입력 함수 S E
void input() {
  cin >> l >> r >> c;
  if (l == 0 && r == 0 && c == 0)
    exit(0);

  for (int f = 0; f < l; f++) {
    for (int x = 0; x < r; x++) {
      for (int y = 0; y < c; y++) {
        cin >> m[f][x][y];

        if (m[f][x][y] == 'S')
          s = {f, x, y};
        else if (m[f][x][y] == 'E')
          e = {f, x, y};
      }
    }
  }
}
// BFS 탐색 함수
int bfs(P start) {
  auto [sf, sx, sy] = start;
  queue<N> q;
  q.push({sf, sx, sy, 0});
  visited[sf][sx][sy] = true;

  while (!q.empty()) {
    auto [cf, cx, cy, cnt] = q.front();
    q.pop();

    if (cf == e.f && cx == e.x && cy == e.y) {
      return cnt;
    }

    for (int i = 0; i < 6; i++) {
      int nf = cf + df[i];
      int nx = cx + dx[i];
      int ny = cy + dy[i];
      // l r c
      if (nf < 0 || nf >= l || nx < 0 || nx >= r || ny < 0 || ny >= c) {
        continue;
      }

      if (m[nf][nx][ny] == '#' || visited[nf][nx][ny]) {
        continue;
      }

      visited[nf][nx][ny] = true;
      q.push({nf, nx, ny, cnt + 1});
    }
  }
  return -1;
}
// Solution 함수 (결과 출력)
void Solution() {
  int result = bfs(s);

  if (result == -1)
    cout << "Trapped!" << endl;
  else
    cout << "Escaped in " << result << " minute(s)." << endl;
}

// Solve 함수 (전체 과정 반복)
void Solve() {
  while (true) {
    initialize();
    input();
    Solution();
  }
}

// main 함수
int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  Solve();

  return 0;
}
