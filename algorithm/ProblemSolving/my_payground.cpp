/*
---입력------------
7 20 15
30 21 1 2 30 22 3
---출력------------
9
------------------
*/
#include <bits/stdc++.h>
using namespace std;
int N;//몬스터 수
int D;//기본데미지
int p;//얼마나 오버킬 퍼센트
vector<int> A;
int count_ = 0;//공격 횟수
int main() {
    cin >> N >> D >> p;
    A.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }

    for (int i = 0; i < N; i++) {
        if (A[i] <= 0) {//이미 죽어있을 수 있어.
            continue;
        }
        if (A[i] < D) {//첫 공격이 오버킬이야.
            count_++;
            int h = D - A[i];
            if (i == N - 1) {
                break;
            }
            A[i+1] -= h*p/100;
            continue;
        }
        count_ += A[i] / D;
        int remain_health = A[i] % D;
        if (remain_health != 0) {
            //오버킬 일어남
            count_++;
            int h = D-remain_health;
            if (i == N - 1) {
                break;
            }

            A[i + 1] -= h * p / 100;
        } else {
        }
    }
    cout << count_;
}