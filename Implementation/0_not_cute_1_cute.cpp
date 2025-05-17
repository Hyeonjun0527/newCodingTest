#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    int b = 0;//기준
    while (n--) {//3 2 1
        int a;
        cin >> a;
        if (a == 1) b++;
        else b--;
    }

    if (b > 0) cout << "Junhee is cute!";
    else cout << "Junhee is not cute!";
}