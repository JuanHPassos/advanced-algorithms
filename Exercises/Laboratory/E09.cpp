#include<iostream>
#include<vector>
#include<map>
using namespace std;

const int INF = 1000 + 5;

int main(void)
{
    int n; cin >> n;
    int gomo[n];

    for(auto &u : gomo) cin >> u;
    
    int dp[n + 1];
    //  Sem gomas, sem valor
    dp[0] = 0;

    //  Contruir a melhor combinação de gomas
    //  para o valor n.
    for(int i = 1; i <= n; i++)
    {
        int preco = -1;
        // Valor maximo da entrada é 100,
        // Sempre compensa valores menores ou iguais.
        for(int j = 1; j <= min(100, n); j++)
        {   
            if(i - j < 0) break;
            // Melhor escolha de goma possível
            else preco = max(preco, dp[i - j] + gomo[j - 1]);
        }
        dp[i] = preco;
    }

    cout << dp[n] << endl;

    return 0;
}