/*
일단 반복적으로 해야 해.
그리고 다이나믹이야.
점화식은

먼저 xi와 yi가 같은지 확인
다르면 xi-1,y     xi, yi-1


std::copy쓰려면 먼저 resize를 해야 함.

ABCBD
ACBD

 */


#include <iostream>
#include <string>
#include <vector>

using namespace std;

int lcs (string s1, string s2) {
    int s1_size = s1.size();
    int s2_size = s2.size();
    vector<char> X;
    vector<char> Y;
    vector<vector<int>> DP;//dp테이블
    // vector<char> Z;


    if (s1_size == 0 || s2_size == 0) {
        return 0;
    }

    X.resize(s1_size);
    Y.resize(s2_size);
    // Z.resize(max(s1_size,s2_size));
    DP.resize(s1_size, vector<int>(s2_size, 0));

    copy(s1.begin(),s1.end(),X.begin());
    copy(s2.begin(),s2.end(),Y.begin());
    if (X[0] == Y[0]) {
        DP[0][0] = 1;
    }
    for (int i = 1; i < s1_size; i++) {
        DP[i][0] = (X[i] == Y[0]) ? 1 : DP[i - 1][0];
    }
    for (int j = 1; j < s2_size; j++) {
        DP[0][j] = (X[0] == Y[j]) ? 1 : DP[0][j - 1];
    }


    for (int i = 1; i < X.size(); i++) {
        for (int j = 1; j < Y.size(); j++) {
            if (X[i] == Y[j]) {
                DP[i][j] = DP[i-1][j-1] + 1;
            } else {
                DP[i][j] = max(DP[i][j-1], DP[i-1][j]);
            }
        }
    }
    return DP[X.size() - 1][Y.size() - 1];
}


string s1;
string s2;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    getline(cin, s1);
    getline(cin, s2);

    int length = lcs(s1, s2);

    cout << length;
}
