#include<iostream>
#include <map>
using namespace std;

int main(void)
{
  int quant_produtos;
  cin >> quant_produtos;
  
  map<string, double> estoque;
  for(int i = 0; i < quant_produtos; i++)
  {
    string codigo;
    double preco_por_quilo;
    cin >> codigo >> preco_por_quilo;
    if(estoque.count(codigo))
    {
      cout <<  "Produto com código " << codigo << " já cadastrado." << endl;
    } else {
      estoque[codigo] = preco_por_quilo;
    }    
  }

  while(true)
  {
    int quant_itens_compra = -1;
    cin >> quant_itens_compra;
    if(quant_itens_compra == -1) break;

    double total_compra = 0;
    for(int i = 0; i < quant_itens_compra; i++)
    {
      string codigo;
      double peso_quilo;
      cin >> codigo >> peso_quilo;
      if(estoque.count(codigo))
      {
        double preco_por_quilo = estoque[codigo];
        total_compra += preco_por_quilo*peso_quilo;
      } else {
        cout <<  "Produto com código " << codigo << " não cadastrado." << endl;
      }
    }

    printf("R$%.02lf\n", total_compra);    
  }

  return 0;
}