#include<iostream>
#include<vector>
using namespace std;

int main(void)
{
    int n, m; cin >> n >> m;
    int grade[n][m];
    
    // Ler entrada
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            cin >> grade[i][j];

    // Estado é a quantidade de pastilhas
    vector<vector<long long>> dp(n, vector<long long> (m));

    // Se -1, não consigo chegar nessa pastilha
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            dp[i][j] = -1;

    // Iniciar trajeto em (0, 0)
    dp[0][0] = grade[0][0];
    
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            long long maior = -1;
            // Caso em que é impossível chegar na pos (i, j)
            if (grade[i][j] == -1) maior = -1;
            // Caso contrário, pego o melhor caminho.
            else
            { 
                // Se houver caminho vindo de cima
                if (i - 1 >= 0 && dp[i - 1][j] != -1)
                    maior = max(maior, dp[i - 1][j] + grade[i][j]);
                
                // Se houver caminho pela direita
                if (j - 1 >= 0 && dp[i][j - 1] != -1)
                    maior = max(maior, dp[i][j - 1] + grade[i][j]);
            }
            
            dp[i][j] = max(maior, dp[i][j]);
        }
    }

    // for(int i = 0; i < n; i++)
    // {
    //    for(int j = 0; j < m; j++)
    //        cout << dp[i][j] << " ";
    //
    //    cout << endl;
    // }
        
    cout << dp[n - 1][m - 1];

    return 0;
}