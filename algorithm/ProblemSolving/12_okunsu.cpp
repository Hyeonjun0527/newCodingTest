
/*
오큰수가 머냐. 오른쪽에 있으면서 Ai보다 큰수중에서 가장 왼쪽에 있는수래.
A   : 3 5 2 7이래. 그러면
NGE : 5 7 7 -1 이래.
개쉽네 여기서 어떻게 아이디어 떠올릴까
A  :  9 5 4 8
NGE : -1 8 8 -1

10^6 하나하나씩 처리하면 시간복잡도 개높을거야.
그러면 어케해.
시간복잡도 줄여야지. 어케줄일거야? 정보를 버려. 정보를 줄여.
하나하나씩 처리해야되는데 정보를 줄여야 돼. 그러면 자료구조야.
3만 있다고 쳐 봐
그리고 5를 넣었다고 쳐봐 그리고 넣은 input이 기존 3보다 크네 그러면 오큰수네
만약에 작다고 쳐봐 9넣고 5넣었어. input이 더 작네? 그러면 또 넣어야지 그리고 9보다 작네?
그러면 또 넣어야지 8 넣었네 작네? 그러면 -1이야. 그런데 이러면 5는 어떻게 처리될거임
처리못하지. 배열 또 다 넣어서 다시 비교해야지. 그러면 시간초과지.
그러면 9를 넣었어. 오큰수가 안나와. 그럼 그냥 5를 넣어. 그리고 4를 봐.
오큰수가 안나와 그러면 4를 넣고 8을 봐. 오큰수네? 그러면 8을 결과배열에 넣어.
while문으로 오큰수를 만나면 top과 input 비교해서 input이 크면오큰수잖아.
그러면 while문으로 top빼고 while문으로 또 빼. 다 빼고 넣어. 그리고 9가 남네 어떻게 처리 해.
9와 8이 남잖아 -1로 처리해. 그럼 답 완성이네 오큰수 된거만 빼고 못뺀거는 오큰수 못찾은거네
다른경우도 그렇게 될까?
9 5 4 8   3 4 5라고 하자.
-1 8 8 -1 4 5 -1이 되겠지. 되네. 신뢰할 만 하네.
9
9 5
9 5 4
9 5 4 8

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
    vector<int> A(N+1, 0);
    vector<int> ans(N+1, 0);
    for (int i = 1; i < N+1; i++) {
        cin >> A[i];
    }
    stack <int> Stack;
    Stack.push(1);
    for (int i = 2; i < N+1; i++) {
        //스택 비어있지 않고 현재 수열이 스택 TOP인덱스 가르키는 수열보다 크면
        while (!Stack.empty() && A[Stack.top()] < A[i]) {
            ans[Stack.top()] = A[i];  //정답 배열에 오큰수를 현재 수열로 저장하기
            Stack.pop();
        }
        Stack.push(i); //신규데이터 push
    }
    while (!Stack.empty()) {
        // 반복문을 다 돌고 나왔는데 스택이 비어있지 않다면 빌 때 까지
        //         A  :  9 5 4 8
        // NGE : -1 8 8 -1
        // 9와 8이 남잖아 -1로 처리해.
        ans[Stack.top()] = -1;
        Stack.pop();
    };
    for (int i = 1; i < N+1; i++) {   // 출력
        cout << ans[i] << " ";
    }
}


/*

N수열개수 A배열 ans정답배열

A에 데이터 저장
스택에 push(1)
for(i=2~끝까지)반복
    while(스택이 남아있고 A[top] < A[i])반복
        ans[top] = A[i]
        스택 pop
    }
    스택 push
}
while(스택 남아있으면) 반복
    ans[top] = -1;
    스택 pop
}
ans출력

 */