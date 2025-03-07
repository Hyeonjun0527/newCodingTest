#include <iostream>

using namespace std;

int main()
{

    int n;
    cin >> n;

    int use = 0; // 현재사용량
    int cum = 0; // 누적사용량
    int cp = -1; // 현재 휴대폰 종류
    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;

        // 종류 같으면 현재의 2배
        if (cp == a)
        {
            use *= 2;
        }
        else
        { // 다르면
            use = 2;
        }

        cum += use;

        if (cum >= 100)
        {
            cum = 0;
            use = 0;
            cp = -1;
        }
        else
        {
            cp = a;
        }
        // cout << use << "\n";
        // cout << cum << "\n"
        //      << "\n";
    }
    cout << cum;
}