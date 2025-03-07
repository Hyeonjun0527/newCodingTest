#include <iostream>
using namespace std;
int main() {
    //그 값부터 min ( )값까지.
    int n, m, k;
    cin >> n >> m >> k;
    //감염시나리오 감염 1일 뒤자나. R을 찾아서 감염을 시켜. 그리고 감염자 수 <= M치료제면 YES
    string a;
    cin >> a;
    int i = 0;
    for (char c : a) {
        if (c == 'R') {
            int start = max(1,i-k);
            int end = min(n,i+k);
            // cout << start << " " << end << "\n";
            for (int j = start; j <= end; j++) {
                a[j+1] = 'R';
            }
        }
        i++;
    }

    int cnt = 0;
    for (char c : a) {
        if (c == 'R') {
            cnt++;
        }
    }
    if (cnt <= m) {
        cout << "Yes";
    } else {
        cout << "No";
    }
    //나는0베이스드로했어. 여기는 1베이스드야 그러면 
}