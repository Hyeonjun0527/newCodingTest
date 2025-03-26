#include <iostream>
#include <vector>
using namespace std;
int main() {
    //트레이드 AI
    //10개 색이 있는 도시 맵.
    //같은 색상의 도시는4개 존재함.
    //도시구매/현금 대출/도시현금 트레이드

    //플레이어는 현금과 도시를 제시해.
    //담보대출 도시 넘기면 대출도 넘어감

    //색상별로 가치 계산
    ///도시없는 색상은 0


    //트후자신 - 트후상대 >= 트전자신 - 트전상대
    int w[10][4];
    int a[10][4];//소유도시
    int b[10][4];//트레이드정보
    int c[10][4];
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 4; j++) {
            cin >> w[i][j];
        }
    }
    string k;
    cin >> k;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 4; j++) {
            a[i][j] = k[4*(i-1)+j];
        }
    }

    string t;
    cin >> t;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 4; j++) {
            b[i][j] = t[4*(i-1)+j];
        }
    }

    string t1;
    cin >> t1;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 4; j++) {
            c[i][j] = t1[4*(i-1)+j];
        }
    }

    int q,w;
    cin>>q>>w;//내현금 상대현금

}