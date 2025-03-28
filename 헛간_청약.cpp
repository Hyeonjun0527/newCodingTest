#include <iostream>
using namespace std;
int main() {
    int n, w, h, l;
    int k;
    cin >> n >> w >> h >> l;

    k = (w / l) * (h / l);

    cout << min(n, k);
}