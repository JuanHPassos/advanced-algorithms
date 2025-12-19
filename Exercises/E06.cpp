#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

using ponto = pair<double, double>;
using vPonto = vector<ponto>;
using vi = vector<int>;

ponto sub_ponto(ponto a, ponto b);
double norma(ponto p);
int escolher_pivo(const vPonto& p);
double prodVet(ponto a, ponto b);
double prodVet(ponto p, ponto a, ponto b);
vi contruir_colar(const vPonto& pontos);

int main(void)
{
  int testes;
  cin >> testes;
  for(int i = 1; i <= testes; i++)
  {
    int quant_pontos;
    cin >> quant_pontos;

    vPonto pontos(quant_pontos);
    for(int i = 0; i < quant_pontos; i++)
    {
      cin >> pontos[i].first >> pontos[i].second;
    }

    vi colar = contruir_colar(pontos);
  
    printf("Caso %d:\n", i);
    printf("Tamanho do colar: %d\n", colar.size());
    printf("Pedras ancestrais: ");

    for(int i = 0; i < colar.size(); i++)
    {
      if(i != 0) printf(",");
      printf("(%.4lf,%.4lf)", pontos[colar[i]].first, 
                          pontos[colar[i]].second);
    }
    printf("\n\n");
  }

  return 0;
}


ponto sub_ponto(ponto a, ponto b)
{
  return {a.first - b.first, a.second - b.second};
}


double norma(ponto p)
{
  return (p.first*p.first) + (p.second*p.second);
}

int escolher_pivo(const vPonto& p)
{
  // Pivo será o index do menor elemento.
  int pivo = 0;
  for(int i = 1; i < p.size(); i++)
  {
    if(p[i].first < p[pivo].first || (
        (p[i].first == p[pivo].first) && 
        p[i].second < p[pivo].second))
    {
      pivo = i;
    }
  }

  return pivo;
}


double prodVet(ponto a, ponto b)
{
  return (a.first*b.second - b.first*a.second);
}

double prodVet(ponto p, ponto a, ponto b)
{
  return prodVet(sub_ponto(a, p), sub_ponto(b, p));
}

vi contruir_colar(const vPonto& pontos)
{
  // Pivo será o elemento mais a esquerda.
  int pivo = escolher_pivo(pontos);
  vi vPivo, hull = {pivo};

  // Constroe vetor sem o pivo.
  for(int i = 0; i < pontos.size(); i++)
    if(i != pivo)
      vPivo.push_back(i);

  sort(vPivo.begin(), vPivo.end(), 
      [&](int a, int b)
      {
        // Achar os vetores do pivo aos pontos.
        ponto x = sub_ponto(pontos[a], pontos[pivo]); 
        ponto y = sub_ponto(pontos[b], pontos[pivo]); 

        // Realizar produto vetorial entre os vetores.
        double pVet = prodVet(x, y);
        
        // Orientação do prod. vetorial define a direção a virar.
        return (pVet != 0 ? (pVet > 0) : (norma(x) < norma(y))); 
      });

  for(auto &p : vPivo)
  {
    while(hull.size() > 1 && 
          prodVet(pontos[hull[hull.size() - 2]], 
                  pontos[hull.back()], 
                  pontos[p]) <= 0)
    {
      // Remover linha que causa uma virada a esqeurda.
      // Caso ocorra, remove-se o penultimo ponto(p é o ultimo).
      hull.pop_back();
    }
    hull.push_back(p);
  }

  return hull;
}