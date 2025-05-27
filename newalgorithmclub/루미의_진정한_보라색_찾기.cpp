#include <bits/stdc++.h>
using namespace std;
int main() {
    double h1, h2;
    double s1, s2;
    double v1, v2;
    double r, g, b;
    cin >> h1 >> h2;
    cin >> s1 >> s2;
    cin >> v1 >> v2;
    cin >> r >> g >> b;

    double mx = max(r, g);
    mx = max(mx, b);

    double mn = min(r, g);
    mn = min(mn, b);

    bool bora = true;
    if (!(mx >= v1 && mx <= v2)) {
        bora = false;
    }
    double s = 255 * (mx - mn) / mx;
    if (!(s >= s1 && s <= s2)) {
        bora = false;
    }

    double h = 0;
    if (mx == r) {
        h = 60 * (g - b) / (mx - mn);
    } else if (mx == g) {
        h = 120 + 60 * (b - r) / (mx - mn);
    } else { // b
        h = 240 + 60 * (r - g) / (mx - mn);
    }

    while (h < 0) {
        h += 360;
    }

    if (!(h >= h1 && h <= h2)) {
        bora = false;
    }

    if (bora) {
        cout << "Lumi will like it.";
    } else {
        cout << "Lumi will not like it.";
    }
}