#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n;

    // vector<int> a(n);//0이면 A, 1이면 B
    // vector<int> b(n);
    // vector<int> c(n);
    // vector<int> d(n);

    int sumg = 0;
    int sumv = 0;

    for (int i = 0; i < n; i++) {
        string t;
        int w,h,l;

        
        cin >> t >> w >> h >> l;

        // a[i] = (t == "A") ? 0 : 1;
        // b[i] = w;
        // c[i] = h;
        // d[i] = l;

        if (t == "A") {
            //사과 개수
            int ac = (w / 12) * (h / 12) * (l / 12);//사과개수
            sumg += 1000 + ac * 500;
            sumv += ac * 4000;
        } else {
            sumg += 6000;
        }
    }

    cout << sumg << "\n";
    cout << sumv;
}