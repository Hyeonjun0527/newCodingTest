#include <iostream>
#include <stack>
using namespace std;

int main() {
    int K, num;
    cin >> K;

    stack<int> s;  // 정수를 저장할 스택

    for (int i = 0; i < K; i++) {
        cin >> num;
        if (num == 0 && !s.empty()) {
            s.pop();  // 0이 입력되면 가장 최근에 쓴 수를 지운다.
        } else {
            s.push(num);  // 0이 아니면 스택에 숫자를 추가한다.
        }
    }

    // 스택에 남아 있는 값들의 합을 계산
    int sum = 0;
    while (!s.empty()) {
        sum += s.top();
        s.pop();
    }

    cout << sum << endl;  // 최종 합 출력
    return 0;
}
