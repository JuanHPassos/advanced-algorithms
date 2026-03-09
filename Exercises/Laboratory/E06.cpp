#include<bits/stdc++.h>
using namespace std;

int main(void)
{
  int t; cin >> t;
  while(t--)
  {
    int entregas, motoboys;
    cin >> entregas >> motoboys;
    // Tempo fim e tempo inicio
    vector<pair<int,int>> v;
    // Guardar tempo em que meu motoboy acaba o pedido
    multiset<int> fim_entregas;
    for(int i = 0; i < entregas; i++)
    {
      int ini, fim; cin >> ini >> fim;
      v.push_back({fim, -ini});
    }

    sort(v.begin(), v.end());

    for(int i = 0; i < motoboys; i++) fim_entregas.insert(0);

    int ans = 0;
    // Bo trabalhar
    for(int i = 0; i < entregas; i++)
    {
      auto fim_entrega = fim_entregas.lower_bound(v[i].second);
      // Se o proximo pedido, ja tiver entregador
      if(fim_entrega != fim_entregas.end())
      {
        fim_entregas.erase(fim_entrega);
        fim_entregas.insert(-v[i].first);
        ans++;
      }
    }
    cout << ans << endl;  
  }
}