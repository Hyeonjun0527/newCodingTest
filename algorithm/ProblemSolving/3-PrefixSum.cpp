#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    vector<int> S(1'000'01);
    int N,M;
    cin >> N >> M;


    //S[0] = 0이고 사용하지 않음. S[1]부터 초기화 해줌. S[0]도 사용된다면 (구간합 0~j) S[0] 따로 초기화 해줘야함 5.cpp
    for (int i = 1; i <= N; i++) {
        int temp;
        cin >> temp;
        S[i] = S[i-1] + temp;
    }

    for (int i =0; i < M; i++) {
        int start, end;
        cin >> start >> end;
        cout << S[end] - S[start - 1] << "\n";
    }
    
}
