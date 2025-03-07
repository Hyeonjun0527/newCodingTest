#include <iostream>
#include <string>
using namespace std;

int main()
{
    int j, n;
    cin >> j >> n;
    cin.ignore();
    int t = 0;
    for (int i = 0; i < n; i++)
    {
        string a;
        getline(cin, a); // A : 65 ~ 90//26개니까
        // cout << a << "\n";
        // cout << (char)65;
        // cout << (char)90;
        // cout << (char)97;//25더하니까
        // cout << (char)122;
        int sum = 0;
        for (char cc : a)
        {
            int c = (int)cc;
            if (cc == '0' || cc == '1' || cc == '2' || cc == '3' || cc == '4' || cc == '5' || cc == '6' || cc == '7' || cc == '8' || cc == '9' ||
                (c >= 97 && c <= 122))
            {
                sum += 2;
            }
            else if (c >= 65 && c <= 90)
            {
                sum += 4;
            }
            else if (cc == ' ')
            {
                sum += 1;
            }
        }
        // cout << sum << "\n";
        if (sum <= j)
        {
            t++;
        }
    }
    cout << t;
}