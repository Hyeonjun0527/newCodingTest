#include <iostream>
#include <vector>

using namespace std;

int main(){
    int t;

    cin >> t;

    for (int i = 0; i < t; i++) {
        int v, h, x, y;
        cin >> v >> h >> x >> y;
        vector<vector<int>> a(v, vector<int>(h, 0));
        int sum = 0;
        for (int j = 0; j < a.size(); j++) {
            for (int k = 0; k < a[j].size(); k++)
            {
                if (a[j][k] == -1) continue;//1이면 체크, -1이면 불가능
                if (a[j][k] == 1) {
                    if (j+x < a.size() && k+y < a[j].size()){
                        a[j+x][k+y] = -1;
                    }
                }

                if (a[j][k] == 0) {
                    a[j][k] == 1;
                    if (j+x < a.size() && k+y < a[j].size()){
                        a[j+x][k+y] = -1;
                    }
                    sum++;
                }
            }
        }
        
        cout << sum << "\n";
        
    }
}