#include <iostream>
#include <vector>
#include <cmath>
#include <string>
using namespace std;
bool isPalindrome(int target);

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    long N;
    cin >> N;

    constexpr int SIZE = 10'000'001;
    // constexpr int MAX_LIMIT = SIZE - 1;
    long A[SIZE];

    for (int i = 2; i < SIZE; i++) {
        A[i] = i;
    }
    //왜 컨티뉴하냐면 2배수부터 싹 지우니까 그런거임
    for (int i = 2; i < sqrt(SIZE); i++) { // 제곱근 까지만 수행
        if (A[i] == 0) {
            continue;
        }
        for (int temp = i + i; temp < SIZE; temp += i) { // 배수 지우기
            A[temp] = 0;
        }
    }
    // N부터 1씩 증가시켜가면서 소수와 펠린드롬 수가 맞는지 확인
    for (int i = N ;; i++) {
        if (A[i] != 0 && isPalindrome(i)) {// A[i]해도 되고 i해도 됨.
            cout << i << "\n";
            break;
        }
    }

}

//타겟을 스트링으로
bool isPalindrome(int target) {// 팰린드롬 수 판별 함수
    string str = to_string(target);// 숫자를 문자열로 변환
    for (size_t start = 0, end = str.size() - 1; start < end; start++, end--) {
        if (str[start] != str[end]) {
            return false;
        }
    }
    return true;
}
/*
size_t start = 0;
size_t end = str.size() - 1;
while (start < end) {
    if (str[start] != str[end]) {
        return false;
    }
    start++;
    end--;
}
 */