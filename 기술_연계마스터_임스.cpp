#include <iostream>
#include <vector>
#include <deque>
using namespace std;

int main()
{

    // cout << "??" <<"\n";
    int n;
    cin >> n;
    string a;
    cin >> a;
    int cnt = 0;
    // 83 >>> 75; S K
    // 76 >>> 82; L R

    // cout << "??" << "\n";
    deque<int> dq;
    for (char e : a)
    {
        // cout << (int)e << "\n"; // 49 57까지
        int t = ((int)e);
        if (t >= 49 && t <= 57)
        {
            cnt++;
        }
        else
        {

            if (!dq.empty() && dq.back() == 83 && t == 75)
            {
                cnt++;
                dq.pop_back();
                continue;
            }
            if (!dq.empty() && dq.back() == 76 && t == 82)
            {
                cnt++;
                dq.pop_back();
                continue;
            }
            if (!dq.empty() && dq.back() != 83 && t == 75)
                break;
            if (!dq.empty() && dq.back() != 76 && t == 82)
                break;
            
            dq.push_back(t);
            // cout << dq.back() << "\n";
            // 이전기술 현재기술
        }
    }
    cout << cnt;
}