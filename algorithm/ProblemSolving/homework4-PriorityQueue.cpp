
/*
(1) 구현 방식
각 환자가 도착시각 ArrT
치료를 받기위해 필요한 시간 ReqT
우선순위 Pnum 0 ~ ??
환자 순서 idx

처음에는 우선순위대로 치료받고 같으면 ArrT빠른거로만 처리하면 될 것이라고 생각했다.
그렇게 문제를 풀었는데 마지막 예제를 통과하지 못했다.
그리고 처음에는 무조건 치료시키고 그 다음부터 우선순위대로 치료받고 같으면 ArrT빠른거로 처리하면
될 줄 알았는데 보여진 테스트케이스는 통과했는데, 거절이 나왔다.
이유가 궁금했다.
현재 내 코드는 현재시간을 고려하지 않았고,
우선순위가 높은 환자를 즉시 치료했다.
하지만 이미 5명의 환자가 도착해있는게 아니라는 생각이 들었다.
왜냐하면 치료 시작 시각이 0이기 때문에 도착 시각이 1이고 2이고 3인 사람들은 전부 병원에 없는 환자이다.
그런데 내 코드는 우선순위가 높은 병원에 없는 환자를 치료했으니 코드가 통과를 못한 것이다.
그러므로 코드를 바꿨다. 먼저 현재시간을 변수로 추적하고
먼저 환자를 도착시간 순서로 정렬해야했다. 그래야 도착한 환자부터 처리할 수 있기 때문이다.
대기환자가 없을 때에 도착한 환자는 즉시 치료하게 했다.
모든 환자가 치료될때까지 iteration했다.
우선순위 큐에 들어간 환자( 대기환자 )는 우선순위가 높고 우선순위 같다면 도착시간 빠른 환자를 치료하게 했다.
그렇게 로직을 구현했다.
(2) 시간 복잡도
환자를 정렬하는데 NlogN의 시간이 들었다.
우선순위 큐에 push pop하는 연산은 찾아보니 한번에 logN의 시간이 소요된다고 한다.
최악의 경우에 N번을 반복하니 NlogN의 시간복잡도가 걸린다.
외부 while문안에 내부 while문이 있는데 이 내부 while문은 iteration할때마다 외부 while문의 총 iter 횟수를 줄인다.
그러므로 총 반복횟수가 N번으로 결국 변함이 없고, 우선순위 큐에 push pop하는 결과는 NlogN의 시간복잡도가 맞다.
O(NlogN) + O(NlogN) = O(NlogN) 이므로 총 시간복잡도는 NlogN
*/

#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <cmath>
#include <deque>
#include <queue>
#include <string>



using namespace std;
struct Person {
    int ArrT;
    int Pnum;
    int ReqT;
    int idx;

    bool operator<(const Person& other) const {
        if (Pnum != other.Pnum) {
            return Pnum > other.Pnum;
        } else {
            return ArrT > other.ArrT;
        }
    }
};

int main() {
    int N;
    cin >> N;

    vector<Person> patients(N);
    for (int i = 0; i < N; ++i) {
        cin >> patients[i].Pnum >> patients[i].ArrT >> patients[i].ReqT;
        patients[i].idx = i;
    }

    // 도착 시간으로 정렬
    sort(patients.begin(), patients.end(), [](const Person& a, const Person& b) {
        return a.ArrT < b.ArrT;
    });

    priority_queue<Person> pq;
    vector<int> result(N);
    int currentTime = 0;
    int idx = 0;// patients[idx]는 도착시간 순서대로의 환자들이야

    while (idx < N || !pq.empty()) {//환자 전부 처리하고, 대기환자 전부 처리한다.

        while (idx < N && patients[idx].ArrT <= currentTime) {//도착한 환자만을 푸시해.
            //왜 while문이냐면 같은 시간에 온 환자가 있어서.
            pq.push(patients[idx]);
            ++idx;
        }

        if (!pq.empty()) {
            Person current = pq.top();
            pq.pop();
            result[current.idx] = currentTime;//치료한 시간 기록했어.(sol야)
            currentTime += current.ReqT;//치료해서 시간이 지낫어
        } else {//비었어.

            //대기환자가 없을 때에 도착한 환자는 즉시 치료야.
            //환자가 도착할때까지 기다려야해. 환자도착 event 감지되면 시간 갱신.
            currentTime = patients[idx].ArrT;
        }
    }

    for (int i = 0; i < N; ++i) {
        cout << result[i] << endl;
    }

    return 0;
}