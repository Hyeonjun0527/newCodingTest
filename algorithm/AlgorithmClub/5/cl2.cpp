#include <bits/stdc++.h>
using namespace std;

int N;//곡의 마디 수
double S_0;// 곡의 초기 BPM
int K;//곡의 변속 횟수
vector<int> M;//변속이 일어나는 마디
vector<double> S;//변속으로 인해 변한 BPM

//곡은 마디로 마디는 박으로
double sec = 0;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> S_0 >> K;

    M.resize(10000000);
    S.resize(10000000);

    for (int i = 0; i < K; i++) {
        cin >> M[i] >> S[i];
        if (i == 0) sec += (M[i] - 1) * 4 / (S_0 / 60);
        else {
            sec += ((M[i] - M[i-1]) * 4) / (S[i-1] / 60);
        }
    }

    sec +=(N - M[K - 1] + 1) * 4 / (S[K-1] / 60);

    if (K == 0) {
        sec = N * 4 / (S_0 / 60);
    }

    cout << fixed << setprecision(12);
    cout << sec;
    return 0;
}
