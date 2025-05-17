#include <iostream>
#include <stack>
#include <vector>
using namespace std;
int main() {
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        int n, x;
        cin >> n >> x;

        if (n == x) {
            for (int j = 0; j < n - 1; j++) {
                cout << j << " ";
            }
            cout << n - 1;
            cout << "\n";
            continue;
        }

        for (int j = 0; j < x; j++) {
            cout << j << " ";
        }
        for (int j = x + 1; j < n; j++) {
            cout << j << " ";
        }
        cout << x << "\n";
    }
}

/*

int n,x;
    cin >> n >> x;
    0,1,2,3,4
    5 2면 0,1을 앞에 먼저 넣어. 그리고 나머지 5-2-1=2개,3,4야 넣어. 그리고 2
배치. n-1부터 1씩줄여가면서 넣으면 되겟지 2보다 작은거를 먼저 배치
    vector<int>하는데 마지막에 insert
*/