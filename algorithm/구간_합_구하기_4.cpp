#include <iostream>
#include <vector>

using namespace std;

int main() {

    vector<int> a(100000);//구간 합 배열
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        int b;
        cin >> b;
        a[i] = a[i-1] + b;
    }

    for (int i = 0; i < m; i++) {
        int s, e;
        cin >> s >> e;
        cout << a[e] - a[s-1] << "\n";
    }
}