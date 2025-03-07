#include <iostream>
#include <string>

using namespace std;

int main()
{
    while (true)
    {
        string a;
        cin.ignore();
        getline(cin, a);
        if (a == "#") break;
        int b = 0;
        for (char c : a){
            if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U'){
                b++;
            }
        }
        cout << b << "\n";
    }
}