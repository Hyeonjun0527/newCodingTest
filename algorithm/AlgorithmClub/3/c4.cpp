#include <bits/stdc++.h>
using namespace std;

int v;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> v;
    if (v <= 3)
        cout << "0013"[v];
    else
        cout << v * 3 - 4;

}


/*
지우는건 진짜 모르겠음 어케 지워야 할 지
다이얼은 유니크한 자료구조 생성하는 법을 까먹음

홀수 짝수로 나눠라는 왜 틀린지 모르겠음 머리가 안돌아감
 */