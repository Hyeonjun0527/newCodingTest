#include<bits/stdc++.h>

using namespace std;
int N;
string input;
int main() {
    //getline 하기 전에는 꼭 ignore을 해준다.

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


//왜 int =0, string =""이나 null로 초기화 해도 안해도 될까?
//c - '0' 말고 c + '0'해도 잘 코드가 돌아갈까?
