#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int N,A,B;
    cin >> N >> A >> B;
    int onion1 = 1, onion2 = 1;

    bool switched = false;

    for (int i = 0; i < N; i++) {//10번
        if (!switched) {
            //1 : 칭찬 2 : 비난
            onion1 += A;
            onion2 += B;

            if (onion1 < onion2) {
                switched = true;
            } else if (onion1 == onion2) {
                onion2 -= 1;
            }
        } else {
            //1 : 비난 2 : 칭찬
            onion1 += B;
            onion2 += A;

            if (onion2 < onion1) {
                switched = false;
            } else if (onion1 == onion2) {
                onion1 -= 1;
            }
        }
    }
    if (switched){
        cout << onion2 << " " << onion1;
    } else {
        cout << onion1 << " " << onion2;
    }

}
