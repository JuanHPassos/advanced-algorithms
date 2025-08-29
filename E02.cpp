#include<iostream>
#include<vector>
#include<queue>
#include<iomanip>
using namespace std;

int main(void)
{
  size_t testes; cin >> testes;
  while(testes--)
  {
    size_t quant_dias;
    cin >> quant_dias;

    // Vetor que armazena os registros de ganhos e data.
    vector<pair<float,string>> ganho_data(quant_dias);

    // Acesso O(1) ao dia com maior ganho.
    priority_queue<pair<float,int>> ganho_dia;

    // Armazena os valores dos dias restantes na pq.
    float ganhos_restantes = 0;

    for(size_t dia = 0; dia < quant_dias; dia++)
    {
      // Ler a dia(DD/MM/AAAA) e o ganho(xx.xx).
      cin >> ganho_data[dia].second >> ganho_data[dia].first;
      ganhos_restantes += ganho_data[dia].first;
      // Ganho como critério de ordenação primário.
      ganho_dia.push({ganho_data[dia].first, dia});
    } 

    // Armazena ganho dos dias mais lucrativos.
    float maiores_ganhos = 0;

    // Guarda os index dos dias mais lucrativos.
    priority_queue<int> dias_maiores_ganhos;

    // Realizar guloso pegando o maior dia 
    // até ultrapassar os ganhos do restante
    while(maiores_ganhos <= ganhos_restantes)
    {
      // Pegar dia com maior ganho.
      int dia = ganho_dia.top().second;
      ganho_dia.pop(); // Remove dia.

      // Guarda dia em ordem crescente.
      dias_maiores_ganhos.push(-dia);

      // Atualiza valores do dias restante e do acumulado.
      maiores_ganhos += ganho_data[dia].first;
      ganhos_restantes -= ganho_data[dia].first;
    }

    // Numero de dias com maior ganho sobre o restante.
    size_t num_dias = dias_maiores_ganhos.size();
    
    // Ajustar formatação da saída.
    cout << num_dias << (num_dias == 1 ? " dia (" : " dias (");
    while(!dias_maiores_ganhos.empty())
    {
      string data = ganho_data[-dias_maiores_ganhos.top()].second;
      dias_maiores_ganhos.pop();
      cout << data;
      if(dias_maiores_ganhos.size()) cout << ", ";
      else cout << ") | soma=" 
                << fixed << setprecision(2) 
                << maiores_ganhos << " | " 
                << (((float)num_dias)/quant_dias)*100 << "% dos dias totais\n";
    }
  }

  return 0;

}