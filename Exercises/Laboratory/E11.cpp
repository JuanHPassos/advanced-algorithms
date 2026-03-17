#include<bits/stdc++.h>
using namespace std;

int main(void)
{
    int n; cin >> n;
    int dist_saltos[n + 1];
    for(int i = 1; i <= n; i++) cin >> dist_saltos[i];
    // Apenas para inicializar
    dist_saltos[0] = 0;

    int n_saltos = 0;
    int pos = 1;
    while(pos < n)
    {
        // Melhor lugar é o que me leva mais longe caso 
        // eu ainda não alcance o final
        int melhor_salto = -1;
        int pos_melhor_salto = -1;

        // Caso em que já ganhei
        if (pos + dist_saltos[pos] >= n)
        {
            if (pos != n)
            {
                pos = n;
                n_saltos++;
            }

            break;
        }

        // Procurar melhor salto (é o que vai mais longe)
        for(int i = pos + 1; i <= pos + dist_saltos[pos]; i++)
        {
            if (melhor_salto < i + dist_saltos[i])
            {
                melhor_salto = i + dist_saltos[i];
                pos_melhor_salto = i;
            }
        }
        if (melhor_salto == 0 || melhor_salto == -1) break;
        else 
        {
            pos = pos_melhor_salto;
            n_saltos++;
        }
    }

    if (pos < n) cout << "Salto impossivel";
    else cout << n_saltos;

    return 0;
}