// Authored by : chjh2129
#include <bits/stdc++.h>
using namespace std;

// queue도 비어있는 상태에서 front()나 pop()을 하면 런타임 에러가 발생합니다.

int n, k;
queue<int> q;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);

    // input
    cin >> n >> k;
    for(int i = 1; i <= n; i++) q.push(i);

    // solve & output
    cout << "<";
    while(q.size() > 1){
        for(int i = 1; i < k; i++){
            q.push(q.front());
            q.pop();
        }
        cout << q.front() << ", ";
        q.pop();
    }
    cout << q.front() << ">";
}