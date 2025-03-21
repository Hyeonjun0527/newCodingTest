

/*
단순히 전부 체크했다가는 100000... 1만자리수 ~ 9999999(1만자리수)니까 10^10000의 시간복잡도가 걸린다.
그런데 아무리 생각해도 직접 확인하는 수밖엔 없는거 같은데..? 7의 배수인지 아닌지 판단하는건 %7하는거다 그런데 각각 %7해도 된다. 분배법칙
모듈러 연산 분배법칙은 (A+B)%C=((A%C)+(B%C))%C라고 한다. 또 (A×B)%C=((A%C)×(B%C))%C라고 한다. 나머지만 알아도 된다는거
이걸 활용하자. 그리고 단순히 전부 체크하지 않고 다른 방법 생각해보자. 어케 할까 테스트케이스를 잘 분석해보면 n=2에서 계산했던 걸 그대로 3에서 쓸 수 있다.
그러면 dp테이블을 만들자. 모든 경우의 수 누적해서 저장해야 함. n=2의 것 + 7 , n=2의 것 x 7 이런식으로 가능함.
dp테이블 구조는 n으로 나뉘어야함. DP[1~10000][0~6][0~6]
0~6은 합했을 때 나머지와 곱했을 때 나머지임. 합했을때 나머지3 곱했을때 나머지 2 개수도 다 구해야 함. 왜냐면 그게 언젠가 [0][0]이 될 수 있음.
70 -> 7+0 = 7
               7 x 0 = 0
77 -> 7+7 = 14
        -> 7 x 7 = 49
777-> 7+7 + 7 = 21
         -> 7 x 7 x 7 = pow(7,3)
 */

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
long long DP[10001][7][7] = {};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int T, N;
    cin >> T;

    //초기화 1 2 3 4 5 6 7 8 9
    DP[1][1][1] = 2;//1자리수이고, 합의 나머지 0 곱의 나머지 0 인 경우 1가지.
    DP[1][2][2] = 2;
    DP[1][3][3] = 1;
    DP[1][4][4] = 1;
    DP[1][5][5] = 1;
    DP[1][6][6] = 1;
    DP[1][0][0] = 1;


    // 1 0 0 : 나눠서 0이되는 1의 자리수, 1 0 1
    for (int n = 1; n <= 9999; n++) {
        for (int current_sum_mod = 0; current_sum_mod <=6; current_sum_mod++) {
            for (int current_mul_mod = 0; current_mul_mod <= 6; current_mul_mod++) {
                if (DP[n][current_sum_mod][current_mul_mod] != 0) {//0이면 말이 안댐 존재하지 않는 숫자임

                    for (int i = 0; i <= 9; i++) {
                        int next_sum_mod = (current_sum_mod + i) % 7;
                        int next_mul_mod;
                        if (i == 0) {
                            next_mul_mod = 0;
                        }else {
                        next_mul_mod = (current_mul_mod * i) % 7;
                        }
                        //누적을 시켜야 하므로
                        DP[n+1][next_sum_mod][next_mul_mod] =
                            (DP[n+1][next_sum_mod][next_mul_mod] + DP[n][current_sum_mod][current_mul_mod]) % MOD;
                    }
                }
            }
        }
    }

    for (int i = 0; i < T; i++) {
        cin >> N;
        cout << DP[N][0][0] << endl;
    }

    return 0;

}
