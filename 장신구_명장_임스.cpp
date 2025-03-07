#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{

    int p, n;
    cin >> p >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    sort(a.begin(), a.end());

    int cnt = 0;

    if (p < 200)
    {
        for (int e : a)
        {
            p += e;
            cnt++;
            if (p >= 200)
                break;
        }
        cout << cnt;
    } else {
        cout << 0;
    }
}