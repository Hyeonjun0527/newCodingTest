#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n;
    cin >> n;

    int use = 0;
    int cp = 0;

    int cum = 0;

    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;

        // 다르면이야
        if (cp != a)
        {
            if (cum + 2 >= 100)
            {
                use = 0;
                cum = 0;
            }
            else
            {
                use += 2;
            }
            cp = a;
        }
        else
        { // 같으면이야

            if (use == 0)
            {
                use = 2;
            }
            else
            {
                if (cum + use*2 >= 100)
                {
                    use = 0;
                    cum = 0;
                }
                else
                {
                    use *= 2;
                }
            }
        }
        cum += use;
        // cout << use << "현재사용량" << "\n";
        // cout << cum << "누적사용량" << "\n";
        // cout << "\n";
    }

    cout << use;
}