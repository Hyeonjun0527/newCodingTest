// Authored by : chjh2129
#include <bits/stdc++.h>
using namespace std;

/*
  현재 입력으로 들어오는 데이터가 아래와 같다고 하자.
  데이터 : [ 1, 2, 3, 4, 5, 6, 7 ]
  두 개의 우선순위 큐를 선언해 아래와 같이 데이터를 저장한다.
  l = [ 4,3,2,1 ] 최대힙의 탑이 중간값 = 4
  r = [ 5, 6, 7 ] 최소힙 최소힙의 탑이 중간값 = 5
 l = 5 r = 4야.그러면 r을 l에 넣고, l = 5,4야. 그리고 l에서 빼서 r에 넣어. 그럼 l = 4 r= 5가 되겠지.
  l.top()은 항상 가운데 값을 가지게 한다.
*/

int n;
priority_queue<int> l;
priority_queue<int, vector<int>, greater<int>> r;
int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    // input
    cin >> n;
    // solve & output
    int cur;
    while(n--){
        cin >> cur;
        (l.size() <= r.size()) ? l.push(cur) : r.push(cur);//중간값 이하를 최대힙에 중간값이상을 최소힙에.
        //cur의 값 크기와 상관없이 단순히 두 힙의 크기를 기준으로 삽입. 일단 정보가 없으니 넣어.
        // 이전 데이터는 이미 올바르게 삽입이 되어있음
        // 현재0 데이터의 값이 반대로 들어갔으니
        // 최대 힙과 최소 힙의 top()을 swap
        if(r.size() && l.top() > r.top()){//r size가 있어. 그런데 l 최대힙값이 r의 최소힙값보다 크면 안대.
            l.push(r.top());//r을 l에 넣고 r을 제거
            r.pop();
            r.push(l.top());//l을 r에 넣고 l을 제거
            l.pop();
        }
        cout << l.top() << '\n';//작은거 출력하라니깐.
    }
}