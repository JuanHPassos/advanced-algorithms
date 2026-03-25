#include<iostream>
#include<vector>
using namespace std;

typedef long long ll;
typedef vector<long long> vll;
typedef vector<vector<int>> vvi;


// Varre a linha da direita para esquerda
vll caminha_direita(int m, int i, vector<vll>& dp, const vvi& grade)
{
    vll dp_direita (m, -1);
    // Inicializa em caso i = 0;
    dp_direita[0] = dp[i][0];

    for(int j = 0; j < m; j++)
    {
        ll maior = -1;
        // Caso em que é impossível chegar na pos (i, j)
        if (grade[i][j] == -1) maior = -1;
        // Caso contrário, pego o melhor caminho.
        else
        { 
            // Se houver caminho vindo de cima
            if (i - 1 >= 0 && dp[i - 1][j] != -1)
                maior = max(maior, dp[i - 1][j] + grade[i][j]);
            
            // Se houver caminho que vem da esquerda
            if (j - 1 >= 0 && dp_direita[j - 1] != -1)
                maior = max(maior, dp_direita[j - 1] + grade[i][j]);
        }
        
        dp_direita[j] = max(maior, dp[i][j]);
    }

    return dp_direita;
}

// Varre a linha da direita para esquerda.
vll caminha_esquerda(int m, int i, vector<vll>& dp, const vvi& grade)
{
    vll dp_esquerda (m, -1);
    // Inicializa em caso i = 0;
    dp_esquerda[0] = dp[i][0];

    for(int j = m - 1; j >= 0; j--)
    {
        ll maior = -1;
        // Caso em que é impossível chegar na pos (i, j)
        if (grade[i][j] == -1) maior = -1;
        // Caso contrário, pego o melhor caminho.
        else
        { 
            // Se houver caminho vindo de cima
            if (i - 1 >= 0 && dp[i - 1][j] != -1)
                maior = max(maior, dp[i - 1][j] + grade[i][j]);
            
            // Se houver caminho que vem da esquerda
            if (j + 1 < m && dp_esquerda[j + 1] != -1)
                maior = max(maior, dp_esquerda[j + 1] + grade[i][j]);
        }
        
        dp_esquerda[j] = max(maior, dp[i][j]);
    }

    return dp_esquerda;
}

int main(void)
{
    int n, m; cin >> n >> m;
    vvi grade (n, vector<int> (m));
    
    // Ler entrada
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            cin >> grade[i][j];

    // Estado é a quantidade de pastilhas
    vector<vll> dp(n, vll (m, -1));
    vll dp_aux(m, -1);

    // Iniciar trajeto em (0, 0)
    dp[0][0] = grade[0][0];
    
    // O(N)
    for(int i = 0; i < n; i++)
    {
        // O melhor caminho é(dado que não visita grade visitada):
        // Descer pela esquerda e varrer a linha (->);
        // Descer pela direita e varrer a linha (<-).

        // O(3*M)
        vll dp_esquerda = caminha_esquerda(m, i, dp, grade);
        vll dp_direita = caminha_direita(m, i, dp, grade);
        for(int j = 0; j < m; j++)
        {
            dp[i][j] = max(dp_esquerda[j], dp_direita[j]);
        }
    }

    /*
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
            cout << dp[i][j] << " ";
    
        cout << endl;
    }
    */
        
    cout << dp[n - 1][m - 1];

    return 0;
}