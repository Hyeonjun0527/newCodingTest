#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;

struct E{
    ll idx = 0, minv = - 1, maxv = -1, minh = -1, maxh = -1;
    bool operator< (const E& other) const {
        ll temp = (maxv - minv) * (maxh - minh);
        ll other_temp = (other.maxv - other.minv) * (other.maxh - other.minh);
        
        if (temp != other_temp) {
            return temp > other_temp;//배열 sort면 내림차순, pq면 오름차순
        }
        return idx < other.idx;//같으면 배열 오름차 작은거 택
    }
};

int main() {
    int r, t;
    cin >> r >> t;
    int n;
    cin >> n;

    vector<E> a(n+1);
    for (int i = 0; i < n; i++)
    {
        ll k, v, h;
        cin >> k >> v >> h;//k는 유물 번호
        a[k].idx = k;
        if (a[k].minv == -1) {
            a[k].minv = v;
            a[k].maxv = v;
            a[k].minh = h;
            a[k].maxh = h;
        } else {
            a[k].minv = min(a[k].minv, v);
            a[k].maxv = max(a[k].maxv, v);
            a[k].minh = min(a[k].minh, h);
            a[k].maxh = max(a[k].maxh, h);
        }
    }
    sort(a.begin(), a.end());

    E e = a.front();

    if (e.minv == -1) {
        cout << e.idx << " " << 1; 
        return 0;
    }

    cout << e.idx << " " << (e.maxv - e.minv + 1) * (e.maxh - e.minh + 1);
    
}