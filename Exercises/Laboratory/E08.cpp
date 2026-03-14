#include<iostream>
#include<vector>
using namespace std;

const int INF = 1000 + 5;

int main(void)
{
    int t; cin >> t;
    while(t--)
    {
        int v; cin >> v;
        int m; cin >> m; 
        vector<int> moedas(m);
        // Transição = valor. dp[valor] = 
        // numero min de moedas para valor
        int dp[v + 1];
        dp[0] = 0;

        for(int i = 0; i < m; i++) cin >> moedas[i];
        
        for(int i = 1; i <= v; i++)
        {
            int menor = INF;
            for(auto moeda : moedas)
            {
                if(i - moeda < 0) break;
                else menor = min(menor, dp[i - moeda]);
            }
            if(menor != INF) dp[i] = menor + 1;
        }
        cout << dp[v] << endl;
    }

    return 0;
}