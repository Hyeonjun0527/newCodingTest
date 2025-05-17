// 4점이 다 x=0 || 4점이 다 y==0 || 4점이 다 z==0 이냐? 맞으면 yes 아니면 no
#include <iostream>
#include <map>
#include <vector>
using namespace std;

int main() {

    map<int, string> m;
    m.emplace(0, "000");
    m.emplace(1, "001");
    m.emplace(2, "010");
    m.emplace(3, "011");
    m.emplace(4, "100");
    m.emplace(5, "101");
    m.emplace(6, "110");
    m.emplace(7, "111"); // 이진수로 변환하는거 알아두자.

    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        string aa, bb, cc, dd;
        aa = m[a];
        bb = m[b];
        cc = m[c];
        dd = m[d];
        bool x;
        bool y;
        bool z;
        string sol = "NO";
        for (int j = 0; j < 3; j++) { // j는 x,y,z
            if (aa[j] == '0' && bb[j] == '0' && cc[j] == '0' && dd[j] == '0')
                sol = "YES";
            if (aa[j] == '1' && bb[j] == '1' && cc[j] == '1' && dd[j] == '1')
                sol = "YES";
        }
        cout << sol << "\n";
    }
}