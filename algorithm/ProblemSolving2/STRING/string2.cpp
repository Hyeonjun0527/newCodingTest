#include <iostream>
#include <string>
using namespace std;
int main() {

    //기본 탐색
    //원하는 위치에서 탐색
    //뒤에서 탐색
    //비교
    // 변환 :: 숫자 -> 문자열
    // 변환 :: 문자열 -> 숫자
    // 1. 인덱스 기반 순회
    // 2. Range-based 순회 (읽기)
    // 3. Range-based for (수정) + 소문자로

    /* 
    탐색
    */
    string text = "this is a sample text, this is simple.";
    string pattern = "is";
    
    //기본 탐색
    int p = text.find(pattern); // 첫 "is" 찾기

    if (p != string::npos) {
        cout << "'" << pattern << "' found at: " << p << endl; // 2
    } else {
        cout << "'" << pattern << "' not found." << endl;
    }
    //원하는 위치에서 탐색
    int np = text.find(pattern, p + 1); // 2번 다음부터 찾기
    if (np != string::npos) {
        cout << "Next '" << pattern << "' found at: " << np << endl; // 5
    }

    //뒤에서 탐색
    int rp = text.rfind("this"); // 뒤에서 "this" 찾기
    if (rp != string::npos) {
        cout << "Last 'this' found at: " << rp << endl; // 24
    }

    /*
    비교
    */
    string s1 = "apple";
    string s2 = "banana";
    string s3 = "apple";

    if (s1 == s3) {
        cout << "s1 and s3 are equal." << endl;
    }
    if (s1 < s2) {
        cout << "s1 is lexicographically smaller than s2." << endl;
    }

    /*
    변환
    */
    // 변환 :: 숫자 -> 문자열
    int num = 123;
    string str_num = to_string(num);
    str_num += "45"; // "12345"
    cout << "str_num: " << str_num << endl;

    // 변환 :: 문자열 -> 숫자
    string s_int = "456";
    string s_ll = "1234567890123";
    string s_d = "3.14";

    int i_val = stoi(s_int);
    long long ll_val = stoll(s_ll);
    double d_val = stod(s_d);

    cout << "i_val: " << i_val << ", ll_val: " << ll_val << ", d_val: " << d_val << endl;

    /*
     * 순회 
     */

    std::string s = "Hello";

    // 1. 인덱스 기반 순회
    std::cout << "Index-based: ";
    for (int i = 0; i < s.length(); ++i) {
        std::cout << s[i];
    }
    std::cout << std::endl;

    // 2. Range-based 순회 (읽기)
    std::cout << "Range-based: ";
    for (char c : s) {
        std::cout << c;
    }
    std::cout << std::endl;

    // 3. Range-based for (수정)
    std::cout << "Range-based (modify): ";
    for (char &c : s) {
        c = std::tolower(c); // 소문자로
        std::cout << c;
    }
    std::cout << std::endl;

    return 0;
}