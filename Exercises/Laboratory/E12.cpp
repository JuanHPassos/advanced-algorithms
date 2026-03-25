#include<iostream>
using namespace std;

const int MOD = 1e9 + 7;

int main(void)
{
    int n; cin >> n;
    string s[n];
    // Deixar margem para facilitar checagem
    int dp[n + 1][n + 1];
    
    for(int i = 0; i < n; i++) cin >> s[i];

    // Inicializar matriz
    for(int i = 0; i <= n; i++)
        for(int j = 0; j <= n; j++)
            dp[i][j] = 0;

    // Forma de inicializar a posição
    dp[1][1] = (s[0][0] == '*' ? 0 : 1);
    
    // Checar possíveis caminhos
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            if(s[i - 1][j - 1] == '*') continue;
            else
            {
                // O estado i j é foramdo pelo o que ta vindo das duas direções possíveis
                if(dp[i - 1][j] != 0) dp[i][j] = (dp[i][j] + dp[i - 1][j])%MOD;
                if(dp[i][j - 1] != 0) dp[i][j] = (dp[i][j] + dp[i][j - 1])%MOD;
            }
        }
    }

    cout << dp[n][n];

    return 0;
}