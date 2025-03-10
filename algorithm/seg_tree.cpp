#include <iostream>
#include <vector>
using namespace std;
vector<int> a, t;

int mrg(int a, int b) { return a + b; }

int st(int n, int s, int e) {
  if (s == e)
    return t[n] = a[s];
  int mid = s + (e - s) / 2;
  return t[n] = mrg(st(n, s, mid), st(n, mid + 1, e));
}
int qry(int n, int s, int e, int l, int r) { // elrs erls
  if (e < l || r < s)
    return 0;
  if (e <= r && l <= s)
    return t[n];
  int mid = s + (e - s) / 2;
  return mrg(qry(n, s, mid, l, r), qry(n, mid + 1, e, l, r));
}
int upt(int n, int s, int e, int i, int v) { // isei
  if (i < s || e < i)
    return t[n];
  if (s == e)
    return t[n] = v;
  int mid = s + (e - s) / 2;
  return t[n] = mrg(upt(2 * n, s, mid, i, v), upt(2 * n + 1, mid + 1, e, i, v));
}
int main() {
  int n, m, k;
  cin >> n >> m >> k;
  int ROOT = 1;
  int START = 0;
  int END = n - 1;
  a.resize(n);
  t.resize(n * 4);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  st(ROOT, START, END);
  for (int i = 0; i < m + k; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    if (a == 1) {
      upt(ROOT, START, END, b - 1, c);
    } else {
      cout << qry(ROOT, START, END, b - 1, c - 1) << "\n";
    }
  }
}
/*
백준 2042번
5 2 2
1
2
3
4
5
1 3 6
2 2 5
1 5 2
2 3 5

17
12
 */
