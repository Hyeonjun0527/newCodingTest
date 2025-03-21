#include <iostream>
#include <string>
using namespace std;

int N;
string input;
int sum;
int main() {

    cin >> N;
    cin.ignore(); getline(cin, input);

    int sum = 0;
    for (char c : input) {
        int c_int = c - '0';
        sum += c_int;
    }

    cout << sum << endl;
    return 0;
}
