#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void merge_sort(int start, int end);
static vector<int> A;
static vector<int> tmp;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N;
    cin >> N;
    A = vector<int>(N + 1, 0);
    tmp = vector<int>(N + 1, 0);
    for (int i = 1; i <= N; i++) {
        cin >> A[i];
    }
    merge_sort(1, N); // 병합정렬 수행하기

    for (int i = 1; i <= N; i++) {
        cout << A[i] << "\n";
    }
}
void merge_sort(int start, int end) {
    if (end - start == 0)//만나면
        return;
    int mid = start + (end - start) / 2;
    // 재귀함수 형태로 구현
    merge_sort(start, mid);
    merge_sort(mid + 1, end);
    for (int i = start; i <= end; i++) {
        tmp[i] = A[i];
    }
    int k = start;
    int index1 = start;
    int index2 = mid + 1;
    while (index1 <= mid && index2 <= end) { // 두 그룹을 Merge 해주는 로직
        if (tmp[index1] > tmp[index2]) {
            A[k] = tmp[index2];
            k++;
            index2++;
        }
        else {
            A[k] = tmp[index1];
            k++;
            index1++;
        }
    }
    // 한쪽 그룹이 모두 선택된 후 남아있는 값 정리하기
    while (index1 <= mid) {
        A[k] = tmp[index1];
        k++;
        index1++;
    }
    while (index2 <= end) {
        A[k] = tmp[index2];
        k++;
        index2++;
    }
}