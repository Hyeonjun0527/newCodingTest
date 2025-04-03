#include <iostream>
#include <vector>
using namespace std;
int main() {
    vector<string> a(7);
    a[0] = "Never gonna give you up";
    a[1] = "Never gonna let you down";
    a[2] = "Never gonna run around and desert you";
    a[3] = "Never gonna make you cry";
    a[4] = "Never gonna say goodbye";
    a[5] = "Never gonna tell a lie and hurt you";
    a[6] = "Never gonna stop";

    int n;
    cin >> n;
    cin.ignore();
    string sol = "No";
    for (int i = 0; i < n; i++) {
        string o;
        getline(cin, o);
        bool soakHanDa = false;
        for (string el : a) {
            if (o == el) {
                soakHanDa = true;
            }
        }
        if (!soakHanDa) {
            sol = "Yes";
            cout << sol << "\n";
            return 0;
        }
    }
    cout << sol << "\n";
}