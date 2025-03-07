
#include <vector>
#include <iostream>
#include <sstream>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int t;
    cin >> t;

    for (int i = 0; i < t; i++)
    {
        int n;
        cin >> n;
        
        if (n == 1) {
            cout << "0" << "\n";
            continue;
        }
        if (n == 2) {
            cout << "11" << "\n";
            continue;
        }
        
        string s;
        s = "1";
        for (int j = 1; j <= n - 2; j++)
        {
            s += "2";
        }
        
        s += "1";
        cout << s << "\n";
    }
}