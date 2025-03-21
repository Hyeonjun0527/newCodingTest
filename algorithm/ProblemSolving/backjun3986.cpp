#include <iostream>
#include <stack>
using namespace std;

int main() {
    int N;
    cin >> N;

    int good_word_count = 0;  // 좋은 단어의 개수를 저장하는 변수

    for (int i = 0; i < N; i++) {
        string word;
        cin >> word;

        stack<char> s;  // 스택을 사용하여 쌍을 맞출 수 있는지 확인
        /*
        A
        B가 들어가 다른 단어니까 추가하자
        AB
        A가 들어가 다른 단어니까 추가하
        ABA

        ...

        1. A
        추가
        2. AB
        B가나오니 팝
        3. A
        A나오니 팝
        4. 공집합

         */
        for (char c : word) {
            if (!s.empty() && s.top() == c) {
                s.pop();  // 같은 문자가 나오면 스택에서 제거하여 쌍을 맞춤
            } else {
                s.push(c);  // 그렇지 않으면 스택에 문자를 추가
            }
        }

        // 스택이 비어 있으면 "좋은 단어"
        if (s.empty()) {
            good_word_count++;
        }
    }

    cout << good_word_count << endl;  // 결과 출력

    return 0;
}
