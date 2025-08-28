#include<iostream>
#include<vector>
#include<set>
using namespace std;

// Classe que representa um nó da Trie
class NoTrie 
{
public:
  bool fim_da_palavra;
  NoTrie* filhos[26];

  // Construtor que inicializa o nó da trie
  NoTrie()
  {
    fim_da_palavra = false;
    for (int i = 0; i < 26; i++) 
    {
      filhos[i] = nullptr;
    }
  }
};

// Classe para implementação da trie
class Trie 
{
private:
  NoTrie* raiz;

public:
  Trie() 
  { 
    raiz = new NoTrie(); 
  }

  // Função para inserir uma palavra na trie
  void inserir(string palavra)
  {
    // Começar pelo nó raiz.
    NoTrie* no = raiz;
    for (char c : palavra) 
    {
      int index = c - 'A';
      // Caso não exista o filho, cria-se o nó
      if (!no->filhos[index]) 
      {
        no->filhos[index] = new NoTrie();
      }
      // Atualiza próximo nó a ser visitado
      no = no->filhos[index];
    }
    // O último nó é o fim da palavra
    no->fim_da_palavra = true;
  }

  // Função para procurar uma palavra em um trie
  bool buscar(string palavra)
  {
    NoTrie* no = raiz;
    for (char c : palavra) 
    {
      int index = c - 'A';
      if (!no->filhos[index])
      {
        return false;
      }
      no = no->filhos[index];
    }
    return no->fim_da_palavra;
  }

  // Função para verificar se a palavra é um prefixo
  bool prefixo(string palavra)
  {
    NoTrie* no = raiz;
    for (char c : palavra) 
    {
      int index = c - 'A';
      if (!no->filhos[index])
      {
        return false;
      }
      no = no->filhos[index];
    }
    return true;
  }
};

int main(void)
{
  // quantidade de linhas e colunas
  int l, c;
  cin >> l >> c;

  string caca_palavras[l];
  for(auto &linha : caca_palavras) cin >> linha;

  // Quantidade de palavras no dicionario
  int d;
  cin >> d;
  string dicionario[d];

  for(auto &palavra : dicionario) cin >> palavra;

  // Vetor de movimentos
  vector<pair<int,int>> movs = 
  {
    { 1,  0},  // baixo
    {-1,  0},  // cima
    { 0,  1},  // direita
    { 0, -1},  // esquerda
    { 1,  1},  // diagonal baixo-direita
    {-1, -1},  // diagonal cima-esquerda
    {-1,  1},  // diagonal cima-direita
    { 1, -1}   // diagonal baixo-esquerda
  };

  Trie trie;
  set<string> palavras_achadas;
  for(int i = 0; i < l; i++)
  {
    for(int j = 0; j < c; j++)
    { 
      // Armazenar todas as direções de um elemento na trie
      Trie trie;
      for(auto mov : movs)
      {
        int aux_i = i;
        int aux_j = j;
        string sequencia;
        while(aux_i >= 0 && aux_j >= 0 && aux_i < l && aux_j < c)
        {
          sequencia.push_back(caca_palavras[aux_i][aux_j]);
          aux_i += mov.first; aux_j += mov.second;
        }
        trie.inserir(sequencia);
      }
      // Dado todas as direções, procurar prefixo das palavras
      for(auto palavra : dicionario)
      {
        if(trie.prefixo(palavra)) 
        {
          palavras_achadas.insert(palavra);
        }
      }
    }
  }

  cout << palavras_achadas.size() << endl;
  for(auto palavra_achada : palavras_achadas)
  {
    cout << palavra_achada << endl;
  }

  return 0;
}