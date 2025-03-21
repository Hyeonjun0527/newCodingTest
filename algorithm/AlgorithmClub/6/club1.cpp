
//이걸 어떻게 풀까 생각해보면 날짜가 주어졌어. 프라이버시마다 갑시 있지
//프라이버시에 텀즈 더해서 비교하고 출력하면 되는 문제야
//어케 더하냐가 중요함
//더하고 12를 넘으면 13이면 그러면 앞에숫자를 더해야함. 스트링으로 주어진거 파싱해야 될거같아
//그리고 12를 빼면 되지.


#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <tuple>ma

using namespace std;

vector<int> solution(string today, vector<string> terms, vector<string> privacies) {
    vector<int> answer;
    vector<tuple<int,int,int>> calendars;
    vector<string> alphabet;


    for (auto& privacy : privacies) {
        //일단 날짜랑 A를 나눴어.
        //그리고 각각 담았어.
        stringstream ss(privacy);
        string calendar_s;
        string alphabet_s;
        ss >> calendar_s;
        ss >> alphabet_s;//받은거야 받았어. 이제

        //카렌다s이거를 .을 기준으로 나눠야 해

        stringstream ss2(calendar_s);
        string token;
        tuple<int,int,int> calendar;
        string year; string month; string day;
        getline(ss2, year, '.');
        getline(ss2, month, '.');
        getline(ss2, day, '.');
        calendar = make_tuple(stoi(year),stoi(month),stoi(day));

        calendars.emplace_back(calendar);
        //카렌다에 담았지 이제 A도 담자.
        alphabet.push_back(alphabet_s);
    }

    for (int i = 0; i < calendars.size(); i++) {
        cout << get<0>(calendars[i]) << " ";
        cout << get<1>(calendars[i]) << " ";
        cout << get<2>(calendars[i]) << " ";
        cout << alphabet[i] << " ";
        cout << "\n";
    }

    cout << "프라이버시 사이즈 :: " << privacies.size() << "\n";


    tuple<int,int,int> temp_cal;

    for (int i = 0; i < privacies.size(); i++) {
        //다 담았으면 비교하자.

        bool is_yes = false;
        for (const string& s3 : terms) {
            stringstream ss3(s3);
            string alphabet2;
            string number_s;
            ss3 >> alphabet2;
            ss3 >> number_s;
            int number = stoi(number_s);
            //여기 알파벳2와 알파벳비교하면 댐.
            if (alphabet2 ==alphabet[i]) {

                int temp = get<1>(calendars[i]) + number;
                //이게 12를 넘으면 년도 + 1하고 나는 - 12하고
                if (temp >= 13) {


                    //temp가 100이면
                    int yearplus = temp / 12;
                    int monthplus = temp % 12;//

                    if (monthplus == 0) {
                        yearplus--;
                        monthplus = 12;
                    }
                    temp_cal = make_tuple(get<0>(calendars[i]) + yearplus,
                        monthplus,
                        get<2>(calendars[i])
                        );
                    int y = get<0>(temp_cal);
                    int m = get<1>(temp_cal);
                    int d = get<2>(temp_cal);
                    d -= 1;
                    //일을 1일 빼줘. 빼주는데 만약에 0이면, 먼스를 하루 줄이고 day를 28로 한다.
                    if (d == 0) {
                        m -= 1;
                        d = 28;
                        if (m == 0) {
                            y -= 1;
                            m = 12;
                        }
                    }
                    temp_cal = make_tuple(y,m,d);

                    cout <<"파기날짜" << "i :: " << i << "\n";
                    cout << get<0>(temp_cal) << " ";
                    cout << get<1>(temp_cal) << " ";
                    cout << get<2>(temp_cal) << " ";
                    cout << "\n";

                } else {//12를 안넘으면 단순히 더해
                    temp_cal = make_tuple(get<0>(calendars[i]),
                        temp,
                        get<2>(calendars[i]));

                    int y = get<0>(temp_cal);
                    int m = get<1>(temp_cal);
                    int d = get<2>(temp_cal);
                    d -= 1;
                    //일을 1일 빼줘. 빼주는데 만약에 0이면, 먼스를 하루 줄이고 day를 28로 한다.
                    if (d == 0) {
                        m -= 1;
                        d = 28;
                        if (m == 0) {
                            y -= 1;
                            m = 12;
                        }
                    }
                    temp_cal = make_tuple(y,m,d);

                    cout <<"파기날짜" << "i :: " << i << "\n";
                    cout << get<0>(temp_cal) << " ";
                    cout << get<1>(temp_cal) << " ";
                    cout << get<2>(temp_cal) << " ";
                    cout << "\n";
                }

                //string인 today와 temp_cal을 비교하면 된다.
                //temp_cal 의 년도가 높으면 파기대상
                //년도는 같아 월이 높으면 파기 대상
                //월은 같아 날짜가 높으면 파기 대상
                int y = (today[0] - '0')*1000 + (today[1]-'0')*100 + (today[2]-'0')*10 + (today[3]-'0');
                int m = (today[5] - '0')*10 + (today[6]-'0');
                int d = (today[8] - '0')*10 + (today[9] - '0');
                if (get<0>(temp_cal) < y) {
                    answer.push_back(i+1);
                } else if (get<0>(temp_cal) == y && get<1>(temp_cal) < m) {
                    answer.push_back(i+1);
                } else if (get<0>(temp_cal) == y && get<1>(temp_cal) == m && get<2>(temp_cal) < d) {
                    answer.push_back(i+1);
                }
            }
        }//terms 반복
    }//i 반복 privacy 반복

    for (int data : answer) {
        cout << data <<" ";
    }

    return answer;
}