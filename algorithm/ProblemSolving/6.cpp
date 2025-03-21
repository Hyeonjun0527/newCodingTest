
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int N;
    cin >> N;
    int count = 1;
    int start = 1;
    int end = 1;
    int sum = 1;
    while (end != N) {//end가 start와 같은지점에서 시작이고 end가 뒤끝까지 가면 종료
        if (sum == N) {
            count++;//정답입니다. 정답인 케이스 센다.
            end++;//정답또잇나 봐야대니 뒤를 탐색해야지.
            sum += end;//그러면 자동으로 sum > N이 되겠지.
        } else if (sum > N) {
            start++;
            sum -= start -1;
        } else {
            end++;
            sum += end;
        }
    }
    cout << count << "\n";
    /*
구간합 투포인터 문제
1. 투포인터는 먼저 정렬을 해야 댐.
2. 투포인터는 꼭 배열이 있을 필요는 없음. 추상적인 배열도 가능
3. start end를 둘다 왼쪽에 아니면 양끝에 둘 지 정하자.

문제 : 연속된 자연수의 합 구하기
15 면 [(15), (7 8), (4 5 6), (1 2 3 4 5)]
4가지가 있어

이건 end와 start를 1로 두고 출발해. 서로 끝에 두면 연속된 자연수의 합 못구하잖아.

SUM = N 이면
count를 1증가 / end + 1증가 / sum갱신

SUM > N이면
START + 1증가 / SUM 갱신

SUM < N이면
end + 1증가 / SUM 갱신
 */
}
