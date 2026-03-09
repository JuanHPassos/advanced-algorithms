#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int main(void)
{
  int t; cin >> t;
  // Rodar todos os testes
  while(t--)
  {
    int n, x; cin >> n >> x;
    // Ler peso das crianças
    vector<int> childrens;
    for(int i = 0; i < n; i++)
    {
      int children; cin >> children;
      childrens.push_back(children);
    }

    // Ordenar pesos para tentar pegar uma pesada com uma leve
    sort(childrens.begin(), childrens.end());

    // Tentar juntar a mais pesada com a mais leve
    int l = 0, r = n - 1, ans = 0;
    while(l <= r)
    {
      // Caso em que da para levar a mais pesada com a mais leve
      if(childrens[l] + childrens[r] <= x)
      {
        l++; r--;
      }
      // Caso em que a mais pesada deve ir sozinha
      // Logo não há uma criança leve o suficiente
      else r--;

      ans++;
    }

    cout << ans << endl;
  }

  return 0;
}