
/*
(1) 구현 방식
start와 end를 둬 그리고 처음에 쭉 스캔해.
그리고 팰린드롬 로직을 돌린다.
start가 <만나면 >만날때까지 div 같은 string을 만들어서 큐에 넣는다.
끝났으면 end가 >만나면  /만나고 < 만날 때까지 string을 합쳐 vid가 되겠지 그거를 반대로 돌리고 큐에서 꺼내서 같은지 봐
그런데 end가 >만나고 바로 /만나면 <만날 때까지 continue해. 그리고 >가 를 만나야 해.
다르면 break false 같으면 반복
넣을 때 일단 이상하면 false한다. 버퍼개념이 있어야해. 버퍼 on 하고 버퍼 off한다.
처음에 이런식으로 만들었다.
이렇게 만들었을때 생기는 문제점이 무엇이냐
<div><a></a></div>와 같이 열린태그들이 전부 등장하고 닫힌태그가 등장하는 구조는 처리하지만
<div><a></a><a></a></div>와 같이 닫힌 태그가 중간에 등장하는 구조는 처리하지 못했다.
그래서 방법을 바꿔야 했다.
일단 투포인터 방식으로는 불가능하다고 생각했다.
열린태그를 만나면 넣고 닫힌태그를 만나면 꺼내는 식으로 해야할 것 같았다.
태그의 순서가 지켜지도록 스택을 사용했다. 나중에 열린 태그는 가장 빨리 닫혀야하기 때문이다.
먼저 열린태그를 만났을때 해야 할 행동들을 정의했고, 그다음에 닫힌태그를 만났을때 해야할 것들을 정의헀다.

(2) 시간복잡도
N개의 문자열 전체를 순회하니 N의 시간복잡도가 걸린다.
while문 내부의 while문을 순회하는 경우가 있는데 이 부분은 전부 N이하의 횟수로 i를 늘리는 작업이다.
그러므로 총 시간 복잡도에 영향을 주지 않는다.
내부 while문이 순회하는 만큼
전체 while문의 순회횟수가 줄어드는 구조를 가지고 있기 때문에 전체 시간복잡도는 N이다.
*/
#include <iostream>
#include <stack>
#include <string>

using namespace std;

int main() {
    string input_string;
    getline(cin, input_string);

    stack<string> tag_stack;
    bool sol = true;
    int i = 0;

    while (i < (int)input_string.size() && sol) {

        if (input_string[i] == '<') {
            i++;


            if (input_string[i] != '/') {  // 열린태그

                // 태그명 만들어
                string tag_name;
                while (input_string[i] != '>' && input_string[i] != ' ' && input_string[i] != '/') {
                    tag_name += input_string[i];
                    i++;
                }

                // 깍두기야
                if (input_string[i] == '/') {
                    // > 만날때까지 건너뛰어
                    while (input_string[i] != '>') {
                        i++;
                    }
                    i++;  // '>' 넘김
                    continue;
                }

                // 공백 만나면 >까지 이동해
                while (input_string[i] != '>') {
                    i++;
                }
                i++;  // '>' 넘김

                // 여는 태그는 스택에 추가
                tag_stack.push(tag_name);

            } else {      // </이라면 닫는 태그야.

                i++;  // 다음으로 이동

                // 태그명 만들어
                string tag_name;
                while (input_string[i] != '>' && input_string[i] != ' ' && input_string[i] != '/') {
                    tag_name += input_string[i];
                    i++;
                }

                // 공백 만나면 >까지 이동해
                while (input_string[i] != '>') {
                    i++;
                }
                i++;  // '>' 넘김

                // 태그 잘 잇는지 같은 놈 맞는지
                if (tag_stack.empty() || tag_stack.top() != tag_name) {
                    sol = false;
                    break;
                } else {
                    tag_stack.pop();  // 매칭되면 스택에서 제거
                }
            }

        } else {  // <가 아니면..
            i++;
        }
    }

    // 스택이 비어있지 않으면 태그가 제대로 닫히지 않은 경우
    if (!tag_stack.empty()) {
        sol = false;
    }

    if (sol)
        cout << "true" << endl;
    else
        cout << "false" << endl;

    return 0;
}
