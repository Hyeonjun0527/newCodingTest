/*
슬라이딩 윈도우
12891 DNA 비밀번호
9 8
CCTGGATTG
2 0 1 1
가 주어져 그리고 ACGT가 2 0 1 1개 이상을 만족하는 부분문자열 8의 개수는?
그러면 비밀번호가 부분문자열로 주어지잖아. 띄엄띄엄은 안돼.
CCTGGATT거나 CTGGATTG야. 그러면 슬라이딩윈도우 문제인게 감이오고,
조건은 머냐 ACGT가 2 0 1 1개 이상이라는 조건이 있어.
윈도우마다 이걸 검사하면 대. 하나라도 실패하면 실패야.
그러면 4번성공하면 됐는지 보자.
체크어레이 있어야겠지.  2 0 1 1넣어.
값이 0인게 있으면 바로 숫자 ++해.

그런데 첫번째 슬라이딩 윈도우를 그냥 만들까? 아니면 하나씩 넣을까? 어차피 첫번째 윈도우 만들고 add remove해야 된단말이지.
그리고 한번에 만들고 결국에 비교해야된단 말이지 그러면 하나씩 넣는 로직만 만드는게 더 코드 빨리 짜겠네 add반복해서하자.
 */


#include <bits/stdc++.h>
using namespace std;

int checkArr[4];
// 0 1 2 3
// 2 0 1 1

int myArr[4];
// 0 1 2 3
// 0 0 0 0
int checkSecret = 0;

void Add(char c);

void Remove(char c);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int S, P;
    cin >> S >> P;
    int Result = 0;
    string A;
    cin >> A;

    //checkArr 초기화 2 0 1 1 ACGT가 주어졌었지. 그 4가지가 성립하는 지 볼거야. 그걸 위한 배열.
    //체크시크릿이 4가 되면 정답을 찾은거야! Result++.
    for (int i = 0; i < 4; i++) {
        cin >> checkArr[i];
        if (checkArr[i] == 0) {
            checkSecret++;
        }
    }
    //myArr 초기화
    for (int i = 0; i < P; i++) {
        Add(A[i]);// 더하면서 조건이랑 맞는지 검사해야대.
    }
    //checkSecret이 4가 되야 올바른 케이스야. ACGT 각각 성립하면 checkSecret++해.
    //첫번째 슬라이딩 윈도우가 조건을 성립시켜서 Result값을 올렸는지 봐야대.
    //그걸 봤으면 슬라이딩 윈도우를 iter해야지.
    if (checkSecret == 4) Result++;

    //이제 첫번째 case는 처리했어. 나머지 케이스는 반복으로 처리해
    //슬라이딩 윈도우 처리 4 2면 3번 반복 / 9 8이면 2번 반복 / 10 5면 6번 반복
    //그러면 2 / 1 / 5번 반복하면 대.

    //배열 총 size는 S야. P는 윈도우 size야. P~S만큼 반복하면 댐. 윈도우 사이즈 5, 배열 10면 10-5+1= 6번 반복 5 6 7 8 9
    //슬라이딩 윈도우 처리
    int start = 0;
    int end = P - 1;
    //윈도우 개수는 몇개일까 end가 윈도우 마지막 포인터지. 전체 Arr크기 S지.
    //포인터가 찍을 수 있는게 0부터 S-1까지고 S개 포인터 가능하다는거야.
    //end가 S-1이 될 때까지 가능하겠네. end == S - 2에 마지막 바퀴 돌고 S - 1되고 종료. 그러면 end < S - 1해도 되고 end != S - 1
    //end 포인터가 딱 S-2을 가리키고 있어. 그리고 S-1이 있어. 그러니 end < S - 1까지야.
    //end < S - 1라는건 end <= S - 2에 마지막 연병장 1바퀴 도는거야.
    while (end <= S - 2) {
        Remove(A[start]);//삭제하고(이거는 조건에 맞는지 확인하는 과정을 추상화)
        start++;//포인터 옮기고
        end++;
        Add(A[end]);//더하고
        if (checkSecret == 4) Result++;
    }
    cout << Result << "\n";
}
//'A'가 들어가면 myArr[0]++해.

// int charToIndex(char c) {
//     switch (c) {
//         case 'A' :
//             return 0;
//         case 'B' :
//             return 1;
//         case 'C' :
//             return 2;
//         case 'D' :
//             return 3;
//     }
// }
unordered_map<char,int> charToIndexMap = {{'A', 0}, {'C', 1}, {'G', 2}, {'T', 3}};

void Add(char c) {
    // c를 받았어 'A'야 그러면 myArr[0]++해야돼. 개수세는거야. myArr는 개수세는걸 추상화한거야.
    //그리고 비교도 해야지 비교했을때 맞으면 checkSecret++해야대.
    //이상이니까 myArr[idx] >= checkArr[idx]해야되는거아니야? 이런 생각 들거야.
    //처음에 그렇게 할 수 밖에 없을거야. 그런데 이런 생각도 가능해. 리무브를 할거잖아.
    //리무브하면 다음 슬라이드로 넘어가는거잖아. 그러면 비교했을때 조건 안맞을 수 있잖아.
    //조건이 안맞는 만큼 --를 할거잖아. checkSecret을? 그리고 하나씩 ++하잖아.
    //이상인데 조건이 2야. 그런데 내 myArr가 2가되고 3이되고 4가돼. 그때마다 ++하면 안대지.
    //이상이 되는 그 순간에 true되었다고 표시하는거니까 ==로 하는거야. 4지만 true 4개를 의미하는거야.
    //checkSecret말고 맵으로 해도 돼.
    int idx = charToIndexMap[c];
    myArr[idx]++;
    if (myArr[idx] == checkArr[idx]) checkSecret++;
    //같을 때만 checkSecret++함. 중복해서 더하는 일 발생하지 않도록 함 최대 4만 되도록 함.
}
void Remove(char c) {
    //리무브할거잖아. 하나 뺏어. 그러면 그때 조건 맞는지 아닌지 검사해야지. 빼고 검사해야지
    //조건이 아니게 되어버리는 그 순간에 --를 해야하는거야. 이것도 같은거 아니라 이하로
    //검사하게 되면 문제가 생기지. 아니면 map<int,bool>같은거로 하던지 그러면 더 안전하긴 하겠다.
    int idx = charToIndexMap[c];
    myArr[idx]--;
    if (myArr[idx] + 1 == checkArr[idx]) checkSecret--;
    //같을때 remove하면 checkSecret--해야 지??
    //myArr[idx]--로 빼기 전에는 myArr[idx]+1인 상태지.
}
