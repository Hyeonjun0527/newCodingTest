
#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  int n;
  cin >> n;
  vector<int> a(n);
  vector<int> b(n);
  for (int i = 0; i < n; i++) {
    int tmp;
    cin >> tmp;
    a[i] = tmp;
    b[i] = tmp;
    b[i] += i + 1;
  }

  int mx = -99999;
  int mn = INT_MAX;
  int xi = 0;
  int ni = 0;
  for (int i = 0; i < n; i++) {
    if (mx < b[i]) {
      mx = b[i];
      xi = i;
    }
    if (mn > b[i]) {
      mn = b[i];
      ni = i;
    }
  }

  cout << xi << " " << ni;

  

  swap(a[0],a[n-1]);

}

/*

가장 손해인걸 찾아야해
그런건 Ai가
*/