//7을 100이라는 데이터에 숨기면 100에꺼에 7뒤에다가 붙여.

//세 십진수 이진수로 변환해서 4LSB를 이어붙이고 십진수로 변환하면 된다.

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int d,e,f;
    cin >> d >> e >> f;
    int a,b,c;
    a = d;
    b = e;
    c = f;

    string A,B,C;
    A = ""; B = ""; C="";
    while (a > 1) {
        A += to_string(a%2);
        a /= 2;
    }
    A+="1";
    reverse(A.begin(), A.end());

    if (d == 0) A="0";
    if (d == 1) A="1";
    if (d == 2) A="10";

    while (b > 1) {
        B += to_string(b%2);
        b /= 2;
    }
    B+="1";
    reverse(B.begin(), B.end());

    if (e == 0) B="0";
    if (e == 1) B="1";
    if (e == 2) B="10";
    while (c > 1) {
        C += to_string(c%2);
        c /= 2;
    }
    C+="1";
    reverse(C.begin(), C.end());

    if (f == 0) C="0";
    if (f == 1) C="1";
    if (f == 2) C="10";

    int count = 1;
    stringstream lsbA;
    //cout << A << endl;
    //cout << B << endl;
    //cout << C << endl;

    for (char a : A) {
        string aa(1,a);
        if (count >= ((int)A.length() - 3)) lsbA << aa;
        count++;
    }

    //cout << lsbA.str() << endl;
    count = 1;
    stringstream lsbB;
    for (char a : B) {
        string aa(1,a);
        if (count >= ((int)B.length() - 3)) lsbB << aa;
        count++;
    }
    count = 1;
    //cout << lsbB.str()<< endl;
    stringstream lsbC;
    for (char a : C) {
        string aa(1,a);
        if (count >= ((int)C.length() - 3)) lsbC << aa;
        count++;
    }
    //cout <<"먼데" <<lsbC.str() << endl;


    stringstream Sum_string_stream;
    if (lsbA.str().length() >= 4) Sum_string_stream << lsbA.str();
    else if (lsbA.str().length() == 3) {
        Sum_string_stream << "0" <<lsbA.str();
    } else if (lsbA.str().length() == 2) {
        Sum_string_stream << "00" <<lsbA.str();
    } else if (lsbA.str().length() == 1) {
        Sum_string_stream << "000" <<lsbA.str();
    } else {
        Sum_string_stream << "0000";
    }
    if (lsbB.str().length() >= 4) Sum_string_stream << lsbB.str();
    else if (lsbB.str().length() == 3) {
        Sum_string_stream << "0" <<lsbB.str();
    } else if (lsbB.str().length() == 2) {
        Sum_string_stream << "00" <<lsbB.str();
    } else if (lsbB.str().length() == 1) {
        Sum_string_stream << "000" <<lsbB.str();
    } else {
        Sum_string_stream << "0000";
    }
    if (lsbC.str().length() >= 4) Sum_string_stream << lsbC.str();
    else if (lsbC.str().length() == 3) {
        Sum_string_stream << "0" <<lsbC.str();
    } else if (lsbC.str().length() == 2) {
        Sum_string_stream << "00" <<lsbC.str();
    } else if (lsbC.str().length() == 1) {
        Sum_string_stream << "000" <<lsbC.str();
    } else {
        Sum_string_stream << "0000";
    }
    //cout << Sum_string_stream.str()<< endl;


    int zinsu = pow(2,Sum_string_stream.str().length() - 1);
    int sum =0;

    for (char aa : Sum_string_stream.str()) {
        if (aa == '1') sum += zinsu;
        zinsu/=2;
    }
    //cout << sum;

    string sol = to_string(sum);
    stringstream solstream;
    if (sol.length() >= 4) solstream << sol;
    else if (sol.length() == 3) {
        solstream << "0" <<sol;
    } else if (sol.length() == 2) {
        solstream << "00" <<sol;
    } else if (sol.length() == 1) {
        solstream << "000" <<sol;
    } else {
        solstream << "0000";
    }
    cout <<solstream.str();

}
