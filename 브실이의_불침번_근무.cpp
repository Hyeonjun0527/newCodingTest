#include <iostream>
using namespace std;
int main() {
    long long n, m;
    cin >> n >> m;
    //100-2는 98
    //(100 + 55) % 4
    //(100)%4 = 
    //(55)%4

    long long a = 1;
    long long b = 1;
    for (int i = 1; i <= n; i++) {//n이 10^6승 m도 10^6 => (10^6)^(10^6)
        a *= m;
        a%=1000000007;
    }
    for (int i = 1; i <= n; i++) {
        b *= (m-1);
        b%=1000000007;
    }

    long long ans = ((a - b) + 1000000007) % 1000000007;

    if (m == 1) {
        // N >= 1이므로 그대로 1 출력
        cout << 1 << "\n";
        return 0;
    }

    cout << ans;
}


/* 
1000000007 다르게 표현하는법 공부해보자.
N제곱이란건 머야? N번 곱햇다는거야.
AAA
AAB
ABA
BAA
ABB
BBA
BBB

5명이 있어 4명으로 꽉채울 수도 있겠지.

그러면 4

A가 0개인경우 
A가 1개인경우
A가 2개인경우

7개가 되네 즉, 중복된 게 있는 순열
중복 순열이네. 아니야. 중복순열이 아니야 서로다른 n개를 r개만큼 뽑아서 순서 나열하는거가 중복순열임.

nPr이라고 하자.
그리고 r!으로 나누면 됨.
2^n/r! 하면 될듯?

3P2 / 2
3 * 2 * 1/ 2



*/