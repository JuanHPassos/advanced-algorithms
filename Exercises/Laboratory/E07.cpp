#include<iostream>
#include<queue>
using namespace std;

int main(void)
{
  // Ler entrada das tarefas
  int n; cin >> n;
  priority_queue<pair<int, int>> pq; 
  for(int i = 0; i < n; i++)
  {
    // Ordenar as tarefas por duracao
    int dias, prazo; cin >> dias >> prazo;
    pq.push({-dias, -prazo});
  }

  // Tarefas que acabam primeiro 
  // geram menores tempos de finalização
  long long dias = 0;
  long long ans = 0;
  for(int i = 0; i < n; i++)
  {
    int duracao = -pq.top().first;
    int prazo = -pq.top().second;
    pq.pop();
    // Pontuação atual é os pontos iniciais d_i = d - f
    // menos a quantidade de dias que se passaram.
    ans += (prazo - duracao) - dias;
    dias += duracao;
  }
  
  cout << ans;

  return 0;
}