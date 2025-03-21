/*
계속 넣어야겠지. 넣다가
max : 현재까지 추적한 최댓값
input : 주어진 값 4, 3, 6, 8, 7, 5, 2, 1
max와 input 비교해서 input이 크면 max를 증가시키면서 max와 input크기를 맞춰야돼.
그리고 그동안 sol 배열에 +를 입력해.
다 맞추면 팝해야 돼. 그때는 - 입력해

max가 더 커? 그러면 어떻게 하지.
input < max야. 그런데 input < top 이래.


어떤 문제냐 N이 주어져.
그러면 1~N까지의 배열이 있는거야.
그걸 막 섞어.
그리고 그거를
1~N까지 순서대로 스택에 넣었다가 빼서
만들어낼 수 있느냐. 이 문제임.
N=8이라고

문제 있는 상황은 현재 스택 배열에 1 2 3 4 이런식으로 있는데
3을 요구하는 상황이야.
즉, top보다 작은걸 요구하는 상황.


케이스는 먼저 2가지로 나눌 수 있어.
아직 앞으로 안갔거나 (input >= max)
(스택에 5를 넣었으면 max는 6이 돼.) 사실 max는 다음 들어올 타자야. 다음 들어오는 놈이야.
이미 앞으로 너무 간거야 (input < max)

 */



#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int N;
vector<int> A;
vector<char> sol;
stack <int> myStack;
int max_ = 1;
bool able = true;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    A.resize(N);

    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }

    for (int input : A) {
        if (input >= max_) {
            while (input >= max_) {
                myStack.push(max_++);
                sol.push_back('+');
            }
            myStack.pop();
            sol.push_back('-');
        }
        else {
            int top = myStack.top();
            if (top != input) {
                cout << "NO";
                able = false;
                break;
            }else {
                myStack.pop();
                sol.push_back('-');
            }
        }
    }
    if (able) {
        for (char i : sol){
            cout << i << '\n';
        }
    }
}
