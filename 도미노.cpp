#include <iostream>
using namespace std;
int main() {
    int n;
    cin >> n;
    int sum = 0;
    for (int i = 0; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            sum += i + j;
        }
    }
    cout << sum;
}

/*


그러니까 N=4면
i = 0 1 2 3 4로 뽑고
j는 i보다 큰거로 하는거지?

0 : 0 1 2 3 4
1 : 1 2 3 4
2 : 2 3 4
3 : 3 4
4 : 4
질문 1 : 뭔가 피라미드 모양이네 ?
질문 2 : 중복조합은 0 <= i <= j <= N 이야?
질문 3 :
n
 H
r
 =
n+r−1
 C
r
이 공식이 왜 성립하지

그러니까 4개의 아직 어떤 과일인지 정해지지 않은 양자역학 과일이 칸막이 가장왼쪽
중간 오른쪽 어느쪽에 위치하는 문제로 환원할 수 있으니까 과일4개 + 칸막이 2개
6C2가 되는건가? 3H4 = 6C2야?

그런데 4개의 과일과 2개의 칸막이를 나열하는 경우의 수는 6C2인 이유가 뭐지?

핵심은:

지금 과일은 서로 구별되지 않는 같은 것 4개입니다.
(즉, 아직 종류가 정해지지 않은, 동일한 4개)

칸막이도 서로 구별되지 않는 같은 것 2개입니다.

이런 문제는 서로 구별되지 않는 물건을 나열하는 문제이며,
이를 "동일한 물건의 순열" 문제로 생각할 수 있습니다.

즉,

총 6개의 자리 중에서,

칸막이의 위치 2개를 먼저 정해주면 과일의 위치는 자동으로 정해집니다.

💡 예시로 이해해보면:
복사
편집
● ● ● ● ● ●  ← 6개의 빈 자리가 있을 때,
이 중 칸막이 위치 2개만 골라주면 나머지 4자리는 자동으로 과일이 들어가겠죠?


*/