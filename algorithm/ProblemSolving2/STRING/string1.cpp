#include <iostream>
#include <string>
using namespace std;
int main() {

    /* 
    단순 입력과  getline
    */

    string word, line;
    cin >> word; // "Hello World" 입력 시 "Hello"만 word에 저장됨

    cout << word << "\n";

    // cin 버퍼 비우기 (getline 사용 전 필수)
    cin.ignore(); // 중요!

    getline(cin, line);

    cout << line << "\n";

    /*
    이어 붙이기, 삭제, 삽입, 교체
    */
   //이어불이기
    string s = "abc";
    s += "def";       // "abcdef"
    s.erase(3, 3);    // 3번 인덱스부터 3개 삭제 ("def" 삭제) -> "abcghi"
    cout << "이어붙이기: " << s << "\n";
    // 삭제
    s.erase(3, 3);    // 3번 인덱스부터 3개 삭제 ("def" 삭제) -> "abcghi"
    cout << "삭제: " << s << "\n";

    // 삽입
    s.insert(3, "DEF"); // 3번 인덱스에 "DEF" 삽입 -> "abcDEFghi"
    cout << "삽입: " << s << "\n";

    // 교체
    s.replace(3, 3, "def"); // 3번부터 3개를 "def"로 교체 -> "abcdefghi"
    cout << "교체: " << s << "\n";

    s.clear();
    cout << "clear 후 길이: " << s.length() << "\n"; // 0

    string ss = "Programming";
    string sub1 = ss.substr(0, 7); // "Program"
    string sub2 = ss.substr(7);    // "ming" (7번부터 끝까지)

    cout << "sub1: " << sub1 << endl;
    cout << "sub2: " << sub2 << endl;

    return 0;
}