#include <iomanip>
#include <iostream>
using namespace std;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  double pi = 3.14159265358979323846;
  double a;
  cin >> a;
  cout << fixed << setprecision(6);
  cout << pi * a * a << "\n";
  cout << 2 * a * a << "\n";
}