#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iostream>

using namespace std;

int main() {
    // 1. 문자열 분할(split) stringstream, vector, string, getline, while, push_back
    // 1. 문자열 분할(split)
    string text = "사과,바나나,오렌지";
    stringstream ss(text);
    cout << "원본 텍스트: " << text << endl;

    vector<string> tokens;
    string token;
    
    while (getline(ss, token, ',')) {
        tokens.push_back(token);
    }
    
    cout << "분할 후: ";
    for(const auto& t : tokens) {
        cout << t << " ";
    }
    cout << endl << endl;
    
    // 2. 문자열 합치기(join)
    vector<string> words = {"안녕", "씨쁠쁠", "세상"};
    cout << "합칠 단어들: ";
    for(const auto& w : words) cout << w << " ";
    cout << endl;
    
    string joined;
    for (int i = 0; i < words.size(); ++i) {
        joined += words[i];
        if (i >= words.size() - 1) continue;
        joined += " ";
    }
    cout << "합친 후: " << joined << endl << endl;
    
    // 3. 문자열 내 모든 부분 문자열 찾기
    string haystack = "가나다가나다가";
    string needle = "가나";
    cout << "'" << haystack << "' 에서 '" << needle << "' 찾기" << endl;
    
    vector<int> positions;
    int pos = haystack.find(needle, 0);
    
    while (pos != string::npos) {
        positions.push_back(pos);
        pos = haystack.find(needle, pos + 1);
    }
    
    cout << "찾은 위치들: ";
    for(int p : positions) cout << p << " ";
    cout << endl << endl;
    
    // 4. 팰린드롬 확인 (reverse해서 같은지)
    string palindromeTest = "abccba";
    cout << "팰린드롬 검사할 문장: " << palindromeTest << endl;

    string clean;
    bool isPalindrome = false;
    for (char c : palindromeTest) {
        if (isalnum(c)) clean += tolower(c);
    }
    cout << "clean :: " << clean << "\n";
    string pal = clean;
    reverse(pal.begin(),pal.end());
    cout << "pal :: " << pal << "\n";
    //팰린드롬 확인 방법임.
    isPalindrome = clean == pal ? true : false;

    cout << "팰린드롬 여부: " << (isPalindrome ? "네" : "아니오") << endl << endl;
    
    // bool isPalindrome = [](const string& s) {
    //     string clean;
    //     for (char c : s) {
    //         if (isalnum(c)) clean += tolower(c);
    //     }
    //     return clean == string(clean.rbegin(), clean.rend());
    // }(palindromeTest);
    

    string s = "abc";
    int sz = s.size();
    if (!s.empty()) {
        cout << "원본: " << s << endl;
        reverse(s.begin(), s.end());
        cout << "뒤집은 후: " << s << endl << endl;
    }

    //한글은 뒤집을 수가 없다. 뒤집으면 깨져서 대부분 코테 문제에는 안나옴.

    string str = "Hello";
    str.replace(str.begin(), str.begin()+1, "J");   // "Jello"
    cout << str << "\n";

    // string str2 = "안녕이야";
    // str2.replace(str2.begin()+3, str2.begin()+6, "밖");  //0에서 몇바이트까지. 한글 1개가 3바이트여서 3바이트.
    // cout << str2 << "\n";

    
    replace(str.begin(), str.end(), 'l', 'j'); // Hejjo
    cout << str << "\n";
    return 0;
}

