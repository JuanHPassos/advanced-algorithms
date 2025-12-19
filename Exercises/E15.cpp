#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 55;

vector<int> adj[MAXN];
// -1 = não calculado, 0 = perde, 1 = ganha
int estado_jogo[MAXN];

// Função recursiva com memoização (DFS)
// Retorna 1 se o jogador da vez ganha começando em u, 0 caso contrário.
int pode_vencer(int u) 
{
    // Se já calculamos o resultado para este vértice, retorna o valor salvo
    if (estado_jogo[u] != -1) return estado_jogo[u];


    bool chance_de_vitoria = false;

    // Tenta mover para cada vizinho v
    for (int v : adj[u]) 
    {
        // Se, ao mover para v, o oponente NÃO consegue vencer (retorna 0),
        // isso significa que essa é uma jogada vencedora para mim.
        if (pode_vencer(v) == 0) 
        {
            chance_de_vitoria = true;
            break; // Já achei um caminho para ganhar, não preciso testar outros
        }
    }

    // Salva o resultado (1 se achou caminho vitorioso, 0 se não) e retorna
    return estado_jogo[u] = (chance_de_vitoria ? 1 : 0);
}

void resolver_caso() 
{
    // Quantida de de vértices, arestas e posição inicial
    int n, m, s;
    cin >> n >> m >> s;

    // Limpar o grafo para o caso de teste atual
    for (int i = 0; i < n; ++i) 
    {
        adj[i].clear();
        estado_jogo[i] = -1; // -1 = estado não calculado
    }

    // Leitura das arestas (Pistas)
    for (int i = 0; i < m; ++i) 
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }

    // Verifica se Ash (que começa em s) tem estratégia vencedora
    if (pode_vencer(s)) cout << "Ash" << endl;
    else cout << "Noir" << endl;
}

int main() 
{
    int quant_testes;
    cin >> quant_testes;
    while (quant_testes--) resolver_caso();

    return 0;
}