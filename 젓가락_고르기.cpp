#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
using namespace std;
int main() {
  int n,k;
  cin >>n>>k;
  vector<int> a(n);
  
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  
  // for (int t : a) {
  //   cout << t << " ";
  // }
  int cnt = 0;
  for (int i = 0; i < n; i ++) {
    a[i]--;
  }
  vector<int> b(n,1);
  sort(a.begin(),a.end(),greater<int>());

  

  if (k==0) {
    cout << cnt;
  } else {
    cout << -1;
  }
}

/* 
무작위로 
Ai는 색이 i인 젓가락 개수야.


젓가락쌍 K개 만들고 싶어.
젓가락 X개 뽑앗어. 근데 
젓가락 랜덤으로 뽑히는데 멀 뽑히든
K개 쌍 만들 수 있으려면 X의 값은?

n=3 k = 2야. 
젓가락 3종류야
2개의쌍만들어야대
1 2 3
빨주노

X=6이라면 
다 뽑는다면 2개의 쌍 무조건 만들수잇ㅇ머.

젓가락이 n종류야.
.  . .  . . . . .
다 2개 이상인게 없다면 의미없겟다.
2개 이상인걸 필터링해.
그리고 

젓가락 x개 뽑으면 개떡같이 뽑아도 k개는 만드냐?
즉 최악으로 뽑으면 되는 case 찾아서
그 로직 돌리면 대겟다.


*/