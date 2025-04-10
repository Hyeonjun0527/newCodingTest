#include <iostream>
#include <vector>
using namespace std;
int main() {
  //2로나눈몫이 0이될때까지 나눠. 그리고 나눌때마다 나머지 있으면 1 없으면 0
  //그 나머지를 보관해 반대로 출력해
  int n;
  cin >> n;
  vector<int> a;

  if (n==0) {
    cout << 0;
    exit(0);
  }
  if (n==1) {
    cout << 1;
    exit(0);
  }

  if (n % 2== 0) {
    a.emplace_back(0);
  } else {
    a.emplace_back(1);
  }

  while (true) {
    n /= 2;
    if (n % 2 == 0) {
      a.emplace_back(0);
    } else {
      a.emplace_back(1);
    }
    if (n / 2 == 0) {
      break;
    }
  }
  for (int i = 0; i < a.size(); i++) {
    cout << a[a.size() - i - 1];
  }
  return 0;
}