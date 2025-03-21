#include <iostream>     // 표준 입출력 사용을 위한 헤더
#include <vector>       // vector 자료구조 사용을 위한 헤더
#include <algorithm>    // fill 함수 사용을 위한 헤더
#include <cmath>
using namespace std;
/*
//2^2 3^2 4^2 로 나누어 떨어지지 않는 수 제곱 ㄴㄴ수
//1 2 3 [4] 5 6 7 [8] [9] 10
//pow(10,6)을 n번 반복은 괜찮아. now라고 하자. now % x^2 != 0 인 것들이 답이잖아.
/*
저 식에서 x를 어떻게 구하지..? 반복문이야. min~max사이 수들 중에서

501,1000이라면..?
start는 501부터 일까?
4로 나누는 거라면......  504부터겠지.(4,9,16 이런걸로 나눠봐야하니 4부터 나눠보는거임)
500,1000이라면...?
start는 500부터 겠지?
4로 나누는 거라면..... 500부터겠지.
이걸 어떻게 일반화할까? 나누어 떨어질 때 vs 나누어 떨어지지 않을때 나누면 되지 머.
(min,max)
만약에 min=27이면 9로 나눠떨어지는거니까. 4,9,16이런거로 나눠봐야겠다.

504 508 512 516 이렇게 안될거야. power = 4 start = 504 max = 1000
근데 테이블에 저장할건데 어떻게 저장할까? table은 min~max까지를 저장해야되지?
table은 그럼 0~max-min+1를 저장하면 되겠다. 원래보다 -min을 했지?
언제나 저장할때도 -min 하면 돼. 꺼내서 출력할땐 +min 하면 되고
조정을 -min 했으면 저장하기전에 똑같이 -min 해주고, 출력할 땐 +min 해주면 돼.
그게싫으면 그냥 min ~ max저장해도 되기는 해.
*/
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    long long min, max;
    cin >> min >> max;


    // vector<bool> table(max - min + 1, true);
    vector<bool> table(max - min + 1, true);// (min부터 max+1) 조정 -min
    //삽입, 수정, 삭제, 조회시 -min, 복원 시 +min
    // fill(table.begin(), table.end(), true);

    //머 해야 하냐면 start~end사이에 제곱ㄴㄴ수가 아닌걸 전부 지우면 제곱 ㄴㄴ수만 남겠지
    //그러니 전부 지우는 작업을 해야해.
    //2제곱부터 포우까지 4 9 16 25 36 49 64 81 100 ... <= max 반복해야지.
    //start 27이라면 28부터 4의 배수 싹 지우고,
    //27부터 9의 배수 싹 지우고, 32부터 16의 배수 싹 지우고...
    //start 501이라면 504부터 4의 배수 싹 지우고, 504부터 9의 배수 싹 지우고....

    //뭘 이용한거냐. 9, 18, 27, 36 이런걸 이용한거야. 9의 배수에 9를 더했을때 여전히 9의 배수임을 이용한거임.
    for (long long number = 2, power = 4;
        power <= max;
        number++, power = number * number) {
        long long start;
        //나누어 떨어진다면( min = 500 이면 start = 500)
        //나누어 떨어지지 않는다면( min = 501 이면 start = 504)
        if (min % power == 0) start = min;
        else start = min / power * power + power;//501 / 4 * 4 + 4

        // long long start = min / power * power;
        // //시작을 조정함
        // if (min % power != 0) {
        //     start += power;
        // }

        //테이블에 반영해야지 코드
        for (long long now = start;
            now <= max;
            now += power) table[now - min] = false;
        //false는 살아남지 못한거야. 27못살아남지. 27+9, 27+9+9 , .... 다 못살아남아.
        //now - min은 조정
    }
    int count = 0;
    for (bool isSolution : table) if (isSolution) count++;
    cout << count << '\n';
}


/*
에라토스테네스의 체
문제를 보고 힌트가 뭘 지 추측해야돼
1. 제곱수의 배수를 찾으려고 하는거야!!! 제외하려는거야!!! 여기까지가 핵심 그 다음엔?
2. min에 가장 가까운 제곱수의 배수를 계산해. 거기서 start하자.
그건 머냐면 start = min / power * power
나누어떨어지지 않으면 start += power
3. 제곱수 배수는 일정한 간격으로 존재해.
4. iteration은 max까지 하면 되겠네 index로는 root(MAX)
5. 제곱수의 배수만 찾으면 되니까
그리고 그 배수부터 max까지 제곱수의 배수를 찾아서 false로 바꾼다.
*/
