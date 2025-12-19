#include <iostream>
#include <cstdint>
#include <queue>
#include <vector>
using namespace std;

// horário, retirada(false) ou devolucao(true), cliente e modelo do carro.
using Dados = pair<string, pair<string, pair<int, int>>>;

int main(void)
{
  // max 100 casos testes
  int testes;
  cin >> testes;
  while(testes--)
  {
    // max de 50 carros e 1000 pedidos.
    int carros_existentes; 
    cin >> carros_existentes;
    int pedidos_aluguel;
    cin >> pedidos_aluguel;
  
    priority_queue<Dados, vector<Dados>, greater<Dados>> pedidos;
    for(int i = 0; i < pedidos_aluguel; i++)
    {
      // Ler pedido de aluguel do cliente i
      int cliente_id;
      cin >> cliente_id;
      string horario_chegada, horario_termino;
      cin >> horario_chegada >> horario_termino;
      int modelo_carro;
      cin >> modelo_carro;
    
      // Adicionar aluguel priorizando horario de devolução, retirada e id.
      pedidos.push( { horario_termino, { horario_chegada, { cliente_id, modelo_carro} } } );
    } 

    // Guardar clientes que alugaram os carros.
    vector<queue<int>> alugueis(carros_existentes);
    // Guarda id cliente que está usando carro, 0 caso esteja livre.
    vector<string> carro_ocupado(carros_existentes, "");  
    
    // Lógica para alugar carros, pelos horários
    while(!pedidos.empty())
    {
      // { horario devolucao, { horario retirada, { cliente , modelo carro } } }
      string horario_devolucao = pedidos.top().first;
      string horario_retirada = pedidos.top().second.first;
      int cliente_id = pedidos.top().second.second.first;
      int modelo_carro = pedidos.top().second.second.second;
      pedidos.pop();
      
      // Verificar se o carro está livre.
      if(carro_ocupado[modelo_carro - 1] <= horario_retirada)
      {
        alugueis[modelo_carro - 1].push(cliente_id);
        carro_ocupado[modelo_carro - 1] = horario_devolucao;
      }
    }
    
    // Formatar saída conforme especificação.
    int primeiro = 1;
    for(int i = 0; i < carros_existentes; i++)
    { 
      if(!primeiro) cout << " | ";
      primeiro = 0;

      cout << i + 1 << ": " << alugueis[i].size();
      if (alugueis[i].empty()) continue;
      cout << " = ";


      while(!alugueis[i].empty())
      {
        cout << alugueis[i].front();
        if(alugueis[i].size() > 1) cout << ", ";
        alugueis[i].pop();
      }
    }

    if(testes) cout << endl;
  }

  return 0;
}