/*
수 N개 A1, A2, ..., AN이 주어진다.
• 이때, 연속된 부분 구간의 합이 M으로 나누어떨어지는 구간의 개수를 구하는 프로그램을
작성하시오.
 • 즉, Ai + ... + Aj (i ≤ j) 의 합이 M으로 나누어떨어지는 (i, j) 쌍의 개수를 구해야 한다.

즉 1 2 3 1 2 면 구간합이 3으로 나누어떨어지는 쌍의 개수.
(1 2) 3 1 2 >>  if (remainder == 0) answer++;
(1 2 3) 1 2 >>  if (remainder == 0) answer++;
1 (2 3 1) 2
1 2 (3) 1 2
1 2 (3 1 2)
1 2 3 (1 2)
(1 2 3 1 2) >>  if (remainder == 0) answer++;
이게 답이야. 합배열 생성하고 구간합 공식 이용해서 구간 합 구할 수 있어.
구간합이 MOD로 떨어지는지 확인하고 떨어지면 count ++;
그런데 이렇게 했을 때 시간복잡도가 얼마지 10^6의 제곱이라서 안돼.
S : 1 3 6 7 9
그러면 합배열을 변형해
S%M : 1 0 0 1 0
합배열을 MOD 연산해.
i : 0 1 2
C[i] : 3 2 0
그 다음 1. 원소값이 0개면 정답에 더해.
원소값 0이란건 0~i까지의 구간합이 M으로 나누어 떨어진다는거 그 케이스 전부 셌어.
그리고 C[0]=3이잖아. 그러면 3C2를 answer에 더해. 왜냐?
거기서 2개 택한 쌍도 정답이니까 그래. 답:Ai + ... + Aj (i ≤ j) 의 합이 M으로 나누어떨어지는 (i, j) 쌍의 개수를 구해야 한다

(A + B) % C =  ((A % C) + (B % C)) % C
한번에 더해서 모드 한거 = 각각 모드 하고 더한다음 다시 모드한거.
나머지가 같은 두 구간을 선택하면 그 사이의 합이 M으로 나누어떨어집니다.
S[j]%M=S[i−1]%M일 때, 𝑆[𝑗]−𝑆[𝑖−1], S[j]−S[i−1]는 M으로 나누어떨어진다는 것을 의미합니다.

S[end] - S[start] = start~end의 합이잖아.
S[end]%M - S[start]%M = 0 이라고 그래.
그 말은 (S[end]-S[start])%M = 0 이라는거야. 즉 start~end의 합이 M으로 나누어 떨어진다는 것.
다시말해 start,end쌍이 정답이라는것이야.
그래서 나머지가 같은 두 구간을 선택하면 정답이야.
5%3=2  8%3=2일때 (8-5)%3=0이다.
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N,M;
    cin >> N >> M;

    vector<long> S(N, 0);//합배열
    //변형된 합배열은 S 각각을 MOD로 나눈거야 따로 메모리에 저장안함.
    vector<long> C(M, 0);//M=3이면 remainder가 0인 경우, 1인 경우, 2인 경우..
    long answer = 0;
    cin >> S[0];
    //합배열 만들어
    for (int i = 1; i < N; i++) {
        int temp = 0;
        cin >> temp;
        S[i] = S[i-1] + temp;
    }

    //변형된 합배열 만들어 그리고 원소값 0이면 remainder배열에 추가해.
    for (int i = 0; i < N; i++) {
        int remainder = S[i] % M;
        if (remainder == 0) answer++;
        C[remainder]++;
    }
    //answer는 지금 3이 됐어.

    //정답은 쌍의 개수는 머냐.
    //remainder가 1인 경우가 3개야 그러면 3C2, N개면 NC2
    for (int i = 0; i <=M-1; i++) {
        if (C[i] >= 2) {
            answer += C[i] * (C[i] - 1) / 2;
        }
    }

    //answer가 3 + 3C2 + 2C2 = 7
    cout << answer << "\n";
    
}
