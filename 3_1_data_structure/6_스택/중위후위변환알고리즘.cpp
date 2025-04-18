#include <iostream>
#include <stack>
#include <string>
using namespace std;

// 연산자의 우선순위를 반환하는 함수
int precedence(char op) {
    if (op == '+' || op == '-')
        return 1; // 덧셈, 뺄셈: 낮은 우선순위
    if (op == '*' || op == '/')
        return 2; // 곱셈, 나눗셈: 높은 우선순위
    return 0;
}

// 중위 표기식 → 후위 표기식으로 변환하는 함수
string infixToPostfix(string expr) {
    stack<char> opStack; // 연산자와 괄호를 저장할 스택
    string result;       // 최종 결과 문자열 (후위 표기식)

    // 수식 문자열을 왼쪽부터 한 글자씩 읽기
    for (char c : expr) {
        if (isdigit(c) || isalpha(c)) {
            // 숫자나 문자(피연산자)는 결과 문자열에 바로 추가
            result += c;
        } else if (c == '(') {
            // 여는 괄호는 무조건 스택에 push
            opStack.push(c);
        } else if (c == ')') {
            // 닫는 괄호가 나오면 여는 괄호를 만날 때까지 연산자 pop
            while (!opStack.empty() && opStack.top() != '(') {
                result += opStack.top();
                opStack.pop();
            }
            if (!opStack.empty())
                opStack.pop(); // 여는 괄호 제거
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            // 연산자일 경우 우선순위 비교
            while (!opStack.empty() &&
                   precedence(opStack.top()) >= precedence(c)) {
                // 스택 위에꺼(top) vs 현재꺼(c)
                //  스택 위의 연산자 우선순위가 같거나 높으면 pop하여 출력
                result += opStack.top();
                opStack.pop();
            }
            // 현재 연산자를 스택에 push
            opStack.push(c);
        }
    }

    // 수식이 끝난 후, 스택에 남은 연산자를 모두 결과에 추가
    while (!opStack.empty()) {
        result += opStack.top();
        opStack.pop();
    }

    return result; // 완성된 후위 표기식 문자열 반환
}

int main() {
    string expr;
    getline(cin, expr); // 사용자로부터 수식 입력 (예: (3+4)*2)

    string postfix = infixToPostfix(expr); // 중위 → 후위 변환
    cout << "후위 표기식: " << postfix << endl;

    return 0;
}
