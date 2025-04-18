#include <iomanip>
#include <iostream>
#include <queue>
#include <random>

using namespace std; // ★ std:: 접두어 없이 사용

struct Customer {
    int arrival_time; // 도착 시각(분)
    int service_time; // 서비스 시간(분)
};

int main() {
    /* ===== 파라미터 ===== */
    const int SIM_MINUTES = 480;      // 8시간
    const double ARRIVAL_PROB = 0.35; // 분당 도착 확률
    const int MAX_SERVICE_TIME = 6;   // 1~6분

    /* ===== 난수 엔진 ===== */
    random_device rd;
    mt19937 gen(rd());
    bernoulli_distribution arrive(ARRIVAL_PROB);
    uniform_int_distribution<> svc(1, MAX_SERVICE_TIME);

    /* ===== 상태 변수 ===== */
    queue<Customer> q;
    bool teller_busy = false;
    int remaining_service = 0;

    long long total_wait = 0;
    int served_cnt = 0;

    /* ===== 시뮬레이션 ===== */
    for (int clock = 0; clock < SIM_MINUTES; ++clock) {
        // 1) 새 고객 도착?
        if (arrive(gen)) {
            q.push({clock, svc(gen)});
            cout << "[t=" << clock << "] 고객 도착 (요청 "
                 << q.back().service_time << "분)\n";
        }

        // 2) 창구 처리 중이면 1분 경과시켜. 그리고 0이 된다면 창구 비우고
        // 완료를 표출해.
        if (teller_busy && --remaining_service == 0) {
            teller_busy = false;
            cout << "[t=" << clock << "] 서비스 완료\n";
        }

        // 3) 창구가 비고 대기열이 있으면 다음 고객 호출
        if (!teller_busy && !q.empty()) {
            Customer nxt = q.front();
            q.pop();
            int wait =
                clock - nxt.arrival_time; // 현재시각 - 도착시각 = 기다린시간
            total_wait += wait;
            ++served_cnt;

            teller_busy = true;
            remaining_service = nxt.service_time;

            cout << "[t=" << clock << "] 서비스 시작 "
                 << "(대기 " << wait << "분, 소요 " << remaining_service
                 << "분)\n";
        }
    }

    /* ===== 결과 ===== */
    cout << "\n=== 시뮬레이션 종료 ===\n";
    cout << "총 고객 수 : " << served_cnt << "명\n";
    cout << "전체 대기   : " << total_wait << "분\n";
    if (served_cnt)
        cout << "평균 대기   : " << fixed << setprecision(2)
             << (static_cast<double>(total_wait) / served_cnt) << "분\n";
    else
        cout << "평균 대기   : -- (고객 없음)\n";
}
