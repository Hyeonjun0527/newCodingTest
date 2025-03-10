#include <algorithm>
#include <iostream>
#include <queue>

#define M 30
using namespace std;

struct P {
  int f, x, y;
};

struct N {
  int f, x, y, cnt;
};

int l, r, c;
char m[M][M][M];
bool v[M][M][M];

P s, e;

// 6방향 이동 정의
int df[] = {0, 0, 0, 0, 1, -1};
int dx[] = {0, 0, 1, -1, 0, 0};
int dy[] = {1, -1, 0, 0, 0, 0};

void initialize() { fill(&v[0][0][0], &v[0][0][0] + M * M * M, false); }

void Input() {
  cin >> l >> r >> c;
  if (l == 0 && r == 0 && c == 0)
    exit(0);

  for (int f = 0; f < l; f++) {
    for (int x = 0; x < r; x++) {
      for (int y = 0; y < c; y++) {
        cin >> m[f][x][y];

        if (m[f][x][y] == 'S') s = {f,x,y};
        else if (m[f][x][y] == 'E') e={f,x,y};
      }
    }
  }
}

int bfs(P start) {
    auto [sf,sx,sy] = start;
    queue<N> q;
    q.push({sf,sx,sy,0});
    v[sf][sx][sy] = true;

    while (!q.empty()) {
        auto
    }
}