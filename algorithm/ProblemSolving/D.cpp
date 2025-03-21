// Authored by : chjh2129
/*
4 2 10
7 4 5 6
8
 */
#include <bits/stdc++.h>
using namespace std;

int n, w, L, ans;
int bridge[105]; // 다리
queue<int> truck; // 트럭

// 배열을 옆으로 밀어낸다.
void go(){
    for(int i = w-1; i > 0; i--) bridge[i] = bridge[i-1];
    bridge[0] = 0;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);

    // input
    cin >> n >> w >> L;//트럭 수 , 다리 길이, 최대 하중
    while(n--){
        int x;
        cin >> x;
        truck.push(x);
    }

    // accumulate(st, en, 0) : 배열의 [st, en) 범위 내 원소값을 모두 더한 값 + 0 을 반환해줌
    // solve
    // *bridge[0]**은 다리의 들어오는 부분. 브릿지배열에 트럭의 무게들이 저장될거임.
    do{
        int total = accumulate(bridge, bridge+w, 0); // 다리 위에 트럭 무게 총합
        if(total <= L){//총 무게 감당 되면...
            total -= bridge[w-1]; // 다리에서 나가는 트럭의 무게 값을 뺀다.
            go(); // 이동
            // 트럭이 있는데, 트럭이 들어갈 경우 다리가 무게를 버틴다.
            if(!truck.empty()&&(total + truck.front() <= L)){
                bridge[0] = truck.front(); truck.pop();
            }
        }
        ans++;
    } while(accumulate(bridge, bridge+w, 0)); // 다리 위에 트럭이 있으면 루프를 계속 진행

    // output
    cout << ans;
}