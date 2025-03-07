#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int a[3][3];
int dx[] = {0, 1, 0, -1}; // 동남서북
int dy[] = {1, 0, -1, 0};

void dfs(int x, int y, int &cnt, bool (&visited)[3][3])
{
    //모든경우에적용가능한영역.return 없이 해결한다고 하면, 전체에 if문을 건 것과 마찬가지임.
    //모든 dfs 함수 호출 시에 필터링함.
    if (x < 0 || x > 2 || y < 0 || y > 2)
    {
        return;
    }
    if (visited[x][y])
    {
        return;
    }

    visited[x][y] = true;
    cnt++;

    for (int i = 0; i < 4; i++)
    {
        int nx = x + dx[i];
        int ny = y + dy[i];
        //다음 nx,ny에 적용하는영역, 호출을 할 지 말지 결정하는 영역.
        //호출 할 지 말지 결정할 때 필터링함.
        if (a[nx][ny] == 0 || a[nx][ny] == -1)
            continue;

        dfs(nx, ny, cnt, visited);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int t;
    cin >> t;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            a[i][j] = -2;
        }
    }
    // 1이면 O
    // 0이면 X
    //-1이면 가운데
    for (int q = 0; q < t; q++)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                char temp;
                cin >> temp;
                // cout << temp << " temp";
                if (temp == 'O')
                    a[i][j] = 1;
                else if (temp == 'X')
                    a[i][j] = 0;
                else
                    a[i][j] = -1;
            }
            // cout << "\n";
        }

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                // cout << a[i][j] << " ";
            }
            // cout << "\n";
        }
        // cout << "\n";

        cin.ignore();
        string ss;
        getline(cin, ss);
        vector<int> sol; // idx에 1더해서 출력
        bool visited[3][3] = {};
        int cnt = 0;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (!visited[i][j] && a[i][j] == 1)
                {
                    dfs(i, j, cnt, visited);
                    sol.push_back(cnt);
                    // cout << "cnt :: " << cnt << "\n";
                    cnt = 0;
                }
            }
        }
        // cout << "\n";

        sort(sol.begin(), sol.end());

        string sss = to_string(sol.size());
        for (int a : sol)
        {
            sss += " ";
            sss += to_string(a);
        }

        if (sss == ss)
        {
            cout << 1 << "\n";
        }
        else
        {
            cout << 0 << "\n";
        }

        // cout << "ss :: " << ss << " sss :: " << sss << "\n";
    }
}