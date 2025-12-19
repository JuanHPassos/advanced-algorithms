#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <cmath>
#include <queue>
#include <iomanip>
#include <algorithm>
#include <set>
using namespace std;

#define pii pair<int, int>
#define pdd pair<double, double>

typedef struct estrela_
{
  string nome;
  double x;
  double y;
  int ordemEntrada;
}ESTRELA;

typedef struct arestas_
{
  double peso;
  int origem;
  int destino;
}ARESTAS;

double CalculaDistanciaPontos(pdd a, pdd b)
{
  return sqrt(pow(abs(a.first - b.first), 2) + 
              pow(abs(a.second - b.second), 2));
}

int find(vector<int> &link, int x) 
{
  while (x != link[x]) x = link[x];
  return x;
}

bool same(vector<int> &link, int a, int b) 
{
  return find(link, a) == find(link, b);
}

void unite(vector<int> &link, 
          vector<int> &size, 
          int a, 
          int b) 
{
  a = find(link, a);
  b = find(link, b);
  if (size[a] < size[b]) swap(a,b);
  size[a] += size[b];
  link[b] = a;
}

bool ComparaPorCoordenada(ESTRELA A, ESTRELA B)
{
  if (A.x < B.x) return true;
  else if (A.x > B.x) return false;
  else
  {
    if (A.y < B.y) return true;
    else return false; 
  }
}

int main(void)
{
  // Números de problemas a serem resolvidos.
  int numeroProblemas;
  cin >> numeroProblemas;

  while(numeroProblemas--)
  {
    // Número de sistemas totais, de sistemas mais importantes e
    // valor máximo de tensão subespacial.
    int sistemasTotais, sistemasImportantes, maxTensaoSupespacial;
    cin >> sistemasTotais >> sistemasImportantes >> maxTensaoSupespacial;

    // Serão informados os nomes e localização (x, y) das estrelas.
    vector<ESTRELA> sistemasEstelares(sistemasTotais);

    // Ligar index com o nome.
    unordered_map<int, string> index_nome;
    unordered_map<string, int> nome_index;

    for(int i = 0; i < sistemasTotais; i++)
    {
      // Ler nome da estrela e coordenada (x, y).
      cin >> sistemasEstelares[i].nome;
      cin >> sistemasEstelares[i].x;
      cin >> sistemasEstelares[i].y;

      // Acesso ao index em O(1) 
      index_nome[i] = sistemasEstelares[i].nome;
      sistemasEstelares[i].ordemEntrada = i;
    }

    // Armazenar distancias entre as estrelas
    priority_queue<pair<double, pii>> distanciasEstrelas;

    // Criar possíveis caminhos entre as estrelas importantes.
    for(int i = 0; i < sistemasImportantes; i++)
    {
      for(int j = i + 1; j < sistemasImportantes; j++)
      {
        // Calcular peso da aresta.
        double distancia = CalculaDistanciaPontos(
          {sistemasEstelares[i].x, sistemasEstelares[i].y},
          {sistemasEstelares[j].x, sistemasEstelares[j].y}
        );
        if(distancia <= maxTensaoSupespacial)
        {
          // Adicionar aresta, com o peso e os nos envolvidos.
          distanciasEstrelas.push({-distancia, {-i, -j}});
        }
      }
    }

    vector<int> link(sistemasImportantes);
    vector<int> size(sistemasImportantes);

    for (int i = 0; i < sistemasImportantes; i++) 
    {
      link[i] = i;
      size[i] = 1;
    }

    while (!distanciasEstrelas.empty()) 
    {
      double distancia = -distanciasEstrelas.top().first;
      pii estrelas = distanciasEstrelas.top().second;
      estrelas = { -estrelas.first, -estrelas.second };

      distanciasEstrelas.pop(); 
      if (!same(link, estrelas.first, estrelas.second)) 
      {
        unite(link, size, estrelas.first, estrelas.second);

        // Imprimir um dos tuneis essencias da malha.
        cout << index_nome[estrelas.first] << ", "
            << index_nome[estrelas.second] << ", "
            << fixed << setprecision(2) 
            << distancia << "\n";
      }
    }

    // Ordenar estrelas por coordenada X.
    sort(sistemasEstelares.begin(),
        sistemasEstelares.end(),
        ComparaPorCoordenada
    );

    set<int> indexEstrelas = { 0, 1 };
    double distanciaMaxima = CalculaDistanciaPontos(
      {sistemasEstelares[0].x, sistemasEstelares[0].y},
      {sistemasEstelares[1].x, sistemasEstelares[1].y}
    );

    // Guardadas com sua ordem de chegada
    pii estrelasInstaveis = {
      min(sistemasEstelares[0].ordemEntrada, sistemasEstelares[1].ordemEntrada),
      max(sistemasEstelares[0].ordemEntrada, sistemasEstelares[1].ordemEntrada)
    };

    for(int i = 2; i < sistemasEstelares.size(); i++)
    { 
      pdd estrelaAtual = {sistemasEstelares[i].x, sistemasEstelares[i].y}; 

      for(auto it = indexEstrelas.begin(); it != indexEstrelas.end(); )
      {
        int index = *it;
        pdd estrelaAnterior = {sistemasEstelares[index].x, sistemasEstelares[index].y};
        
        // Verifica se a estrela anterior está fora da "janela" de busca.
        if(estrelaAtual.first - estrelaAnterior.first > distanciaMaxima)
        {
          // Apaga o elemento e avança o iterador para o próximo elemento válido.
          it = indexEstrelas.erase(it);
        }
        else
        {
          double novaDistancia = CalculaDistanciaPontos(estrelaAtual, estrelaAnterior);
          if (novaDistancia < distanciaMaxima)
          {
            distanciaMaxima = novaDistancia;
            // Salva os ÍNDICES ORIGINAIS do novo melhor par, em ordem crescente.
            estrelasInstaveis = {
              min(sistemasEstelares[index].ordemEntrada, sistemasEstelares[i].ordemEntrada),
              max(sistemasEstelares[index].ordemEntrada, sistemasEstelares[i].ordemEntrada)
            };
          }
          else if (novaDistancia == distanciaMaxima)
          {
              // Cria um par candidato com os índices originais do par atual.
              pii indicesCandidato = {
                min(sistemasEstelares[index].ordemEntrada, sistemasEstelares[i].ordemEntrada),
                max(sistemasEstelares[index].ordemEntrada, sistemasEstelares[i].ordemEntrada)
              };
              
              // A comparação de pares do C++ já faz o desempate lexicográfico!
              if (indicesCandidato < estrelasInstaveis)
              {
                estrelasInstaveis = indicesCandidato;
              }
          }
          // Se não apagou, avança o iterador manualmente.
          ++it;
        }
      }
      indexEstrelas.insert(i);
    }

    cout << "Ponto de Ressonância: " 
        << index_nome[estrelasInstaveis.first] << ", "
        << index_nome[estrelasInstaveis.second]
        << ", " << distanciaMaxima << "\n\n";
  }
  
  return 0;
}