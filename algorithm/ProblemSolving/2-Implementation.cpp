#include <iostream>
#include <vector>
using namespace std;


int N = 0;
vector<int> A(1000);

long sum = 0;
long max1 = 0;
double result = 0;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }

    for (int i = 0; i < N; i++) {
        if (A[i] > max1) {
            max1 = A[i];
        }
        sum += A[i];
    }
    //실수형 나눗셈 하기 위해 먼저 100.0을 곱한다.
    //이게 새로운 평균점수야.
    //모든 점수를 max로 나누고 100을 곱하는거니까. 이렇게 해도 대.
    result = sum * 100.0 / max1 / N;
    cout << result << "\n";
}

// long 과 double을 연산하면 double이야. 그래서 100.0을 곱한거야.
//long 말고 ll 이런식으로 하는 방법 있었는데 그거 뭐였더라.
