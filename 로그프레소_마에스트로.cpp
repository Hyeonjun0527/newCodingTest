#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
struct Logg {
    int a;
    int b;
    int c;
    bool operator<(const Logg other) const {
        return a > other.a; // 내림차.
    }
};
int main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> gam;
    for (int i = 0; i < k; i++) {
        int r;
        cin >> r;
        gam.emplace_back(r); // 감염자리스트
    }
    vector<Logg> l; // 로그 리스트임.
    for (int i = 0; i < m; i++) {
        int r1, r2, r3;
        cin >> r1 >> r2 >> r3;
        l.push_back({r1, r2, r3});
    }
    sort(l.begin(), l.end());

    bool elcisgam = false;

    int sol = 0;

    int cnt = 100;
    while (cnt--) {
        int temp = 0;
        int count = 0;
        for (int i = 0; i < l.size(); i++) { // 로그순회
            if (i == 0) {
                temp = l[i].c;
            }
            for (int j = 0; j < gam.size(); j++) {
                if (gam[j] == temp) {
                    elcisgam = true;
                }
            }

            if (elcisgam) {
                count++;
                temp = l[i].b;
            }
        }
        if (count == gam.size() - 2) {
            cout << temp;
            break;
        }
    }
}

// 5에서 4를 찾고 4에서 3을 찾아야 돼. 없네
// 그러면 3에서 5를 찾고 5에서 4를 찾아야대.

/*

k가 감염된 컴터가 후보야
다 해봐. 실제 상황이 주어지는지 안주어지는지
예제입력1번보면 첫째컴터가 3번이 감염자라고 판단하고 모순 있는지 전수조사.
*/