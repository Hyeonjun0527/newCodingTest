//도로의 길이기 2^2해서 4야
/*
 * 재활용 쓰레기 수는 2야
 * a와 b는 각각 힘을 의미하게 돼
 * info 배열에는 2개 정수가 있어. 최댓값은 2^n이야. 각 원소가 쓰레기 위치를 말해.
 *
 * {1, 3} 이면 도로의 길이 4잖아.
 * 1 2 3 4에서 1과 3에 쓰레기 있는거야.
 * 한번에 처리하면 B * n_a(스레기수) * C(현재청소구역길이) 가 들어.
 * 한번에 처리하면 2 * 2 * 4가 들어 16이 들어. 그거한번 계산할때마다 N번반복하네?
 * 그럴필요없어 정적으로 처리하면 돼
 * 나눠서 처리하면 1 2 / 3 4 로 나눠.
 * 이제 한번에 처리하면 2*1*2 + 2*1*2 = 8이야.
 * 또 나눠서 처리하면 1 / 2 / 3 / 4 로 나뉘어.
 * 그러면 2*1*1 + 1 + 2*1*1 + 1 = 6 이야.
 *
 * 1 2 3 4가 1 2와 3 4로 나뉘지
 * 1 2가 1과 2로 나뉘고.
 *
 * 이렇게 계속 나눠. 그런데 나누는게 효율적일지 고민해보고 나눠.
 *
 * 나누는거는 재귀함수 써야댈거같아.
 *
 * 인자는 배열이랑 인덱스
 */


#include <bits/stdc++.h>
using namespace std;

//0 1 2 3 4 5 6 7이야.
//0 3
//3 7 이렇게 나눠지네 0 1 2 3
long long divide(vector<int> trash_group, int start, int end,  int left, int right, int A, int B) {
    //쓰레기
    if (left > right) {
        return A;
    }
    int n_a = right - left + 1;

    long long cleanAreaLength = (end - start + 1);
    long long instance_value = B * n_a * cleanAreaLength;

    if (start == end) {
        return instance_value;
    }


    int mid_start = (start + end) / 2;


    //쓰레기 {1,3,5,7}이면 mid = 4이고, 왼쪽 divide는 1 3만 가능한 쓰레기야
    //오른쪽 divide는 5 7만 가능한 쓰레기야.
    //그러면 (left,mid_left) (mid_left+1,end)
    int mid_left = left - 1; // 초기값을 left-1로 설정
    for (int i = left; i <= right; ++i) {
        if (trash_group[i] > mid_start) {
            break; // mid보다 큰 첫 번째 값을 찾으면 중단
        }
        mid_left = i; // i = 2에서 trash_group[2] = 5 이고 중단됐을 때 mid_left = 1
    }


    long long left_result = divide(trash_group, start, mid_start, left, mid_left, A, B);
    long long right_result = divide(trash_group, mid_start + 1, end,  mid_left+ 1, right, A, B);
    return min(instance_value, left_result + right_result);
}

long long get_minimal_effort(int n, int k, int a, int b, int info[]) {

    //내가 할 건 계산이야.
    //info :: {1 3}이 주어지면
    int road_length = (1 << n);

    //인덱스 0 ~ k-1까지
    vector<int> trash_group(info, info + k);
    //쓰레기도
    //초기화 했어.

    long long sol = divide(trash_group,1, road_length, 0, k-1, a, b);


    return sol;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int info[] = {1, 3};
    cout << get_minimal_effort(2,2,1,2, info) << endl;

}
