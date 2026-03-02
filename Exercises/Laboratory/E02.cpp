#include<iostream>
using namespace std;

int main(void)
{
    int t; cin >> t;
    while(t--)
    {
        int x, y;
        cin >> x >> y;
        // Distribuo as moedas de 2
        y = y%2;
        
        // Tento compensar com moeda de 1
        if(y == 1)
        {
            x -= 2;
            y = 0;
        }
        
        // Verifico se deu para compensar 
        if(x >= 0 && x%2 == 0) cout << "YES";
        else cout << "NO";
        cout << endl;
    }

    return 0;
}