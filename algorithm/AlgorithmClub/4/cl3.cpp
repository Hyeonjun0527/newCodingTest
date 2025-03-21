#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    string A = "1";
    int count = 1;
    stringstream lsbAstream;

    for (char a : A) {
        string aa(1,a);
        cout << aa << " " << (int)A.length()-1-3 << endl;
        if (count >= (A.length() - 1 - 3)) lsbAstream << aa;
        count++;
    }
    cout << lsbAstream.str();
    
}
