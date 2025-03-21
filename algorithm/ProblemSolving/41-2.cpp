#include <bits/stdc++.h>
using namespace std;

/*
소인수 찾기. 나누어 떨어지면 소인수야
소인수를 찾으려면 찾고나서, 소인수의 배수들을 싹 지워야 돼. 지우는게 n /= k 야.
소인수들은 sqrt(N)초과와 그 반대로 유형이 나눠져
N의 소인수를 구하려면 어케해? 소인수 분해를 해야지 20 = 2 2 5 잖아? 이걸 컴터가 어케해. 사람이 하는거랑 똑같이 해.
소수로 나누고 다시 가장작은 소수로 나누고...20이 10이되고 10이 5가 됐어. 5는 소수니까 2 2 5
 vector<long> primeFactorization(long N) {
     vector<long> primeFactors;
     // 2로 나눌 수 있을 때까지 나누기
     while (N % 2 == 0) {
         primeFactors.push_back(2);
         N /= 2;
     }
     // 3 이상의 홀수들로 나누기 (2 이후의 소수들)
     for (long i = 3; i * i <= N; i += 2) {
         while (N % i == 0) {
             primeFactors.push_back(i);
             N /= i;
         }
     }
     // 마지막으로 남은 N이 소수인 경우 처리
     if (N > 2) {
         primeFactors.push_back(N);
     }
     return primeFactors;
 }
먼저 2로 나눠보는거임. 3,4,5,6,7, 다 나눠보는거임. 나눴어. 약수라는건 확인됐네?
소인수배열에 담을까? 담기전에 생각해볼게 있어.
36 = 2 x 2 x 3 x 3. 이걸 예시로 해보면
2,3,4,5,6 이렇게 다 확인하면, 4와 6은 의미가 없잖아. 그치?
2~sqrt(n)까지 반복을 하는데 sqrt(n)이 유동적으로 축소되면 더 효율적인 거지.
36 = 2 x 2 x 3 x 3에서 현재 k가 2지 그러면 2를 다 제거해버리고 N을 축소하자. 9 = 3 x 3이 되겠네.
그러면 이제 3까지만 반복을 하면 되고, 3만 담으면 되는거야.
이러면 다 될 까?
소인수분해할 때 소인수들의 형태는 이렇게 표현이 가능해.
case 1 ) n = sqrt(n)보다 큰 수 x sqrt(n)보다 작은 수
case 2 ) n = sqrt(n) x sqrt(n)
case 3 ) n = sqrt(n)보다 작은 수 x sqrt(n)보다 작은 수 x sqrt(n)보다 작은 수 x .....

case 2 case 3는 전부 처리가 되었겠고, case 1은 sqrt(n)보다 작은 수는 나눠질거야.
예를 들어 35 = 7 x 5 라면 5는 처리가 되었고 N = 7인 상태로 남아있게 된다는거지.
그래서 그 7까지 담아줘야 완벽하다는 거야. 그런데 이런 반론이 가능해.
for문을 다 돌리고 나서 sqrt(n)보다 큰 수가 2개라면??? 하지만 그런 경우는 아시다시피 없어. 그러므로 1번만 처리하면 돼.

*/

vector<long> findUniquePrimeFactor(long N) {
    vector<long> primeFactors;

    for (long k = 2; k * k <= N; k++) {
        if (N % k == 0) {
            primeFactors.push_back(k);
            while (N % k == 0) {
                N /= k;
            }
        }
    }
    if (N > 1) {
        primeFactors.push_back(N);
    }

    return primeFactors;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    long N;
    cin >> N;
    vector<long> primeFactors = findUniquePrimeFactor(N);

    for (long factor : primeFactors) {
        N -= N / factor;
    }
    cout << N << endl;

}
