#include <iostream>
#include <unordered_map>
using namespace std;
typedef long long ll;

int main() {
    //28번째생일
    //전부구매하면 어셉터블
    ll b, n, m;//보유금액 아이템수 구매할려는아이템수
    cin >> b>>n>>m;
    unordered_map<string,ll> mp;
    for (ll i = 0; i < n; i++) {
        string a;
        ll p;
        cin >> a >> p;
        mp[a]= p;
    }

    ll sum = 0;
    for (ll i = 0; i < m; i++) {
        string a;
        cin >> a;
        sum += mp[a];
    }
    
    if (sum <= b) {
        cout << "acceptable";
    } else {
        cout << "unacceptable";
    }
    //n개중에 m개를 구매하려고 해. 구맥능하면 
}