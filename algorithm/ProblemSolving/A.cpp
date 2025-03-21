// Authored by : chjh2129
#include <bits/stdc++.h>
using namespace std;

// 스택을 활용해서 괄호의 짝을 찾는 알고리즘은 매우 유명합니다.
// 열린 괄호 '('와 '['를 스택에 넣습니다.

// 닫힌 괄호 ')'를 만났을 때, 스택의 top()이 '('인지 확인합니다.
// 만약, '('가 아니거나 스택이 비어있다면 괄호의 짝이 맞지 않는다고 판단할 수 있습니다.

// ex)  ()), [)

// 닫힌 괄호 ']'를 만났을 때, 스택의 top()이 '['인지 확인합니다.
// 만약, '['가 아니거나 스택이 비어있다면 괄호의 짝이 맞지 않는다고 판단할 수 있습니다.

// ex) []],  (]

// 짝이 맞다면 스택을 pop()한 뒤, 이어갑니다.
// ex) [], ()

// 모든 쿼리가 끝났을 때, 스택이 비어있지 않다면 괄호의 짝이 맞지 않습니다.

// ex) ((()
/*

(
&

)
no

 */
string s;

string solve(){
    stack<char> stk;
    for(auto c : s){
        if(c == '(' || c == '[') stk.push(c);
        else if(c == ')'){
            if(stk.empty() || stk.top() != '(') return "no";
            stk.pop();
        }
        else if(c == ']'){
            if(stk.empty() || stk.top() != '[') return "no";
            stk.pop();
        }
    }
    return (stk.empty() ? "yes" : "no");
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    // getline(cin) : 공백을 포함해서 한 줄을 입력받음
    while(getline(cin, s), s != "."){
        // solve & output
        cout << solve() << '\n';
    }
}