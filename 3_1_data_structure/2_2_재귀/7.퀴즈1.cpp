#include <iostream>
#include <algorithm>
using namespace std;
int main() {
  string a;
  cin >> a;

  for (int i = 0; i < a.length(); i++) {
    cout << a[a.length() - i - 1];
  }

}