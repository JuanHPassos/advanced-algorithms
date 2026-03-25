#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e5;

int main(void)
{
    int t; cin >> t;
    while(t--)
    {
        int n, m; cin >> n >> m;
        string s[n];
        for(auto &u : s) cin >> u;

        // Bastar formar um retangulo entre o
        // primeiro e ultimo b.
        int x_min = MAXN;
        int y_min = MAXN;
        int x_max = -1;
        int y_max = -1;

        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
            {
                if(s[i][j] == 'B')
                {
                    x_min = min(x_min, j);
                    y_min = min(y_min, i);
                    x_max = max(x_max, j);
                    y_max = max(y_max, i);
                }
            }
        }
        /*
        cout << x_min << endl;
        cout << x_max << endl;
        cout << y_min << endl;
        cout << y_max << endl;
        */

        if (x_min == MAXN) cout << "0 0" << endl;
        else
        {
            cout << (n - y_min) << " ";
            cout << (x_max - x_min) + 1 << endl;
        }
    }

    return 0;
}