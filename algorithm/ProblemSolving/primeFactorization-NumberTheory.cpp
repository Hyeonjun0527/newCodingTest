#include <iostream>
using namespace std;
//41-2, 41보기
void primeFactorization(int N) {
    // 2부터 시작해서 N을 소인수분해
    for (int factor = 2; factor * factor <= N; factor++) {
        while (N % factor == 0) {
            cout << factor << endl;//얘는 중복되는 소인수도 별개로 보니까 여기에 cout
            N /= factor;
        }
    }
    // N이 아직 1보다 크면 소수로 남아있는 것
    if (N > 1) {
        cout << N << endl;
    }

    /*
이런 예외상황이 생기는 이유는 무엇이냐면, N은 소인수분해하면 3가지 case가 있기 때문이야
case1 )sqrt보다 큰 수 x sqrt 보다 작은수 x sqrt보다 작은수 x ...
case2 )sqrt인 수 x sqrt인 수
case3 )sqrt보다 작은수 x sqrt보다 작은수 x sqrt보다 작은수 x ....

26이면 2,3,4,5로 for문 반복하곘지. 2는 처리하지만 13은 sqrt보다 큰 수라 처리 못하지

case 2, case3은 처리할 수 있어. for문이.
그리고 또 case2에서 sqrt인 수는 반드시 2개여야만 해
case 1에서 sqrt보다 큰 수는 단 하나 여야만 해.
     */
}

int main() {
    int N;
    cin >> N;

    if (N > 1) {
        primeFactorization(N);
    }

    return 0;
}
