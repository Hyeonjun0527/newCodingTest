#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
using namespace std;

bool isBalanced(const string &str) {
    stack<char> s;
    // 닫는 괄호 -> 여는 괄호 맵핑
    static const unordered_map<char, char> pairs = {
        {')', '('}, {'}', '{'}, {']', '['}};

    for (char c : str) {
        // 여는 괄호인 경우
        if (c == '(' || c == '{' || c == '[') {
            s.push(c);
        }
        // 닫는 괄호인 경우
        else if (c == ')' || c == '}' || c == ']') {
            if (s.empty()) {
                return false; // 스택이 비어있는데 닫으려 하면 불일치
            }
            // 맵핑된 여는 괄호와 비교
            if (s.top() != pairs.at(c)) {
                return false;
            }
            s.pop();
        }
        // 그 외 문자
        else if (isalnum(c)) {
            // 알파벳, 숫자는 무시
            continue;
        } else {
            // 여기서는 기타 문자도 무시한다고 가정
            continue;
        }
    }

    // 모든 괄호가 스택에서 정상적으로 pop되어야 균형
    return s.empty();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    // 만약 각 줄에 공백이 포함될 수 있으면
    // 아래 코드를 cin 대신 getline으로 수정 필요

    while (n--) {
        string str;
        cin >> str;
        // 검사 후 출력
        cout << (isBalanced(str) ? "T\n" : "F\n");
    }
    return 0;
}
