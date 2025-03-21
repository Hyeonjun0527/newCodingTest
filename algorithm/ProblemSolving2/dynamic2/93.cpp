/*
r : row , col : column 즉 사각형을 세로길이가 r이고 가로길이가 c야.
x값이 r이고 y값이 col이야.
ㅡ ㅡ ㅡ
|       |
|ㅡ ㅡ ㅡ|
이렇게 있으면 r = 0,1 c = 0,1,2
먼저 DP 테이블 왼쪽위에서 오른쪽 아래로 좌자자작 채울거야.
가로쭉 가로쭉 가로쭉 이렇게 순회할건데 각 셀마다 왼쪽 위쪽 왼쪽위대각 이렇게 3개 고려할거야
3개 고려했을때
왼쪽 위 대각에서 문자가 같으면 거기서 1 더한거로 DP를 채워
왼쪽 위 대각에서 문자가 같지 않으면 왼쪽이나 위쪽을 그대로 가져와서 DP 채워
그러면 가장 오른쪽 아래 DP값이 우리가 원하는 최적길이야.
그런데 우리가 원하는 문자는 어떻게 얻냐?
그 DP 구했으면 있지. 오른쪽 아래(A.size(),B.size())에서 가장 왼쪽 위 (0,0)으로 역추적하면 돼.
역추적해서 Path에 담을거고 그거 그대로 출력할거야.
논리는 완전히 똑같아.
왼쪽 위 대각에서 문자가 같으면 거기의 문자를 Path에 기록해. 그리고 거기로 이동.
왼쪽 위 대각에서 문자가 다르면 왼쪽과 위쪽중 큰 값으로 이동해. 같으면 아무래도 OK.
*/

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int v;
int DP[1001][1001];
string A, B;
vector<char> Path;
void getText(int r, int c);

int main()
{
    cin >> A >> B;
    for (int i = 1; i <= A.size(); i++) {
        for (int j = 1; j <= B.size(); j++) {
            if (A[i - 1] == B[j - 1]) {
                DP[i][j] = DP[i - 1][j - 1] + 1; // 같은 문자열일 경우 왼쪽 대각선 값 +1
            }
            else {
                DP[i][j] = max(DP[i - 1][j], DP[i][j - 1]); // 다르면 왼쪽과 위의 값 중 큰수
            }
        }
    }

    cout << DP[A.size()][B.size()] << "\n";
    getText(A.size(), B.size());
    for (int i = Path.size() - 1; i >= 0; i--) {
        cout<< Path[i];
    }
    cout << "\n";
}

void getText(int r, int c) { // LCS 출력함수
    if (r == 0 || c == 0) return;
    if (A[r - 1] == B[c - 1]) { // 같으면 LCS에 기록하고 왼쪽 위로 이동
        Path.push_back(A[r - 1]);
        getText(r - 1, c - 1);
    }
    else {
        if (DP[r - 1][c] > DP[r][c - 1]) // 다르면 왼쪽과 윗쪽 중 큰 수로 이동
            getText(r - 1, c);
        else
            getText(r, c - 1);
    }
}