/* 
Ford-Fulkerson usando scaling algorithm para escolher caminhos
Com Grafo Residual
*/

#include<iostream>
#include<vector>
#include<cstring>
#include<cmath> // log2 e floor
#define max(a, b) ((a) > (b) ? (a) : (b))

using namespace std;
const int MAXN = 500 + 10;
const long long INF = 1e18; 

typedef long long ll;

// Estrutura para armazenar arestas e suas reversas
struct Aresta
{
  int destino;
  ll capacidade;
  // Indice da aresta reversa
  int aresta_reversa; 
};

int n, m;
ll C = 0;
vector<vector<Aresta>> adj(MAXN);
vector<int> vis(MAXN);

// DFS agora procura por caminhos com capacidade >= 'C_atual'
ll dfs(int u, ll fluxo, ll C_atual) 
{
  if (vis[u]) return 0;
  vis[u] = 1;

  // Encontrado sumidouro (nó 'n')
  if (u == n) return fluxo; 

  for (auto& a : adj[u]) 
  {  
    if (a.capacidade >= C_atual && !vis[a.destino]) 
    {    
      ll novoFluxo = min(fluxo, a.capacidade);
      ll voltaFluxo = dfs(a.destino, novoFluxo, C_atual);

      if (voltaFluxo > 0) 
      {
        // Diminui a capacidade da aresta direta
        a.capacidade -= voltaFluxo;

        // Aumenta a capacidade da aresta residual (reversa)
        adj[a.destino][a.aresta_reversa].capacidade += voltaFluxo;

        return voltaFluxo;
      }
    } 
  }

  return 0; // Nenhum caminho encontrado.
}

int main(void)
{
  cin >> n >> m;
  
  for(int i = 0; i < m; i++)
  {
    int a, b;
    ll c; // Capacidade pode ser grande
    cin >> a >> b >> c;
    C = max(C, c); // Encontra a capacidade máxima

    // Adiciona a aresta direta (a -> b) e a residual (b -> a)
    int rev_a = adj[b].size();
    int rev_b = adj[a].size();

    adj[a].push_back({b, c, rev_a});
    adj[b].push_back({a, 0, rev_b}); // Residual começa com 0
  }

  ll fluxoMaximo = 0;

  // delta = maior pot 2 menor que C
  ll delta = 1LL << 62; 
  while (delta > C) delta >>= 1;

  while(delta > 0)
  {
    // Continue encontrando caminhos >= delta
    while(true) 
    {
      // Inicia nova busca (reseta vetor de visitados)
      for(int i = 0; i <= n; i++) vis[i] = 0;

      ll fluxoEncontrado = dfs(1, INF, delta); 
      
      // Não há caminhos.
      if (fluxoEncontrado == 0) break;
      
      // Acumula o fluxo total
      fluxoMaximo += fluxoEncontrado;
    }
    
    // Esgotado os caminhos >= delta,
    // tentamos com uma escala menor.
    delta /= 2;
  }
  
  cout << fluxoMaximo;

  return 0;
}