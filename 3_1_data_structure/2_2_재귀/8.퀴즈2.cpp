#include <iostream>
#include <vector>
using namespace std;

int main() {
    // 10진수 정수 n을 2진수로 변환해서 역순으로 출력하기
    int n;
    cin >> n;
    vector<int> a;

    // n이 0이면 바로 0 출력 후 종료
    if (n == 0) {
        cout << 0;
        return 0;
    }
    // n이 1이면 바로 1 출력 후 종료
    if (n == 1) {
        cout << 1;
        return 0;
    }

    // n을 2로 나눈 나머지를 벡터에 저장(첫 자리)
    if (n % 2 == 0) {
        a.emplace_back(0);
    } else {
        a.emplace_back(1);
    }

    // n을 계속 2로 나누면서 나머지를 저장
    while (true) {
        n /= 2; // 몫
        if (n % 2 == 0) {
            a.emplace_back(0);
        } else {
            a.emplace_back(1);
        }
        // n을 또 2로 나누었을 때 몫이 0이 되면 종료
        if (n / 2 == 0) {
            break;
        }
    }

    // 벡터 a에는 이진수가 역순으로 저장되어 있으므로, 거꾸로 출력
    for (int i = 0; i < (int)a.size(); i++) {
        cout << a[a.size() - 1 - i];
    }
    cout << endl;

    // 예시:
    // 입력: 10 -> a 에는 [0,1,0,1], 출력은 "1010"
    return 0;
}
