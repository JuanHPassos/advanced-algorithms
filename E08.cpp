#include <iostream>
#include <vector>
#include <map>
#include <tuple>
using namespace std;

// Estrutura para representar uma peça de dominó
struct Peca 
{
    int a, b;
    int valor() { return a + b; }
};

// Mapa para memoização: (esquerda, direita, turno) -> pontuação de Maria
map<tuple<int, int, int>, int> memo;
vector<Peca> pecas;

/*
Maria deve maximizar sua escolha, logo maria além de pegar
a peça, verifica se isso gera um mais pontos futuramente.
Joao buscara minimizar jogada de maria, para isso ele pode
verificar se no futuro, sua jogada vai gerar maria pegar
peças com menor valor.
*/
int dp(int esq, int dir, bool turno_maria) 
{
    if (esq > dir) return 0;

    auto chave = make_tuple(esq, dir, turno_maria ? 1 : 0);
    if (memo.find(chave) != memo.end()) return memo[chave];

    int resultado;
    if (turno_maria) 
    {
      // Busca maximar pontuação verificando o futuro.
      int pegar_esq = pecas[esq].valor() + dp(esq + 1, dir, false);
      int pegar_dir = pecas[dir].valor() + dp(esq, dir - 1, false);
      resultado = max(pegar_esq, pegar_dir);
    } 
    else 
    {
      // Busca o minimo da pont. de maria.
      int pegar_esq = dp(esq + 1, dir, true);
      int pegar_dir = dp(esq, dir - 1, true);
      resultado = min(pegar_esq, pegar_dir);
    }

    memo[chave] = resultado;
    return resultado;
}

int main() 
{
  int X; 
  cin >> X;

  for (int caso = 0; caso < X; caso++) 
  {
    int N;
    cin >> N;

    // Resetar estruturas para novo teste.
    pecas.clear();
    memo.clear();
    pecas.resize(N);

    // Ler entrada do problema.
    for (int i = 0; i < N; i++) 
    {
      char lparen, comma, rparen;
      cin >> lparen >> pecas[i].a >> comma >> pecas[i].b >> rparen;
    }

    // Imprimir resultado.
    int pontuacao_maxima = dp(0, N - 1, true);
    cout << pontuacao_maxima << endl;
  }

  return 0;
}
