#include <bits/stdc++.h>
using namespace std;

/*
(1) 구현 방식
자릿수의 합이 소수인 숫자쌍끼리의 GCD중 제일 큰 GCD를 찾는다.
조건을 만족하는 숫자가 0개나 1개면 -1을 출력한다.

내가 문제를 해석한 바로는
각 원소의 자릿수의 합 구한다.
그 자릿수의 합이 소수인지 구한다.
이 조건을 통과한 수들 각각의 GCD 중에 가장 큰 GCD를 출력한다.
이런식으로 진행된다.

시나리오를 돌려보면
5
12 13 15 20 30
3 4 6 2 3 (자릿수의 합)
O X X O O(소수인지 아닌지)
12 20 30( 살아남은 수)
이제 3개중에서 GCD 최댓값 구하면 된다.
그냥은 못구한다.
그냥 구하면 nC2인데 n(n-1)/2로 계산되므로 시간복잡도가 너무 커진다.
그러므로 nC2를 계산하는 식으로는 못구한다.
탐색범위는 현재 nC2이다. 탐색범위가 너무 크기 때문에 구할 수 없는 것이다.
문제를 해결하기 위해서는 문제의 특성을 파악해야 한다.
내가 구해야 하는 건 N개중에 2개를 택한 모든 것중에 가장 큰 GCD값이다.
탐색공간의 원소들은 12와 13의 GCD, 12와 15의 GCD, ... 이렇게 나올 것이다.
탐색공간이 너무 클 때 생각해볼 수 있는 것중에 하나는 무엇이냐면
탐색공간의 크기를 줄이는 것이다. 크기를 줄이기 위해서는 탐색공간의 특성을 파악해야한다.
탐색공간의 모든 원소의 value는 반드시 30이하인 것을 파악할 수 있다.
그렇다면 파라메트릭 서치를 이용하여 탐색공간을 1~30으로 줄일 수 있다.
파라메트릭 서치는 탐색공간의 크기가 거대할 때 문제를 결정 문제로 바꾸어 탐색공간의 크기를 줄이는 방법이다.
이 문제에서는 1이 정답(최대 GCD 값)인가요? ~ 30이 정답인가요? 라고 결정문제로 바꿀 수 있다.
각 자릿수 합을 구한다. 소수인것 필터링한다. 모은거중에서 GCD 최대값을 구해.
12 20 30의 GCD를 구해보자. 10^4개야 이것들 싸그리 다 OX 밝혀내면 10^4걸린다.
자릿수의 합을 어떻게 구할까?
N=54234라고 하자.
각 자리수의 합을 구하려면 이를 문자열로 변환하면 된다.
그리고 하나씩 꺼내서 sum 구하면 된다. for(char : string)쓰면 될 것이다.
그리고 파라메트릭서치가 마지막에 사용 된다.
시간복잡도 (2)
마지막에 파라메트릭 서치를 사용하여 최대 GCD값이 1인 경우 ~ 최대 GCD값이 max_value인 경우로
탐색공간의 범위를 좁힌 다음, 각 케이스마다 직접 GCD를 구하려고 했었다.
예를 들어 12 20 30의 GCD를 구하는 것인데 각 케이스는 1~30이다.
30이 12 20 30의 GCD인가? NO. 29가 ~~인가? NO  ....
10이 12 20 30의 GCD인가? YES.
이런식으로 로직을 돌리려고 하였다.
하지만, 공부를 하다보니 12와 20과 30의 약수를 모두 구한다음
1~30케이스의 빈도수를 구하여 30부터 반복문을 돌려 빈도수 값이 2이상인 것을 리턴하면 된다는 것을 알았다.
이 방법이 직관적으로 봐도 더 빠르게 보였고,
gcd함수를 사용하여 각 케이스마다 GCD인지 확인하는 것은 내부적으로 약수를 구하는 과정을 거치기에
중복되는 연산이 훨씬 더 많을 것이라고 이해했다.

이 코드에 대해서 시간복잡도를 계산해보면
calc연산을 N번 반복하므로 이때까지의 전체 시간복잡도는 O(N)이고,
최대값을 구하는 과정도 최악의 경우에 N개를 순회하니 전체 시간복잡도가 O(N)이다.
그리고 약수의 빈도수를 구하는 과정에서는 data의 가능한 최댓값은 N이고,
루프는 최대 sqrt(N)번 수행된다.
총 시간복잡도는 O(N * sqrt(N))이다.
*/

bool isPrime(int num) {
    //17을 하려면 반복문은 2 ~ sqrt(17)까지만 해.
    // i로 나눠봐 나눠지면 false 나눠지지 않으면 true
    if (num <= 1) return false;
    for (int i = 2; i <= sqrt(num); ++i) {
        if (num % i == 0) {//i로 나누어 떨어지면 false
            return false;
        }
    }
    return true;
}

vector<int> stuffsThatseatNumSumIsPrime;

void calc(int N) {
    string N_str = to_string(N);
    int sum = 0;
    for(char N : N_str) {
        int num = N - '0';
        sum += num;
    }
    // cout << "sum 값 :: " << sum << "isPrime(sum) :: " << isPrime(sum) << endl;
    if(isPrime(sum)) stuffsThatseatNumSumIsPrime.push_back(N);
}



int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N;
    cin >> N;
    vector<int> A(N);

    for (int i = 0; i < N; i++) {
        cin >> A[i];
        calc(A[i]);
    }
    //12 20 30이 왔어요. 그러면 먼저 max값을 찾아야 해.
    //이제 1부터 max 배열을 만들어.
    //1이 GCD최대값일까? 30이 GCD 최댓값일까?
    //1은 12 20 30의 공약수일까? 30는 12 20 30의 공약수일까?
    //12의 약수는 1 12 / 2 6 / 3 4 >>> 1 2 3 4 6 12 야.
    //20의 약수 1 20 / 2 10 / 4 5 >>> 1 2 4 5 10 20
    //30의 약수 1 30 / 2 15 / 3 10 / 5 6 .>>> 1 2 3 5 6 10 15 30
    //0~30으 빈도수 배열에 빈도수 값을 넣어서 해결할 ㅜㅅ 이
    //+1

    // 자릿수 합이 소수인 숫자가 2개 미만이면 -1 출력
    if (stuffsThatseatNumSumIsPrime.size() < 2) {
        cout << -1 << endl;
        return 0;
    }

    int max_value = -999999;
    for (int data : stuffsThatseatNumSumIsPrime) {
        max_value = max(data, max_value);
    }

    vector<int> freq(max_value + 1);

    for (int data : stuffsThatseatNumSumIsPrime) {
        //data = 36이라고 해바
        for (int j = 1; j*j <= data; j++) {
            //j = 6이래 그러면 36을 6으로 나눈 나머지가 0이므로 6은 약수야.
            //30 > 1 30 / 2 15 / 3 10 / 5 6
            //20 > 1 20 / 2 10 / 4 5
            //j = 4래. 그러면 4와 9가 약수잖아. 약수를 빈도수 배열에 싹다 넣어.
            if (data % j == 0) {
                // cout << "data" << data  << "j" << j << endl;
                freq[j]++;
                if ( data / j != j) {// 6 6이 아니면.....if문 실행. 4와 9 각각 플러스 하는겅미.
                    freq[data / j]++;
                }
            }
        }
    }
    // for (int data : freq) {
    //     cout << i <<"data" << data << endl;
    //     i++;
    // }
    // 빈도수 배열이 꽉 찻어. 1 2 3 4 5 6 7각각에 대해서 빈도수 결정낫어.
    // 그러면
    // 빈도수배열에 끝에부터 반복문 돌리면 대
    int sol = -1;
    for (int i = static_cast<int>(freq.size()) - 1; i >= 1; i--) {
        if (freq[i] >= 2) {
            sol = i;
            break;
        }
    }

    cout << sol;

    return 0;
}