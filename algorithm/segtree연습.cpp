// n m k 주어지고 m+k 만큼 a,b,c주어짐 a=1이면 업데이트 2면 쿼리
#include <iostream>
#include <vector>
using namespace std;
vector<int> t;
vector<int> a;
// 1,0,n-1, elrs erls, isei
int mrg(int a, int b) { return a + b; };
int st(int n, int s, int e) {
  if (s == e)
    return t[n] = a[s];
  int mid = s + (e - s) / 2;
  return t[n] = mrg(st(n, s, mid), st(n, mid + 1, e));
}
int qry(int n,int s,int e,int l,int r) {
  if (e < l || r < s) return 0;
  if (e <= r || l <= s) 
}

int main() {
  int n, m, k;
  cin >> n >> m >> k;
  // 1,0,n-1
  a.resize(n);
  t.resize(n * 4);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  // st(1,0,n-1);
  for (int i = 0; i < m + k; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    if (a == 1) {
      // upt(1,0,n-1,b-1,c);
    } else {
      cout << qry(1, 0, n - 1, b - 1, c - 1);
    }
  }
}