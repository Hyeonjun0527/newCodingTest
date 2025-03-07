#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

int main() {
    int t;

    cin >> t;

    for (int i = 0; i < t; i++) {
        string s;
        cin >> s;
        
        int num = 0;
        int num_idx = 0;
        for (int j = 0; j < s.size(); j++)
        {
            
            if (s[j] != '!') {
                // cout << s[j] << "\n";
                num = s[j] - '0';
                num_idx = j;
                // cout << num_idx << "\n";
            }
        }

        for (int j = num_idx + 1 ; j < s.size(); j++)
        {
            if (num == 0) num = 1;
            else num = 1;
        }

        for (int j = 0; j < num_idx; j++) {
            if (num == 0) num = 1;
            else if (num == 1) num = 0;
        }
        cout << num << "\n";
    }
    
}