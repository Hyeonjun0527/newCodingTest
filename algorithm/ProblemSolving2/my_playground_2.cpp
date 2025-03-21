#include <bits/stdc++.h>
using namespace std;

vector<int> mom;
int find(int a) {
    return a == mom[a] ? a : mom[a] = find(mom[a]);
}
void uni(int a, int b) {
    a = find(a), b = find(b);
    if (a != b) mom[b] = a;
}

struct Edge {
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cout << "안녕";
    
}
