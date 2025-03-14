#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct B {
  int num;
  int g;
  int s;
  int br;
  int grade;
};

int main() {

  int n,k;
  cin>>n>>k;//국가 등수알고싶은국가

  vector<B> b(n);//

  int num = 0;
  for (int i =0; i<n;i++) {
    int num,q,w,e;//q w e 금은동
    cin>>num>>q>>w>>e;
    b[i] = {num,q,w,e,0};

  }

  sort(b.begin(),b.end(),[](B x,B y) {
    if (x.g != y.g) {
      return x.g > y.g;
    } else if (x.s != y.s) {
      return x.s > y.s;
    } else {
      return x.br > y.br;
    }
  });

  b[0].grade = 1;
  for (int i = 1; i < n; i++) {
    if (b[i].g == b[i-1].g &&
      b[i].s == b[i-1].s &&
      b[i].br == b[i-1].br) {
        b[i].grade = b[i-1].grade;
      } else {
        b[i].grade = i+1;
      }
  }

  int sol = 0;
  for (int i =0; i<n;i++) {
    if (b[i].num == k) {
      sol = b[i].grade;
      break;
    }
  }
  cout << sol << "\n";

}



/* 

한 국가의 등수는 (자신보다 더 잘한 나라 수) + 1로 정의

모두 같다면 두 나라의 등수는 같
이 경우 3등은 없다.

결국에 정렬만 잘하면 돼? 아니야
정렬하면서 순위 정해줘야해.



*/