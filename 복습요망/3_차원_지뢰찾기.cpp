#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int r, c, h;
    cin >> r >> c >> h;
    // 가로 : x, y, z 좌표로 보는거야. 그러면... 모든 점의 좌표를 저장할 수 있겠지.
    vector<vector<vector<char>>> d(h, vector<vector<char>>(r, vector<char>(c)));
    // cout << (int)'.' << "\n";//46
    // cout << (int)'*' << "\n";//42
    for (int i = 0; i < h; i++)
    {                               // 높이
        for (int j = 0; j < r; j++) // 세로
        {
            for (int k = 0; k < c; k++) // 가로
            {
                char a;
                cin >> a;
                d[i][j][k] = a;
            }
        }
    }

    // d가 잘 받아졌는지 확인했음.
    
    int dx[26] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1};
    int dy[26] = {-1,-1,-1,0,0,0,1,1,1,-1,-1,-1,0,0,1,1,1,-1,-1,-1,0,0,0,1,1,1};
    int dz[26] = {-1,0,1,-1,0,1,-1,0,1,-1,0,1,-1,1,-1,0,1,-1,0,1,-1,0,1,-1,0,1};
    int i=0;
    int j=0;
    int k=0;

    for (vector<vector<char>> ell : d)
    {
        for (vector<char> el : ell)
        {
            for (char e : el)
            {
                if (e == '.')
                {
                    //26번검증
                    int cnt = 0;
                    for (int l = 0; l < 26; l++) {
                        if ((i+dz[l]) >= 0 && i+dz[l] <= h-1 &&
                        (j+dy[l]) >= 0 && j+dy[l] <= r-1 &&
                        (k+dx[l]) >= 0 && k+dx[l] <= c-1 &&
                         d[i+dz[l]][j+dy[l]][k+dx[l]] == '*') cnt++;
                    }
                    cout << (cnt%10);

                }
                else if (e == '*')
                {
                    cout << e;
                }
                k++;
            }
            cout << "\n";
            k=0;
            j++;
        }
        j=0;
        i++;
    }
}