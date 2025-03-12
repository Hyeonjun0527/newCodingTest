#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;
int main() {
  int n,m;
  cin>>n>>m;
  int k;
  
  vector<int> a;
  map<int, int> mp;

  int count = 0;
  for (int i = 0; i < n; i++) {
    int k;
    cin >> k;
    count+=k;
    for (int j = 0; j < k; j++) {
      int tmp;
      cin >> tmp;
      if (!mp[tmp]) {
        mp[tmp] = 1;
      } else {
        mp[tmp]++;
      }
    }
  }
  int cnt =0;
  for (auto t : mp) {
    if (t.second >= m) {
      cnt++;
    }
  }

  cout << cnt;
}
/* 


학번이 주어지고 학생 수 구하면 대

M 번이상 수업들은 학생 궁금해
(학생번호, 수업들은 수) 이렇게 데이터화

*/