/*
---입력------------
7 20 15
30 21 1 2 30 22 3
---출력------------
9
------------------
문제 설명을 하면 이런거야. N개의 몬스터가 주루룩 있어.
그리고 공격력 20으로 순서대로 공격을 해.
30 > 10 > -10
그리고 -10의 15%가 다음 몬스터에게도 데미지 들어가.
오버킬 데미지야.
(오버킬 데미지는 다음몬스터에게까지만 들어감)
(한번에 3마리 죽일 순 없음. 2마리 죽이는거 까지만 가능할거임.


 */

#include <bits/stdc++.h>
using namespace std;

int N;
int D;
int p;
int turn = 0;
vector<int> A;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    A.resize(10000000);

    cin >> N >> D >> p;

    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    for (int i = 0; i < N; i++) {
        while (A[i] > 0) {
            //cout << "i: " << i << ", A[i]: " << A[i] << '\n';
            turn++;
            if(A[i] - D >= 0) {//오버킬 안일어남
                A[i] -= D;
            } else {//오버킬 일어남
                int h = (D - A[i]);
                //cout << "h: " << h << '\n';
                A[i] = 0;
                if (i == N - 1) {
                    break;
                }
                //cout << A[i+1] << ' ';
                A[i+1] -= h*p/100;
                //cout << A[i+1] << ' ';
            }
        }
    }
    cout << turn;
}
