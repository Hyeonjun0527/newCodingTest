#include <iostream>
using namespace std;
int main() {
    int hours, minutes, m;
    cin >> hours >> minutes >> m;
    // hours=14, minutes=30
    int temp = minutes + m; // 110

    if (temp >= 60) {
        hours += temp / 60;
    }
    temp %= 60;

    if (hours >= 24) {
        hours %= 24; // 25-> 25%24-> 1 , 50 -> 2
    }

    cout << hours << " " << temp;
}