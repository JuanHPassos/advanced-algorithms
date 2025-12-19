#include<iostream>
#include<vector>
#include<queue>
#include <algorithm>
using namespace std;

// MACROS
typedef pair<int,int> pii;

/* Prototipação */
int conquistar(int l, int r, vector<pii>& pos_ini_fim);
int dividir(int l, int r, vector<pii>& pos_ini_fim);

int main(void)
{
  int trechos;
  cin >> trechos;
  // Armazena o trecho e a quantidade de ultrapassagens
  priority_queue<pii> ult_trecho;
  for(int trecho_i = 0; trecho_i < trechos; trecho_i++)
  {
    int quant_jog;
    cin >> quant_jog;
    
    // Armazena posição inicial e final dos jogadores.
    vector<pii> pos_ini_fim(quant_jog);

    // Ler posição inicial e final dos jogadores.
    for(int jog_i = 0; jog_i< quant_jog; jog_i++)
    {
      cin >> pos_ini_fim[jog_i].first;
      cin >> pos_ini_fim[jog_i].second;
    }

    sort(pos_ini_fim.begin(), pos_ini_fim.end());

    int ult = dividir(0, quant_jog - 1, pos_ini_fim);
    ult_trecho.push({ ult, trecho_i });
  }

  while(!ult_trecho.empty())
  {
    int ultrapassagens = ult_trecho.top().first;
    int trecho = ult_trecho.top().second;
    ult_trecho.pop();

    cout << trecho << " " << ultrapassagens << endl;
  }

  return 0;
}

int dividir(int l, int r, vector<pii>& pos_ini_fim)
{
  if(l == r) return 0;
  int meio = (l + r)/2;
  int ultrapassagens = 0;
  ultrapassagens += dividir(l, meio, pos_ini_fim);
  ultrapassagens += dividir(meio + 1, r, pos_ini_fim);
  return (ultrapassagens + conquistar(l, r, pos_ini_fim));
}

/*
 Um vetor da esquerda, sempre começa antes de um vetor da direita.
 Logo, se um vetor da direita é colocado antes de um vetor da esquerda,
 houve inversão(ultrapassagem).
*/
int conquistar(int l, int r, vector<pii>& pos_ini_fim)
{
  int ultrapassagens = 0;
  int meio = (l + r)/2;

  vector<pii> esq(pos_ini_fim.begin() + l, 
                  pos_ini_fim.begin() + meio + 1);
  vector<pii> dir(pos_ini_fim.begin() + meio + 1, 
                  pos_ini_fim.begin() + r + 1);

  int ll = 0, rr = 0, pos = l;
  while(ll < esq.size() && rr < dir.size())
  {
    if(esq[ll].second < dir[rr].second)
    {
      pos_ini_fim[pos] = esq[ll];
      ll++;
    } 
    else 
    {
      // Evento de "ultrapassagem" (inversão)
      pos_ini_fim[pos] = dir[rr];
      rr++;
      // O elemento dir[rr] pulou TODOS os elementos restantes de 'esq'
      ultrapassagens += (esq.size() - ll); 
    }
    pos++;
  } 

  // Termina de preencher o vetor
  while(ll < esq.size()) 
  {
    pos_ini_fim[pos] = esq[ll];
    ll++; 
    pos++;
  }

  while(rr < dir.size()) 
  {
    pos_ini_fim[pos] = dir[rr];
    rr++; 
    pos++;
  }
  
  return ultrapassagens;
}