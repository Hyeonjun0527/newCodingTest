/*
2042 백준
구간 합 구하기

비교할 만한 문제로 YonseiWaterpark가 있다.

5 2 2
1
2
3
4
5
1 3 6
2 2 5
1 5 2
2 3 5
 */

#include <cmath>
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

vector<long long> tree;

//lnsi
//tree leef_node_start_index ~ leef_node_start_index + n - 1 = 2n-1
void set_tree(int size) { // 초기 트리 생성
  //원본배열이 0based이든 1based이든은 무관계야.
  //원본배열의 based가 바뀌면 get_sum과 update에는 영향을 줘.
  //여기는 무조건 size - 1이라고 보면 돼. 트리랑만 관련이 있는거야.
  //트리는 1based지. 그래서 size - 1 ~ 1까지야. 왜 size - 1이냐. size가 leef_node_start_index 잖아.
  //리프노드 먼저 다 넣었다고 가정. 즉 뒤에꺼는 다 있는거임
    for (int i = size - 1; i >= 1; i--) {
        tree[i] = tree[2 * i] + tree[2 * i + 1];// [i] = [2i] + [2i + 1]
    }
}
/*
void set_tree(int size) {
	for (int i = size; i >= 0; i--) {
		tree[i] =
	}
}
 */
//세그먼트트리는 1 based, 쿼리는 1 based
//배열은 0 based야 평범한데 1 based네.
// 0 based일때 n 더햇자나 그게 1로 변했어.
//그러면 n에도 -1 해주면 대. 원본배열이 1based면 +size-1한다. 0based면 +size한다.
long long get_sum(int size, int s, int e) { // 구간 합 함수
    s += size - 1; // 리프 노드 시작 위치로 변환
    e += size - 1;
    long long sum = 0;
    while (s <= e) {
      //홀
        if (s & 1) sum += tree[s++]; // 왼쪽 노드 포함
      //짝
        if (!(e & 1)) sum += tree[e--]; // 오른쪽 노드 포함
        s /= 2;
        e /= 2;
    }
    return sum;
}
/*
long get_max(int size, int s, int e) {
    s += size - 1;
    e += size - 1;
    long max_value = LLONG_MIN;
    while (s <= e) {
        if (s & 1) max_value = max(max_value, tree[s++]);
        if (e & 1) max_value = max(max_value, tree[e--]);
        s /= 2;
        e /= 2;
    }
    return max_value;
}
 */

void update(int size, int i, long long value) { // index의 값을 val로 변환하고, 트리 전체에 반영하는 변경 함수.
    i += size - 1	; // 리프 노드 시작 위치로 변환
    tree[i] = value; // 리프 노드 값 갱신
    while (i > 1) { // 루트 노드까지 갱신
        i /= 2; // 부모 노드로 이동
        tree[i] = tree[i * 2] + tree[i * 2 + 1]; // 왼쪽 자식과 오른쪽 자식의 합으로 부모 노드 갱신
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N, M, K;
    cin >> N >> M >> K; // 수의 개수, 변경이 일어나는 횟수, 구간 합 구하는 횟수

    //완전 이진 트리를 구성하기 위한 리프 노드의 개수야. 완전이진트리는 리프노드 수 x 2 = 전체 노드수, 리프노드 수 = leefNodeStartIndex
    int size = 1;
    while (size < N) size *= 2;
    //size보다 큰 2의 배수가 리프노드 개수야.

    //size 는 leef_node_start_index를 의미해 size === leef_node_start_index = 완전이진트리 모든 노드 수 / 2
    //size 는 leef_node 개수를 의미해.
    //포셀로야.
    // int size = pow(2,ceil(log2(N)));

    tree.resize(2 * size, 0);

    // 리프 노드에 데이터를 입력 받기 leefNodeStartIndex ~ leefNodeStartIndex + n-1 까지 입력받음.
    for (int i = size; i <= size + N - 1; i++) {
        cin >> tree[i];
    }//트리가 1베이스드니까는 0 버려. 그리고 1~7까지 8부터 리프노드. 번호가 size ~ size+=size-1;
    set_tree(size); // 세그먼트 트리 생성
    //segTree[]는 1based야. 0based segTree[] 만들다가는 머리 깨진다. 하지 말아야 할 것에 대한 경험도 실력임.
    //세그먼트트리는 기존배열과 세그먼트 트리배열이 있잖아. 기존배열의 인덱스는 0,1based이든 괜찮아. 조정하면 돼.

    for (int i = 0; i < M + K; i++) {
        long a, s, e;
        cin >> a >> s >> e;

        //문제가 1 base이다. s는 1<=s<=N번째, e는 s<=e<=N번째
        if (a == 1) { // 값 변경
            update(size, s, e); // 1-based 인덱스 그대로 전달
        } else if (a == 2) { // 구간 합
            cout << get_sum(size, s, e) << "\n"; // 1-based 인덱스 그대로 전달
        }
    }
    return 0;
}





/*
void update(int size, int index, long val) { // 구간 최대값 갱신 함수
    index += size - 1; // 리프 노드 시작 위치로 변환

    tree[index] = val; // 리프 노드 값을 갱신
    while (index > 1) {
        index /= 2; // 부모 노드로 이동
        tree[index] = max(tree[index * 2], tree[index * 2 + 1]); // 자식 노드들의 최댓값을 부모 노드로 반영
    }
}
 */

/*void update(int size, int index, long val) { // index의 값을 val로 변환하고, 트리 전체에 반영하는. 변경 함수.
    index+= size - 1; // 리프 노드 시작 위치로 변환
    tree[index] = val;

    long diff = val - tree[index];
    while (index > 0) {
        index /= 2;
        tree[index] += diff;
    }
}*/