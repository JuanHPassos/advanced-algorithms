#include<iostream>
using namespace std;

int main(void)
{
  int t; cin >> t;
  while(t--)
  {
    string seg; cin >> seg;
    int posSeg = -1;
    int maxTamSeg = -1;

    // As substrings validas começam na posição 1.
    for(int i = 1; i < seg.size(); i++)
    {
      int ii = i;
      int j = 0;
      // Verifica-se a há substring e até onde ela se estende.
      while(ii < seg.size() && seg[ii] == seg[j])
      {
        j++; ii++;
      }
      
      // Caso: substring for um sufixo e for maior que a anterior
      if(maxTamSeg < j && ii == seg.size())
      {
        maxTamSeg = j;
        posSeg = i;
      }
    }

    if(posSeg != -1)
      for(int i = posSeg; i < posSeg + maxTamSeg; i++) cout << seg[i];

    cout << endl;
  }
  
  return 0;
}