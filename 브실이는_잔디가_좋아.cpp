#include <iostream>
#include <queue>
using namespace std;
struct Friend {
    int id;
    int most_strik;
    int freeze_count;
    int start_date;
    int fail_strik_cnt; // 스트릭 프리즈사용한건 cnt안함.
    const bool operator<(Friend a, Friend o) const {
        if (a.most_strik == o.most_strik) {
            if (a.freeze_count == o.freeze_count) {
                if (a.start_date == o.start_date) {
                    return a.fail_strik_cnt > o.fail_strik_cnt;
                } else {
                    return a.start_date > o.start_date; // 스타트데이트이른사람
                }
            } else {
                return a.freeze_count > o.freeze_count;
            }
        } else {
            return a.most_strik < o.most_strik;
        }
    }
};
bool comp(int Frin, int b) {
    return a > b; // 내림차순 정렬
}

int main() {
    int n, w; // 친구수 스트릭기간에 포함된 주 수
    cin >> n >> w;
    priority_queue<Friend> pq;

    for (int i = 0; i < n; i++) {
        string id;
        cin >> id;

        int most_strik = 0;   // 스트릭최장
        int freeze_count = 0; // 스트릭프리즈사용
        int start_date = 0;
        int fail_strik_cnt = 0;  // 스트릭 프리즈사용한건 cnt안함.
        vector<int> date(7 * w); // 0이 1일임.
        for (int j = 0; j < 7; j++) {
            string strik;
            cin >> strik; // 스트릭의 길이는 w야. 1일 8일 15일  (j+1)*7 + k
            int k = 0;
            for (char c : strik) {

                k++;
            }
        }
        pq.emplace({})
    }
}