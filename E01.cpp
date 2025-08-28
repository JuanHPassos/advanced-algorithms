#include<iostream>
#include<vector>
using namespace std;

using Pessoa = pair<bool, pair<int, int>>;

int contar_doentes_hereditarios(
  vector<Pessoa>& arv_genetica, 
  int id_pessoa)
{
  if(id_pessoa < 0) return 0;

  // guardar id do pai e da mae(ajustar index)
  int pai = arv_genetica[id_pessoa].second.first;
  int mae = arv_genetica[id_pessoa].second.second;
  int eh_diabetico = 0;

  // deve conhecer pai e mae, e pelo menos um deles devem ser doente.
  if(pai >= 0 && (arv_genetica[pai].first || arv_genetica[mae].first))
  {
    // caso tenha a doença, pode ser hereditaria.
    eh_diabetico = (arv_genetica[id_pessoa].first ? 1 : 0);
  } 

  return (eh_diabetico  // pessoa atual
       + contar_doentes_hereditarios(arv_genetica, pai)   // ramo paterno
       + contar_doentes_hereditarios(arv_genetica, mae));  // ramo materno
}

int main(void) 
{
  int t; cin >> t;
  while(t--) 
  {
    int n; cin >> n;
    vector<Pessoa> arv_genetica(n);

    for(auto &pessoa : arv_genetica)
    {
      int id, pai, mae;
      string aux;
      cin >> id >> aux >> pai >> mae;
      pessoa.first = (aux == "sim" ? true : false);
      pessoa.second = {--pai, --mae};
    }
    cout << contar_doentes_hereditarios(arv_genetica, 0) << endl;
  }

  return 0;
}