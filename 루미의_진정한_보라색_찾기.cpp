#include <iostream>
#include <algorithm>
using namespace std;
int main() {
    //M구해야돼.
    double a,b,c,d,e,f;
    cin >>a>>b>>c>>d>>e>>f;

    double R,G,B;
    cin>>R>>G>>B;
    double V = max(max(R,G),B);
    double m = min(min(R,G),B);

    double S = 255*(V-m)/V;
    double H = 0;

    if (V == R) {
        H = 60*(G-B)/(V-m);
    }else if (V == G) {
        H = 120 + 60*(B-R)/(V-m);
    } else {
        H = 240 + 60*(R-G)/(V-m);
    }

    if (H < 0) {
        H += 360;
    }

    if (e <= V && V <= f && c <= S && S <= d
    && a <= H && H <= b) {
        cout << "Lumi will like it.";
    } else {
        cout << "Lumi will not like it.";
    }
}