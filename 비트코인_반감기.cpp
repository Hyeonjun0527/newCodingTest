#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
int main() {
  ll r,k,m;
  cin >>r>>k>>m;
  //1 2 1
  // 100
  for (int i = 0; i < (m/k); i++) {
    r /= 2;
  }
  cout << r;
}
/* 

소수점 발생시 버린다. 보상은 정수

*/
