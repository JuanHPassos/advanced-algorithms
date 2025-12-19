#include<iostream>
#include<vector>
#include<queue>
#include<unordered_map>

using namespace std;

const int MAXN = 5*1e4 + 10;

typedef pair<int,int> pii;

// --- Funções do Union-Find (DSU) ---
int find(int x, vector<int>& link) 
{
  while (x != link[x]) x = link[x];
  return x;
}

bool same(int a, int b, vector<int>& link)
{ 
  return find(a, link) == find(b, link);
}

void unite(int a, int b, vector<int>& link, vector<int>& size)
{
  a = find(a, link);
  b = find(b, link);
  if (size[a] < size[b]) swap(a,b);
  size[a] += size[b];
  link[b] = a;
}

// --- Função de Inicialização ---

// Otimizado: Recebe 'n' e inicializa apenas o necessário
void init(vector<int>& link, vector<int>& size, int n)
{
  // Assumindo que os nós são 1-based (de 1 até n)
  for(int i = 1; i <= n; i++)
  {
    link[i] = i;
    size[i] = 1;
  }
}

// --- Algoritmo de Kruskal ---

vector<pair<int, pii>> kruskal(priority_queue<pair<int, pii>>& pontes, 
                                vector<int>& link, 
                                vector<int>& size)
{
  vector<pair<int, pii>> arestas;
  while(!pontes.empty())
  {
    int c = -pontes.top().first;
    int u = pontes.top().second.first;
    int v = pontes.top().second.second;
    pontes.pop();

    if(!same(u, v, link))
    {
      unite(u, v, link, size);
      arestas.push_back({ c, { u, v } });
    }
  }

  return arestas;
}

// --- Função Principal ---

int main()
{
  // Otimização de I/O (Leitura/Escrita)
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int t; cin >> t;
  while(t--)
  {
    // A fila é local para cada caso de teste
    priority_queue<pair<int, pii>> pontes;

    int n, m; cin >> n >> m;
      
    vector<int> link(n + 1);
    vector<int> size(n + 1);

    init(link, size, n); 

    for(int i = 0; i < m; i++)
    {
      int u, v, c;
      cin >> u >> v >> c;
      pontes.push({ -c, { u, v } });
    }

    vector<pair<int, pii>> pontes_reconstruidas = kruskal(pontes, link, size);

    if(pontes_reconstruidas.size() < n - 1)
    {
      cout << "O vale nao pode ser completamente atravessado.\n\n";
    } 
    else 
    {
      unordered_map<int, int> custos;
      int custo_minimo = 0;
      for(int i = 0; i < n - 1; i++)
      {
        int custo = pontes_reconstruidas[i].first;
        custo_minimo += custo;

        if(custos[custo] == 0) custos[custo] = 1;
        else break;
      }

      if(custos.size() != n - 1)
      {
        cout << "Esse nao e o caminho correto para a Cidade Perdida de Z.\n\n";
      }
      else
      {
        cout << "Custo minimo: " << custo_minimo << "\n"; // \n é mais rápido que endl
        cout << "Pontes reconstruidas:\n";
        for(int i = 0; i < n - 1; i++)
        {
          cout << pontes_reconstruidas[i].second.first;
          cout << " - " << pontes_reconstruidas[i].second.second << "\n";
        }
        cout << "\n";
      }
    }
  }
  return 0;
}