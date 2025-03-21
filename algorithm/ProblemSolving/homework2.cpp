#include <iosfwd>
#include <iostream>
#include <vector>
using namespace std;

// 단어들의 감정 점수 각 단어에 부여된 숫자. 평균 감정 계산
/*
(1) 구현 방식
이 문제는 다섯개의 숫자와 슬라이딩 윈도우의 크기가 주어지고,
전체 정수 컬렉션에 슬라이딩 윈도우가 지나가고, 각 윈도우마다 평균을 구하는 문제이다.
주어진 말 그대로 구현하면 되는 문제이다.
슬라이딩 윈도우는 두 인덱스를 통하여 만들어 낼 수 있으므로 투 포인터를 사용한다.
포인터는 인덱스를 가르키고 이 값을 각각 1씩 증가시켜서 윈도우의 이동을 구현할 수 있다.
시나리오를 돌려보면,
5
1 2 3 4 5
3
window1 :: 1 2 3 >> 2
window2 :: 2 3 4 >> 3
window3 :: 3 4 5 >> 4


(2) 시간 복잡도
주어진 정수 컬렉션을 배열에 담는데에 O(N)의 시간복잡도가 걸린다.

처음에 로직을 짤 때는 슬라이딩윈도우마다 평균을 그냥 구하면 될 줄 알았다.
하지만 그렇게 로직을 짜니 O(N^2)시간복잡도가 나왔다.
while문(슬라이딩 윈도우 이동 로직)에서 바깥의 while문은 N-K+1번 로직이 돌아간다.
최악의 경우에 N번이다.
내부 반복문의 시간복잡도를 계산할 때 착각할 만한 것이 있다.
내부 반복문의 시간복잡도를 계산할 때 최악의 경우에 N번 반복할 수 있다.
바깥 반복문이 N번 반복되는 경우는 right=1이므로, K = 1이다.(윈도우 크기가 1)
내부 반복문이 N번 반복되는 경우는 K = N(윈도우 크기가 N)이다.
K=N/2(k는 정수)라고 하면 바깥 반복문은 N/2번, 내부는 N/2번이다.
시간복잡도는 1*N , 2*(N-1), ... 2/N * 2/N 으로 N과 K에 따라 변하고
최악의 경우에는 N^2/4으로 시간복잡도는 O(N^2)이다.
왜냐하면 각 항을 일반화한 다음 함수로 나타내면 f(i) = i * (n - i + 1)이다.
2차함수이므로 -b/2a가 꼭짓점이다. n+1/2인 경우 최대값을 가진다.
대략 n/2근처에서 최대값이다. 그래서 K=N/2일때가 최악의 시간복잡도이다.
주어진 조건의 N은 10^6이고 그러므로 시간복잡도가 O(N^2)이면 풀 수 없다.

그래서 이 슬라이딩 윈도우를 만들때 중복되는 계산을 제거해야했다.
반복문을 통해서 원소들을 다 더해 평균을 구하면 안됐다.
그래서 기존에 더한 sum에 left와 right를 뺴는 방식을 선택했다.
그러면 시간복잡도가 O(N)으로 줄어든다.
구간합으로도 구할 수 있다. 구간합으로 구하더라도 시간복잡도는 같다.


*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N;
    cin >> N;
    vector<int> A(N);

    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }

    //슬라이딩 윈도우는 어떻게 구현햇더라 1 2 3 4 5
    //두 개의 포인터를 1과 3에 두자
    int left = 0;
    int right = 0;
    cin >> right;//윈도우의 크기가 들어와
    right--;
    //L=3이면 0,1,2가 윈도우니깐.

    //left right가 0,2 >> 1,3 >> 2,4 이렇게 가면 대 지금 0,2야. 윈도우 0~2 만들어바

    //right <= 마지막인덱스

    bool allFail = true;//모두 실패하면 -1 출력하래.
    int sum = 0;
    for (int i = left; i <= right; i++) {
        sum += A[i];
    }//처음 윈도우의 sum 구한거야.

    while (right <= static_cast<int>(A.size())-1) {//right가 마지막인덱스전까지 돌아야지. N-1이야.
        //여기 평균구하는거잇고 출력하면댐 0,2 >> 1,3 >> 2,4
        //i = 0 1 2

        //나누어떨어지지않으면 구하는 평균값이 정수가 아니자나 그러면 출력하지마
        if (sum % (right - left + 1) != 0) {
            left++;
            right++;
            continue;
        }
        allFail = false;
        int avg = sum / (right - left + 1);
        cout << avg << "\n";

        sum -= A[left];
        sum += A[right + 1];
        left++;
        right++;

    }

    if (allFail) {
        cout << -1 << endl;
    }


    return 0;
}

/*
 *구간합으로 구한 코드
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int N;
    cin >> N;
    vector<int> A(N);
    vector<int> S(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
        S[i] = S[i-1] + A[i];
    }
    int left = 0;
    int right = 0;
    cin >> right;
    right--;
    bool allFail = true;
    int sum = 0;
    for (int i = 0; i <= right; i++) {
        sum += A[i];
    }
    while (right <= static_cast<int>(A.size())-1) {
        if (sum % (right - left + 1) != 0) {
            left++;
            right++;
            continue;
        }
        allFail = false;
        int avg = sum / (right - left + 1);
        cout << avg << "\n";
        left++;
        right++;
        sum = S[right] - S[left - 1];
    }
    if (allFail) {
        cout << -1 << endl;
    }
    return 0;
}
*/
