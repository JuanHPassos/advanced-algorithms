#include<iostream>
#include<queue>
using namespace std;

int main(void)
{
  int h; cin >> h;
  priority_queue<int> c;
  // Ordernar meses que compensa ordenar
  for(int i = 0; i < 12; i++)
  {
    int c_i; cin >> c_i;
    c.push(c_i);
  }

  // Guardar quanto ela cresceu
  int cresceu = 0;
  int meses_regados = 0;
  while(!c.empty() && cresceu < h) 
  {
    cresceu += c.top();
    c.pop();
    meses_regados++;
  }

  // Output do exercicio
  if(cresceu >= h) cout << meses_regados;
  else cout << "nao cresce";

  return 0;
}