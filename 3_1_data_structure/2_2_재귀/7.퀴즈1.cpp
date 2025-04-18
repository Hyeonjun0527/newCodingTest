#include <algorithm>
#include <iostream>
using namespace std;

int main() {
    string a;
    cin >> a; // 사용자로부터 문자열 입력

    // 문자열의 길이를 이용하여 역순으로 출력
    for (int i = 0; i < a.length(); i++) {
        cout << a[a.length() - 1 - i];
    }
    cout << endl;

    // 예시:
    // 입력: "Hello"
    // 출력: "olleH"
    return 0;
}
