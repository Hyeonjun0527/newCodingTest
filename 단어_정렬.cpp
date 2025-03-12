#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

int main() {
  int n;
  cin >> n;
  set<string> a;
  for (int i = 0; i < n; i++) {
    string b;
    cin >> b;
    a.emplace(b);
  }
  vector<string> c(a.begin(), a.end());

  sort(c.begin(), c.end(), [](const string &a, const string& b) {
    if (a.size() == b.size())
      return a < b;
    return a.size() < b.size();
  });

  for (string s : c) {
    cout << s << "\n";
  }
}