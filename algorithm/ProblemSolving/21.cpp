#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void merge_sort(int start, int end);
static vector<int> A;
static vector<int> tmp;
static long result;

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
    result = 0;
    merge_sort(1, N); // 병합정렬 수행하기

    cout << result << "\n";
}

//재귀함수에서 매개변수를 놓는다는 건 각 반복마다 가져야되는 정보라는거야.
// 작업장, 하얀색 박스,
void merge_sort(int start, int end) {
    if (end - start < 1)
        return;
    int mid = start + (end - start) / 2;
    // 재귀함수 형태로 구현
    merge_sort(start, mid);
    merge_sort(mid + 1, end);
    //왜 복사하는거지? tmp는 작업장이야.
    for (int i = start; i <= end; i++) {
        tmp[i] = A[i];
    }
    //k는 하얀색박스 + 1의 값을 가져.
    int k = start;
    //왼쪽 배열이야. 배열1 시작
    int index1 = start;
    //오른쪽 배열이야. 배열2 시작
    int index2 = mid + 1;
    while (index1 <= mid && index2 <= end) { // 두 그룹을 Merge 해주는 로직
        if (tmp[index1] > tmp[index2]) {//index1이 더 크면 index2를 결과배열에 넣고 스왑해야대지.
            A[k] = tmp[index2];
            result += index2 - k; // 뒤쪽 데이터 값이 작아 선택되는 경우 결과 값 업데이트
            //스왑수가 이렇게 대는구나 왜냐면 index2위치에서 제일 앞으로 가는데 하얀색박스 개수 세면 안되는데
            //index2는 하얀색 박스 개수까지 포함한거야 그래서 k를 빼줘.
            k++;
            index2++;
        }
        else {//index2의 값이 더 크면 index1을 결과배열에 넣어. 스왑은 없어.
            A[k] = tmp[index1];
            k++;
            index1++;
        }
    }
    // 한쪽 그룹이 모두 선택된 후 남아있는 값 정리하기
    while (index1 <= mid) {
        A[k] = tmp[index1];//tmp왼쪽 오른쪽 두개 작업장배열에 있는거 남은거 결과배열에 넣어야지
        k++;//k은 하얀색박스 개수 + 1이야. 기본인덱스 시작이 1이고, 하얀색백스 개수를 더한거.
        index1++;//하나씩 차근차근
    }
    while (index2 <= end) {
        A[k] = tmp[index2];
        k++;
        index2++;
    }

}