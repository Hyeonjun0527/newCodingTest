
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    //A~B
    //A~루트B까지의 소수를 구해.
    //소수의 제곱을 구해서 그것이 B보다 작은지 확인하면 답나와.
    //2,4,8,16,32,64....다 거의 소수야.

    //1~10^7까지니까 SolArr사이즈는 10^7+1이 되어야해.
    long long min, max;
    cin >> min >> max;
    // vector<long> arr(B_2 - A + 2);//1,2,3,4,5....remain
    // constexpr int MAX_LIMIT = 10'000'000;
    // constexpr int SIZE = MAX_LIMIT + 1; // 이거 필요가 없음

    long rootMax = static_cast<long>(sqrt(max));
    vector<long> A(rootMax + 1);//1,2,3,4,5....remain
    // vector<int> PrimePow()
    //초기화 어차피 i=0,1일때는 0이야. 그러므로 2부터
    for (int i = 2; i <= rootMax; ++i) {
        A[i] = i;
    }

    //2,3,4,5,...로 All을 싹 돌려볼거야. 배수를 거를거야. 그렇게 소수를 구할거야.
    // i=2라면 그 All배열을
    //왜 j = i*2부터냐면 2의 배수를 제거해야되지 근데 2는 소수야
    //그러니 i인것 즉, 2인것은 제거하면 안돼.
    //왜 < 아니라 <=지 이유없음
    //sqrt는 마지막 원소에 하면 돼.
    //왜 MAX_LIMIT이라고 물어본다면 원래는 10^14자나.
    //일단 먼저 최대범위에 있는 모든 소수를 구하고 ,A B안에 소수의 제곱이 잇는지 확인할거야.
    // 왜 전체구간이야? 입력값 1~2여도 1~10^7을 모두 계산해서 Arr에 소수를 밝혀냈자나. 이거 비효율적인데?
    //맞아 비효율적이지. 만약에 입력된 Max값를 한정으로 정하고 소수를 밝혀내면 더 좋을거같아.
    //그리고 거의 소수를 구하려면 2,3,4....,10^7의 제곱들을 전부 바라보는데 루트max까지만
    for(int i = 2; i <= sqrt(rootMax); i++) {
        if (A[i] == 0) continue;

        for (int j = i*2; j <= rootMax; j += i) {//2 2x3 2x4 2x5다 걸러.
            A[j] = 0;
        }
    }
    // cout << "A : " << A << " B : " << B << "\n";
    // for (int i = 0; i < arr.size(); ++i) {
    //     cout << arr[i] << ", ";
    // }
    //2,4,8,16,32,64....다 거의 소수야 이거의 개수 출력하는거야.
    //0이면 배수야.
    //각각의 소수에 관해, 소수를 N제곱한 값이 B보다 커질때까지 반복한다.
    //All의 요소를 반복하는데 소수면(0이아니면) 그 소수의 제곱부터 시작해서 N제곱한 값이 B보다 작을때까지 반복한다.
    //그때마다 카운트를 증가시킨다.
    // 소수의 거듭제곱이 주어진 범위 내에 있는지 확인
    // 소수야. 소수야 근데 소수의 제곱이 Max보다
    // 2야 2야 근데 2의 제곱(4)이 Max보다 작아?
    // 그럼 2의 세제곱이 Max보다 작아? 그럼 2의 세제곱이 Max보다 작아?
    //소수까지 살아남겼어. 이제 소수를 죽이고 거의소수만 살려도 되고, 거의소수만 count++해도되고,
    //count하는 선택이 더 쉬워보임. 소수를 만났어. 그럼,
    int count = 0;
    for (int i = 2; i <= rootMax; i++) {
        if (A[i] != 0) {  // 소수인 경우
            // temp=4,8,16,32, 64가 된다. 0이 아니니까 arr[i]와 i는 완전히 같은 값이야 여기서.
            // 소수의 거듭제곱 계산
            //temp = 2^2 2^3 2^4 2^5 2^6
            for (long long temp = i; (double)temp <= (double)max / i; temp *= i) {
                if ((double)temp >= (double)min / (double)i) {
                    count++;
                }
            }

        }
    }

    cout << count << "\n";

}
