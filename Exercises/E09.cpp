#include<iostream>
#include<vector>
#include<cstring> // Necessário para memset
#include<algorithm> // Necessário para max
using namespace std;
const int MAXN = 5*1e3 + 10;

int quantidadeDias;
int diamantesIniciais;

vector<int> diamantes(MAXN);
// dp[dia][temTicket]
// Armazena o lucro máximo partindo do 'dia' com status 'temTicket'
int max_lucro[MAXN][2];

int dp(int dia, bool temTicket, bool trabalho)
{
  // Caso Base: Se já passamos do último dia, não há mais lucro a obter.
  if(dia > quantidadeDias) return 0;

  // Caso 1: Descanso Obrigatório
  if(trabalho) return dp(dia + 1, temTicket, 0);
  

  // Caso 2: Dia de Decisão
  if(max_lucro[dia][temTicket] != -1) {
    return max_lucro[dia][temTicket];
  }

  // Se não foi calculado, calculamos agora.
  int ans;

  if(temTicket)
  {
    // Sub-caso: O jogador TEM um ticket
    // Opção A: Garimpar
    // Ganha diamentes, perde o ticket e deve descansar amanhã
    int profit_garimpar = diamantes[dia] + dp(dia + 1, 0, 1);
    // Opção B: 
    // Sem ganho, mantém o ticket e sem descanso amanhã
    int profit_pular = 0 + dp(dia + 1, 1, 0);
    // A resposta é o máximo entre as opções.
    ans = max(profit_garimpar, profit_pular);
  }
  else // !temTicket
  {
    // Sub-caso: O jogador NÃO TEM um ticket
    // Opção A: Comprar
    // Paga o custo 'diamantes[dia]'(ganha o ticket) e não descansa amanhã
    int profit_comprar = -diamantes[dia] + dp(dia + 1, 1, 0);

    // Opção B: Pular
    // Sem ganho, continua sem ticket e não descansa amanhã
    int profit_pular = 0 + dp(dia + 1, 0, 0);

    // A resposta é o máximo entre as opções.
    ans = max(profit_comprar, profit_pular);
  }

  // Armazena o resultado calculado na tabela de memoização e o retorna.
  max_lucro[dia][temTicket] = ans;
  return ans;
}

int main(void)
{
  int fase; cin >> fase; 

  while(fase--)
  {
    cin >> diamantesIniciais;   
    cin >> quantidadeDias;     

    // Leitura dos N valores (custo/ganho) para os dias 1 até N 
    for(int i = 1; i <= quantidadeDias; i++)
    {
      cin >> diamantes[i];
    }

    // Estado -1 significa não calculado
    memset(max_lucro, -1, sizeof(max_lucro));

    // Chama a função DP para calcular o lucro/prejuízo máximo
    int ans = dp(1, 0, 0);

    // A resposta final é a quantidade inicial + o lucro/prejuízo calculado 
    cout << (diamantesIniciais + ans) << endl;
  }
  return 0;
}