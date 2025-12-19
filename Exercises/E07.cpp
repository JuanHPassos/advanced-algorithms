#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;
const ll INF = 1e18;

int main(void)
{
  int numeroReliquias;
  cin >> numeroReliquias;

  vector<ll> estabilidade(numeroReliquias);
  for(ll &s_i : estabilidade) cin >> s_i;
  
  // Estado 0(quebrado na raça) e 1(tomou dano de queda).
  ll custo[2][numeroReliquias];
  custo[0][0] = estabilidade[0]; 
  custo[1][0] = INF;
  for(int i = 1; i < numeroReliquias; i++)
  {
    // Caso em que o cara é quebrado sem dano de queda.
    custo[0][i] = estabilidade[i] + min(custo[0][i - 1], custo[1][i - 1]);
    // Se houver dano de queda
    // O cara quebrado antes sofreu dano de queda(toma 1 de dano)
    // Caso contrario, o cara atual vai tomar a dano da sua altura original.
    ll estabilidadeRestante = max(estabilidade[i] - i, 0LL);
    custo[1][i] = min(custo[0][i - 1] + estabilidadeRestante,
                      custo[1][i - 1] + (estabilidade[i] - 1));
  }

  cout << min(custo[0][numeroReliquias - 1], custo[1][numeroReliquias - 1]);

  return 0;
}
