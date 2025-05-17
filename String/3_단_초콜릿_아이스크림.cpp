#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int t;
    cin >> t;
    
    for (int i = 0; i < t; i++) {
        string s;
        cin >> s;
        // cout << s << "s\n";
        int n = ceil(s.size() / 3.0);
        // cout << n << "n\n";
        string ss_rev = s.substr(0,n);//DOT
        // cout << ss << "ss\n";
        string ss = ss_rev;
        reverse(ss_rev.begin(), ss_rev.end());
        
        string ss_rev_tail = ss_rev.substr(1,ss.size());

        string ss_tail = ss.substr(1,ss.size());

        string a = ss + ss_rev + ss;
        string b = ss + ss_rev_tail + ss;
        string c = ss + ss_rev + ss_tail;
        string d = ss + ss_rev_tail + ss_tail;
        
        if (s == a || s == b || s == c || s == d) {
            cout << 1 << "\n";
        } else {
            cout << 0 << "\n";
        }
    }
}