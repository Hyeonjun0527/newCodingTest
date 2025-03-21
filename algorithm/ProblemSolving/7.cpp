#include <bits/stdc++.h>
using namespace std;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N,M;
    cin >> N >> M;
    //갑옷을 만드는거야.
    /*'
    6 (여섯 종류 줄게)
    9 (9 만들어)
    2 7 4 1 5 3
    이면 9를 만들어야해. 2 7 만들수 잇지
    4 5 가능하지.
    두가지 재료를 선택해서 합이 9인거 찾아야 해.
    그냥 콤비네이션 하면 시간초과고, 두개 택이니까 투포인터지. 시작과 끝점
    투포인터면 반드시 먼저 정렬 해야 대.

    1. 투포인터 문제면 반드시 정렬을 해라.

    그다음 포인터를 왼쪽 오른쪽에 둬. 그리고 왼쪽 오른쪽이 반전될 때까지 while문 돌려
    두 원소를 더해바 더한게 M=9보다 작으면 i를 당겨봐
    왜 i를 앞으로 당겨? 합이 더 커지니깐.
    더한게 M=9보다 크면 j를 뒤로 땅겨. 합이 작아지니깐 M을 찾을 수 있겠지
    M을 찾았어(즉, 더한게 M과 같아) 그럼 count 늘리고 i는 앞으로 땡기고 j도 땡겨 왜?
    왜냐하면 나는 정렬했고 중복되는 값은 없자나
    A[i] A[j]조합을 찾았었지? A[i]와 A[?]다른무언가로 가능한 조합은 없어
    A[j]와 A[?]의 조합도 불가능해. 하나 찾았으면 A[i] A[j]가 포함된
    2개의 쌍이 정답으로 나오는게 불가능한거야. 그러니까 둘다 떙겨
     */
    vector<int> A(N,0);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    sort(A.begin(), A.end());
    int count = 0;
    int i = 0;
    int j = N - 1;
    while (i < j) {
        if (A[i] + A[j] < M) {
            i++;
        } else if (A[i] + A[j] > M) {
            j--;
        } else {
            count++;
            i++;
            j--;
        }
    }
    cout << count <<"\n";
}
