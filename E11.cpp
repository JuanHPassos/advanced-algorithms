// Consiste em contar componentes conexos.

#include<iostream>
#include<vector>
using namespace std;

const int MAXN = 1e3 + 10;

vector<vector<int>> adj(MAXN);
bool visited[MAXN];

void dfs(int s) 
{
  if (visited[s]) return;
  visited[s] = true;
  // process node s
  for (auto u: adj[s]) dfs(u);
}

int main(void)
{
  int t; cin >> t;
  while(t--)
  {
    int n, m; cin >> n >> m;
    
    for(int i = 0; i <= n; i++)
    {
      visited[i] = false;
      adj[i].clear();
    }

    for(int i = 0; i < m; i++)
    {
      int u, v; cin >> u >> v;
      adj[u].push_back(v);
      adj[v].push_back(u);
    }
    
    int ans = 0;
    for(int i = 1; i <= n; i++)
    {
      if(!visited[i])
      {
        dfs(i);
        ans++;
      }
    }
    cout << ans << endl;
  }
}