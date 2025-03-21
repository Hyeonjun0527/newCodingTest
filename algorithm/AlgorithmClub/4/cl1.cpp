#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);


    int sumA = 0;
    double sumB = 0;
    for (int i = 0; i <= 5; i++) {
        int input = 1;
        cin >> input;
        if (i == 0) input *= 13;
        if (i == 1) input *= 7;
        if (i == 2) input *= 5;
        if (i == 3) input *= 3;
        if (i == 4) input *= 3;
        if (i == 5) input *= 2;
        sumA += input;
    }
    for (int i = 0; i <= 5; i++) {
        int input = 1;
        cin >> input;
        if (i == 0) input *= 13;
        if (i == 1) input *= 7;
        if (i == 2) input *= 5;
        if (i == 3) input *= 3;
        if (i == 4) input *= 3;
        if (i == 5) input *= 2;
        sumB += input;
    }
    sumB += 1.5;

    if (sumA > sumB) cout << "cocjr0208";
    if (sumA < sumB) cout << "ekwoo";

}
