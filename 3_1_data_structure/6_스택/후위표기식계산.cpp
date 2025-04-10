#include <iostream> // 입출력을 위한 헤더
#include <sstream>  // 문자열 스트림 처리 (문자열을 공백 기준으로 나누기 위함)
#include <stack>    // 후위 표기식 계산에 사용할 스택
#include <string>   // 문자열 사용
using namespace std;

// 두 피연산자(a, b)와 연산자(op)를 받아서 연산 결과를 반환하는 함수
int applyOp(int a, int b, char op) {
    if (op == '+')
        return a + b;
    if (op == '-')
        return a - b;
    if (op == '*')
        return a * b;
    if (op == '/')
        return a / b;
    return 0; // 예외 처리 (정상적인 경우가 아님)
}

// 후위 표기식 문자열을 받아서 계산 결과를 반환하는 함수
int evaluatePostfix(string expr) {
    stack<int> s;          // 연산에 사용할 스택
    stringstream ss(expr); // 공백 단위로 문자열 분리
    string token;          // 분리된 문자열(토큰)을 저장할 변수

    // 문자열 끝까지 반복
    while (ss >> token) {
        // 숫자이면 스택에 push
        if (isdigit(token[0])) {
            s.push(stoi(token)); // 문자열 → 정수 변환 후 push
        } else {
            // 연산자라면 스택에서 두 수를 꺼내 연산
            int b = s.top();
            s.pop(); // 두 번째 피연산자
            int a = s.top();
            s.pop();                              // 첫 번째 피연산자
            int result = applyOp(a, b, token[0]); // 연산 수행
            s.push(result);                       // 결과를 다시 스택에 push
        }
    }

    // 최종 결과는 스택의 최상단에 있음
    return s.top();
}

int main() {
    string expr;

    // 사용자로부터 후위 표기식 입력 받기
    getline(cin, expr); // 예: "3 4 + 2 * 7 /"

    // 후위 표기식 계산 함수 호출
    int result = evaluatePostfix(expr);

    // 결과 출력
    cout << result << endl;

    return 0;
}
