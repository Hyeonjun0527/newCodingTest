#include <bits/stdc++.h>
using namespace std;
struct Student {
    string n;
    int s, r, c;
    Student(string name, int s, int r, int c) : n(name), s(s), r(r), c(c) {
    }
    bool operator<(const Student other) {
        int o = other.janghak();
        int me = janghak(); // 나<너 를 리턴하면 오름차순

        if (me == o) {
            if (c == other.c) {
                return n < other.n;
            } else {
                return c < other.c;
            }
        } else {
            return me > o;
        }
    };

    int janghak() const {
        return floor(s * s * s / (c * (r + 1)));
    };
};
int main() {
    int n;
    cin >> n;
    vector<Student> v;
    for (int i = 0; i < n; i++) {
        string n;
        int s, r, c; // name score risk cost
        cin >> n >> s >> r >> c;
        v.emplace_back(n, s, r, c);
    }
    sort(v.begin(), v.end());

    cout << v[1].n;
}

// 나 정렬함수랑 struct 더 공부해야대