/*
C가 gcd(A,B)로 나누어지는지 확인 하고
나누어지면
Ax+By=gcd(A,B)의 해를 구하고
나누어지지않으면 -1 리턴이야

x,y가 정수여야만 할 때 (정수 일 때) 방정식의 해가 있으려면
C가 gcd(A,B)로 나누어 떨어지면 해가 있어
그 해는 Ax + By = gcd(A,B) 의 해에 C/gcd(A,B)를 곱한거야. 비율이 같기 떄문에
gcd(A,B)로 나누고 C를 곱해주면 그게 답이야.

이거에서 x와 y값을 구했어. 그리고 그걸 스케일링할 수 있지?
2x+3y = 8의 x,y가 있겠지 1,2가 있겠지
그러면 자동으로 이게 도출 돼. 2x+3y = 16에는 2,4가 있겠구나
선형 방정식의 비례성이야.
 */

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// 최대공약수(GCD) 계산 함수
long gcd(long a, long b);

// 확장된 유클리드 알고리즘 실행 함수

long extendedEuclid(long A, long B, long &x, long &y);

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    long A, B, C;
    cin >> A >> B >> C;

    // A와 B의 최대공약수를 계산
    long gcdValue = gcd(A, B);

    // C가 gcd(A, B)로 나누어 떨어지지 않으면 해가 존재하지 않음
    if (C % gcdValue != 0) {
        cout << -1 << "\n";
    }
    else {
        // C / gcd(A, B)의 몫을 구함
        int multiplier = (int)(C / gcdValue);//비례성 하려고.

        // 확장된 유클리드 알고리즘을 실행하여 x, y 값 계산
        long x, y;

        // 확장된 유클리드 알고리즘을 실행하여 x, y 값 계산
        extendedEuclid(A, B, x, y);

        // 해를 출력
        cout << x * multiplier << " " << y * multiplier;
    }
}

// 확장된 유클리드 알고리즘을 사용하여 x, y 값을 구하는 함수
long extendedEuclid(long A, long B, long &x, long &y) {

    //Ax + By = GCD(A,B) = GCD(B,A%B) 인데 A%B=0가 0이야?

    // 그러면 Bx + (A%B)y = GCD(B,A%B)인데 B=0이 아니고,  A%B ==0인 상황이잖아?
    //GCD(B,0) = B 이므로 x = 1, y = 0 여기서 B가 A변수에 담긴거고 A%B가 B 변수에 담긴거잖아.
    //gcd는 여기서 A에 담긴 B야. 그래서 A를 리턴해.
    //마지막 상황이야.
    if (B == 0) {
        x = 1;
        y = 0;
        return A;
    }
    long x1, y1; // 임시 변수
    long gcd = extendedEuclid(B, A % B, x1, y1); // 재귀적으로 해를 구함
    //재귀적으로 마지막 스택 밑바닥 top까지 왔어. 거기서 gcd를 리턴해. 그리고 다시 x와 y 계산해.
    //그리고 gcd 리턴. 다시 x와 y 계산. 이거 반복

    // 현재 A에는 이전 B'가 들어가지? 그러니 x에는 y'이 들어가. A' = x1  B' = y1이야.
    //
    // 현재 B에는 이전 A'%B'가 들어가지? 얘는 A'를 B'로 나눈 나머지 r이지? A' = B'*몫 + 나머지잖아?
    // 그러니 나머지 = A' - 몫*B'이야. y = x1 - (A/B) * y1 // 나머지와 몫은 현재 나머지 현재 몫이야.
    // x = y',  y=x'-y'q = r = A-BQ
    x = y1;
    y = x1 - (A / B) * y1;

    return gcd;
}
// 최대공약수(GCD)를 계산하는 함수
long gcd(long A, long B) {
    if (B == 0)
        return A;
    else
        return gcd(B, A % B);
}
