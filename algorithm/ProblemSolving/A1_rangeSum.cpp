#include <iostream>
#include <vector>
using namespace std;
/*
배열의 크기 질의의 개수
배열의 원소
질의인스턴스
5 3
10 20 30 40 50
1 3
2 4
1 5

*/
int main() {
    int N,Q;
    cin >> N >> Q;
    vector<int> A(N+1);
    vector<long long> prefix(N + 1, 0);

    //배열입력받고 구간합 만들어
    for (int i = 1; i <= N; ++i) {
        cin >> A[i];
        prefix[i] = prefix[i - 1] + A[i];
    }//S[i] = S[i-1] + A[i];

    //구간합 질의야 구간합을 물어보면 이렇게 구할 수 있어.
    for (int q = 0; q < Q; ++q) {
        int L,R;
        cin >> L >> R;
        long long sum = prefix[R] - prefix[L - 1];//[L,R] [1,3]이면 S[3] - S[0]
        cout << sum << "\n";
    }
    return 0;
}