
/* 

today	terms	privacies	result
"2022.05.19"	["A 6", "B 12", "C 3"]	["2021.05.02 A", "2021.07.01 B", "2022.02.19 C", "2022.02.20 C"]	[1, 3]
"2020.01.01"	["Z 3", "D 5"]	["2019.01.01 D", "2019.11.15 Z", "2019.08.02 D", "2019.07.01 D", "2018.12.28 Z"]	[1, 4, 5]
유효기한 지났는지 아닌지 확인하는 문제 

2021.05.02 A는 유효기한이 지났어.
https://school.programmers.co.kr/learn/courses/30/lessons/150370/solution_groups?language=cpp
*/

#include <algorithm>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
// 날짜를 일수로 변환하는 함수
int convertToTotalDays(int y, int m, int d) {
    return y * 12 * 28 + (m - 1) * 28 + d;
}

// 문자열 형식의 날짜를 파싱하는 함수
void parseDate(const string& s, int& y, int& m, int& d) {
    y = stoi(s.substr(0, 4));
    m = stoi(s.substr(5, 2));
    d = stoi(s.substr(8, 2));
}

vector<int> solution(string today, vector<string> terms, vector<string> privacies) {
    vector<int> answer;
    
    // today 날짜 파싱
    int y, m, d;
    parseDate(today, y, m, d);
    int todayD = convertToTotalDays(y, m, d);

    vector<int> td(privacies.size());// 토탈 날짜
    map<char, int> mp;
    
    // terms 파싱
    for (int i = 0; i < terms.size(); i++) {
        stringstream ss(terms[i]);
        char c;
        int m;
        ss >> c >> m;
        mp[c] = m;
    }
    
    // privacies 처리
    for (int i = 0; i < privacies.size(); i++) {
        int y, m, d;
        parseDate(privacies[i], y, m, d);
        char c = privacies[i].back();
        td[i] = convertToTotalDays(y, m, d) + mp[c] * 28 - 1;
        //유효기간 계산 시 마지막 날을 포함하지 않아서 1을 뺌.
    }
    
    // 만료된 개인정보 찾기
    for (int i = 0; i < td.size(); i++) {
        if (td[i] < todayD) {
            answer.push_back(i + 1);
        }
    }
    return answer;
}