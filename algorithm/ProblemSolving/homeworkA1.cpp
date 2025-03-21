
/*

피보나치 수열은 1 1 2 3 5 8 13
a1 a2 (a1+a2) (a2+a3) (a3+a4)
a5 = a3 + a4이다.
A_i = A_i-2 + A_i-1 일반항 식을 세울 수 있다.
반드시 분할 정복을 이용해야한다고 한다.
분할정복이 가능한지 보려면 문제를 하위문제로 나눌 수 있는지 보아야 한다.
그리고 problem instance가 비슷한 사이즈로 나눠질 수 있는지 보아야 한다.
예를 들어 F(10)을 구한다고 하면 F(10)=F(9) + F(8), F(9)= F(8) + F(7)
이런식으로 계속 하위문제가 나눠진다 F(n) = F(n-1) + F(n-2)이다.
여기서 F(n-1)은 F(n-2)보다 크다. 그러므로 F(n) >= 2F(n-2)이다.
F(n)은 그러므로 하위문제가 2배씩 늘어나니 매우 비효율적이고
선형 동차 재귀식을 특성방정식을 이용하여 해를 구하면
(1+sqrt(5))/2 = 1.618(황금비)^2의 시간복잡도로 표현된다.
즉, 단순히 분할정복을 이용하면 시간복잡도가 안드로메다로 간다는 것을 알 수 있다.
하지만 분할정복으로 시간복잡도를 logN으로 줄이는 방법이 있다.
피보나치, 루카스 수열과 같은 선형재귀식은 행렬 거듭제곱 방법을 사용할 수 있다는
점을 활용하면,
F(n)    = 1 1 ^n-1 F(1)
F(n-1)  = 1 0     F(0)
이 되고 행렬 거듭제곱하는 함수를 n-1번 호출하면 해결된다.
여기서 거듭제곱연산을 분할정복 알고리즘을 사용하면 a^n = a^(n/2) x a^(n/2)이 된다.
하위문제가 절반씩 줄어듬을 알 수 있다.
n이 짝수일때 a^n = a^(n/2) x a^(n/2)가 되고
n이 홀수일때는 a^5 = a^(2) x a^(2) x a^1이 된다.
이렇게 O(logN)의 시간복잡도로 피보나치수열 문제를 해결할 수 있다.
*/
#include <iostream>
#include <vector>


using namespace std;
/*
 * a b i j
 * c d k l
 *
 * a*i+b*k a*j+b*l
 * c*i+d*k c*j+d*l
 */
vector<vector<long long>> multiply(const vector<vector<long long>>& a,
                                   const vector<vector<long long>>& b) {
    vector<vector<long long>> c(2, vector<long long>(2));
    c[0][0] = a[0][0] * b[0][0] + a[0][1] * b[1][0];
    c[0][1] = a[0][0] * b[0][1] + a[0][1] * b[1][1];
    c[1][0] = a[1][0] * b[0][0] + a[1][1] * b[1][0];
    c[1][1] = a[1][0] * b[0][1] + a[1][1] * b[1][1];
    return c;
}

vector<vector<long long>> pow(vector<vector<long long>> a, long long n) {
    if (n == 0) {
        return {{1, 0}, {0, 1}};//단위행렬
    }
    vector<vector<long long>> temp = pow(a, n / 2);
    if (n % 2 == 0) {
        return multiply(temp, temp);
    } else {
        return multiply(multiply(temp, temp), a);// a^(n/2) * a^(n/2) * a
    }
}

long long fibonacci(long long n) {

    if (n == 0) {
        // cout << 0 << endl;
        return 0;
    }
    if (n == 1) {
        // cout << 1 << endl;
        return 1;
    }

    vector<vector<long long>> M = {{1, 1}, {1, 0}};
    vector<vector<long long>> sol = pow(M, n-1);

    /* 행렬 거듭제곱의 결과를
     * a b
     * c d
     * 라고 하면
     * a * F(1) + b * F(0) = F(n)이다. 즉, a = F(n)
     */
    return sol[0][0];

}

int main() {
    for(int i = 0; i <= 15; i++){
        cout << fibonacci(i) << endl;
    }
    return 0;
}
