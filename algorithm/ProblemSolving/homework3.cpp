
/*

(1) 구현 방식
케이블 타이, 막대사탕
문제를 보자마자 파라메트릭 서치가 떠오를 수 밖에 없다.
목재양을 만족하는 최대 높이를 출력해야 한다.
1~10^6의 높이중에 목재양을 만족하는 최대높이를 출력해야한다. 만약 이걸 전부 구하고 순진하게 max함수로
답을 구하려면 반드시 시간초과가 난다.
최대 높이를 이진탐색으로 확인해야 한다.
목재양을 만족하는 최대 높이를 찾는 이 최적화 문제를 결정 문제로 변환하면
주어진 H가 목재양을 만족하는지? 이다.

(2) 시간 복잡도
이진탐색을 수행하므로 O(log(maxHeight))를 각 케이스 마다 수행한다.
즉 O(N*log(maxHeight))가 된다.
*/
#include <iostream>
#include <vector>
#include <climits>

using namespace std;
//N,trH,heightToCut,myM
void cuttingTree(int N, vector<int> trH, int heightToCut, int& myM);

int main() {
    int N,M;//나무개수, 잘라서 남는 목재의 양 윗부분 자름
    //M = A[i]나무높이 - H의 합
    cin >> N >> M;// 4 7 이렇게 들어가
    vector<int> trH(N);

    int given = 0;
    int maxHeight = -1000;
    for (int i = 0; i < N; i++) {
        cin >> given;//20 15 10 17 이렇게 들어가
        maxHeight = max(maxHeight,given);
        trH[i] = given;
    }
    //일단 맥스 값 구해.



    int start = 0, end = maxHeight;
    int heightToCut = 0;
    while (start <= end) {
        int mid = (start + end) / 2;
        int myM = 0;

        cuttingTree(N, trH, mid, myM);

        if (myM >= M) {//너무 조금 잘랐어? 아니면 M만큼 잘 잘랐어? 그러면 heightToCut 목표 높이 저장하고 더 잘라.
            //왜 더 자르냐? 왜냐면 더 잘자르는 방법이 있을 수도 있거든
            heightToCut = mid;
            start = mid + 1;
        } else {// 너무 많이 잘랐어. 자를 높이를 줄여야해.
            end = mid - 1;
        }
    }

    cout << heightToCut << endl;//나무를 자르고 나서 얻는 최대 목재 양이라기보다는 M을 만족하며 자르는 높이를 출력.
    return 0;
}
void cuttingTree(int N, vector<int> trH, int heightToCut, int& myM) {
    for (int i = 0; i < N; i++){
        if ( trH[i] <= heightToCut) {
            // 안자른다??라는 건 myM에 더해지는게 없다
        } else {
            myM += trH[i] - heightToCut;
            // 자른다.라는건 myM에 더해진다. 쌓인다.
        }
    }
}