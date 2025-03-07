#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n;
    cin >> n;
    vector<int> ap;
    vector<int> bp;
    for (int i = 0; i < n; i++)
    {
        int a, b;
        cin >> a >> b;//a와 b의 능력치야.
        ap.push_back(a);
        bp.push_back(b);
    }
    
    int q; cin >> q;
    
    for (int i = 0; i < q; i++)//10^5
    {
        string type;
        int x;
        cin >> type >> x;

        if (type == "A")
        {
            for (int i = 0; i < ap.size(); i++)//10^5
            {
                ap[i] += x;
            }
        } else {
            for (int i = 0; i < bp.size(); i++)
            {
                bp[i] += x;
            }
        }
        int sum = 0;
        for (int i = 0; i < ap.size(); i++)
        {
            sum += max(ap[i],bp[i]);
        }
        cout << sum << "\n";
    }
}