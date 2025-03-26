#include <iostream>
#include <vector>
using namespace std;


string comp(string a, string b) {//왼쪽이 이기면 true
    if (a == "S") {
        if (b == "S") {
            return "same";
        } else if (b == "R") {
            return "false";
        } else if (b == "P") {
            return "true";
        }
    } else if (a == "R") {
        if (b == "S") {
            return "true";
        } else if (b == "R") {
            return "same";
        } else if (b == "P") {
            return "false";
        }
    } else if (a == "P") {
        if (b == "S") {
            return "false";
        } else if (b == "R") {
            return "true";
        } else if (b == "P") {
            return "same";
        }
    } else {
        return "error";
    }
}

int main() {
    string a,b,c,d;
    cin>>a>>b>>c>>d;

    // S > P 왼쪽이 이김
    // R > S 왼쪽이 이김
    // P > R 왼쪽이 이김

    //내가 a냈는데 c냈어. b냈어.

    // comp(a,c) comp(a,d)
    // comp(b,c) comp(b,d)

    vector<string> k(4);
    k[0] = comp(a,c);
    k[1] = comp(a,d);
    k[2] = comp(b,c);
    k[3] = comp(b,d);
    
    int ext = 0;
    int exf = 0;
    int exs = 0;
    for (int i = 0; i < 4; i++) {
        if (k[i] == "true") {
            ext = 1;
        } else if (k[i] == "false") {
            exf = 1;
        } else if (k[i] == "same") {
            exs = 1;
        }
    }
    /* 
    4개중에 true랑 false가 같이 있으면 확실하지 않아 > ?
    4개가 모두 same이면 비기는거야
    4개중에 true랑 same만 있으면 >> MS 이겨
    4개중에 false랑 same만 있으면 >> TK이겨
    */
    if (ext == 1 && exf == 1) {
        cout << "?";
    } else if (ext == 0 && exf == 0) {
        cout << "?";
    } else if (ext == 1) {
        cout << "MS";
    } else if (exf == 1) {
        cout << "TK";
    }
}