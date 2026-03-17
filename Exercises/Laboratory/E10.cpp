#include<bits/stdc++.h>
using namespace std;

int main(void)
{
    int n, x;
    cin >> n >> x;
    // Pegar mais paginas por menor preco.
    int precos[n];
    int nr_pags[n];
    for(int i = 0; i < n; i++) cin >> precos[i];
    for(int i = 0; i < n; i++) cin >> nr_pags[i];

    // A matrix(vector<vector<int>>) é inicializado com 0.
    // Solução ótima com 0 livros = 0 páginas.
    vector<vector<int>> dp(n + 1, vector<int> (x + 1, 0));
        
    // Verificar solução ótima com i livros.
    for(int i = 1; i <= n; i++)
    {
        // Verificar solução ótima com apenas j dinheiros.
        for(int j = 1; j <= x; j++)
        {
            // Caso em que não há dinheiros suficiente.
            if(j - precos[i - 1] < 0) dp[i][j] = dp[i - 1][j];
            // Devo pegar o livro i?
            // Se sim, guardo o valor dele + a solução ótima do troco.
            // Caso contrário, guardo a solução ótima de i - 1.
            else dp[i][j] = max(dp[i - 1][j - precos[i - 1]] + nr_pags[i - 1],
                                dp[i - 1][j]);
        }
    }

    /*
    for(int i = 0; i <= n; i++)
    {
        for(int j = 0; j <= x; j++)
        {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }
    */   

    cout << dp[n][x] << endl;

    return 0;
}