/*
4 3 6 8 7 5 2 1 이라는 수열을 1~n의 수를 스택에 넣었다가 뽑아서 만들 수 있는지이다.
스택에 먼저 1 2 3 4를 넣는다. 그리고 4를 빼고 3을 뺀다. 그래서 4 3수열을 만들었다.
그리고 6을 결과수열에 넣기 위해. 5를 넣고 6을 넣고 6을 뺀다. 그리고 8을 만들기 위해 7을 넣고 8을 넣고 8을 뺀다.
7만들어야하니 7을 뺀다. 그리고 5를 빼고 2를 빼고 1을 뺀다. 1 2 5 3 4는 만들 수잇나. 1넣고 1빼고 2넣고 2빼고 3 4 5를 넣고 5를  뺀다. 그리고 4를빼고 3을 뺸다. 그러면 4를 못만든다.
실패하는 경우는 언제냐? 실패하는 경우는 스택의 가장 위의 수(4)가 만들어야하는 수(3)보다 크다면  수열 출력 불가능이다.
만약 만들어야 하는 배열이 1 2 5 3이었다면 스택 가장 위의 수가 만들어야하는 수보다 크다고 하더라도 수열 출력 가능해
하지만, 입력은 반드시 1~n까지 모든 수를 가지고 있어. 그걸 알아야 해.

4를 만나면 1 2 3 4를 넣어 4를 빼 ( 4 )
3을 만나면 3을 빼. ( 4 3 )
6을 만나면 5 6을 넣어. 6을 빼 (4 3 6)
...

1을 만나면 1을 넣어. 1을 빼 {}
2를 만나면 2를 넣어 2를 뺴 {}
5를 만나면 3,4,5를 넣어 5를 빼 {3,4}
3을 만나면 top은 4잖아. 4를 빼야하잖아. top(4)과 만난대상(3)을 비교했을때 탑이 더 크면 망함.
4를 만나면 망해. 불가능. {}
 */


#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N;
    cin >> N;
    vector<int> A(N, 0);
    vector<char> resultPlusMinus;//왜냐하면 이거 답으로 출력하래
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    stack <int> myStack;
    int max = 1; // 오름차순 수 넘은 최고기록이야.
    bool result = true;

    //가장 먼저 빼는건 단 한번만 해야 한다. 그래야 수열을 만들 수 있기 때문이다.
    //문제 조건 다시 잘 읽어보면 언제나 1~n 종류가 전부 있는 수열을 만드는 거야. 그래서 팝을 두번하는 일은 존재하지 않아.
    //1~n이 전부있고 그게 전부 있는 수열을 만드는건데 맘대로 pop을 pushback도 안하고 2번 하면 말이 안댐.
    //스택에 push하는 순서가 오름차순을 지킨다고 하니까. num은 올라가기만 하는거야.
    //처음에 4들어가면 num이 4까지 올라가는거여. 그리고 꺼내지.
    //그리고 3이 들어가면 꺼낼 수야 있지.
    //처음에 100이 들어가면 num이 100까지 오르고, 1부터 100까지 스택에 다넣어야대. 왜 다넣어야 대냐? 그래야 수열 만들 수 있을거니까.
    //즉, 미래에 꺼낼 날을 대비하여 미리 다 넣어버리는거야.
    //6꺼내고 6꺼내는 이런 동일한 값이 있는 수열은 안만들기로 했어. 한 값이 한번만 나와. 그래서 이게 가능한거야.
    //num = 1이야 그런데 input이 4야. 그러면 1 2 3 4까지 너어야지
    //num = 4야. 그런데 input이 2야? 그러면 실패야.
    //입력으로 주어지는 수열은 1부터 n까지의 숫자가 한 번씩 모두 포함된 수열
    for (int input : A) {
        // 입력으로 받아온 A의 원소 su
        if (input >= max) { //현재 수열 값 >= 오름차순 자연수 : 값이 같아 질 때까지 push()수행
            while (input >= max) { // push()
                myStack.push(max++);
                resultPlusMinus.push_back('+');
            }
            myStack.pop();
            resultPlusMinus.push_back('-');
        }
        //빼는건 반복이 아니라 1번만 하면 되는거야 입력예제 1을 머릿속으로 돌려봐.
        else {  //현재 수열 값 < 오름차순 자연수: pop()을 수행하여 수열 원소를 꺼냅니다
            int top = myStack.top();

            // 스택의 가장 위의 수가 만들어야 하는 수열의 수 보다 크다면 수열 출력 불가능
            if (top > input) {
                cout << "NO";
                result = false;
                break;
            }else {
                myStack.pop();
                resultPlusMinus.push_back('-');
            }
        }
    }
    if (result) {
        for (char i : resultPlusMinus){
            cout << i << '\n';
        }
    }
}


/*
자연수 1부터 증가시키면서 입력으로 주어진 숫자와 비교하여 증가시킨 자연수를 스택에 추가하거나 빼면 된다.
입력배열의 현재값 >= 루프자연수
num을 스택에 push해 push가 끝나면 수열을 출력하기 위해 마지막 1회만 pop해
현재값이 4면 스택에는  1 2 3 4푸시
num이 입력배열의 현재값보다 커버린다면. 무조건 pop을 해야대.
그런데 만약 top이 입력배열의 현재값보다 커버린다면 NO를 출력하고 끝이야.
그게 아니라면 하나씩 빼고 -출력

입력배열에 8이 있으면 8을 넣어줘야해. 그리고 8을 꺼내야해.


N 수열개수 A 입력배열 result 결과배열
A 배열 초기화
S 스택 선언
for (N만큼반복) {
    if(A의현재값 >= num(1,2,3,...) { // 처음에만 숭숭숭숭 넣어야대서?
        while(A의 현재값 == num까지){
            스택 push
            num++
            result에 + 저장
        }
        스택 pop();
        result에 - 저장
    }else{ // 예를들어 3이나왓는디, num은 5야 그러면 pop을 수행해.
        if(스택의 top > 현재값){
            NO출력
        }else{
            스택 pop
            result에 - 저장
        }
    }
}
result출력
 */