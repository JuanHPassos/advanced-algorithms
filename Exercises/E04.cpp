#include<iostream>
#include<vector>
#include<queue>
#include<string>
#include<sstream>
#include<iomanip>
#include<cstdio>
#include<limits>
using namespace std;

typedef struct heroi_
{
  string nome;
  double produtividade;
  // Guardar quests resolvidas e tempo dos herois.
  queue<int> quests_feitas;
  double tempo_atual;
} HEROI;

typedef struct quest_
{
  // Guarda quests a serem executadas após.
  queue<int> sucessoras;
  // Armazena nº dependencias da quest
  int quant_dep;
  double tempo;
  // Guarda tempo que fica sem dep.
  double tempo_min;
} QUEST;

/* Prototipação */
double definir_produtividade(string nivel);
void ler_quests(int num_quests, 
                vector<QUEST> &quest, 
                queue<int> &quests_livres);


int main(void)
{
  int quantidade_testes;
  cin >> quantidade_testes;

  while(quantidade_testes--)
  {
    // Número de heróis e quests.
    int num_herois, num_quests;
    cin >> num_herois >> num_quests;
    vector<HEROI> heroi(num_herois);

    // Obter informações dos herois.
    for(size_t i = 0; i < num_herois; i++)
    {
      string nome, nivel;
      cin >> nome >> nivel;

      // Inicializar campos
      heroi[i].nome = nome;
      heroi[i].produtividade = definir_produtividade(nivel);
      heroi[i].tempo_atual = 0.0;
    }

    vector<QUEST> quest(num_quests);
    // Armazena a quest pronta para ser executada.
    queue<int> quests_livres;

    // Ler entrada das quests
    ler_quests(num_quests, quest, quests_livres);

    double tempo_minimo = 0;
    while(!quests_livres.empty())
    {
        // Obter uma quest livre FIFO.
        int quest_atual = quests_livres.front();
        double tempo_quest = (double)quest[quest_atual].tempo;
        quests_livres.pop();

        // Obter o tempo mínimo que esta quest pode ser iniciada (devido às dependências)
        double tempo_min_quest = quest[quest_atual].tempo_min;

        // Obter o herói que terminará esta quest mais cedo.
        int heroi_atual = 0;
        
        // Calcular o tempo de término para o primeiro herói (heroi 0) como referência
        double duracao_heroi0 = tempo_quest / heroi[0].produtividade;
        double tempo_termino_melhor = max(heroi[0].tempo_atual, tempo_min_quest) + duracao_heroi0;

        // Iterar pelos outros heróis para encontrar um que termine mais cedo
        for(size_t i = 1; i < num_herois; i++)
        {
            double duracao_heroi_i = tempo_quest / heroi[i].produtividade;
            double tempo_termino_i = max(heroi[i].tempo_atual, tempo_min_quest) + duracao_heroi_i;

            if(tempo_termino_i < tempo_termino_melhor)
            {
                tempo_termino_melhor = tempo_termino_i;
                heroi_atual = i;
            }
        }

        // Ele estará livre no tempo em que termina a quest.
        heroi[heroi_atual].tempo_atual = tempo_termino_melhor; 

        // Guardar tempo de conclusão de todas as tarefas.
        tempo_minimo = max(tempo_minimo, heroi[heroi_atual].tempo_atual);
        
        // Adicionar a quest na lista de quests feitas pelo herói atual.
        heroi[heroi_atual].quests_feitas.push(quest_atual + 1); // Salva 1-based.

        // Verificar as quests sucessoras da quest atual.
        while(!quest[quest_atual].sucessoras.empty())
        {
            int quest_sucessora = quest[quest_atual].sucessoras.front();
            quest[quest_atual].sucessoras.pop();
            quest[quest_sucessora].quant_dep--;
            
            // A quest sucessora só pode começar depois que a quest_atual (seu pré-requisito)
            // for concluída. O tempo de conclusão foi 'tempo_heroi[heroi_atual]'.
            quest[quest_sucessora].tempo_min = max(
              quest[quest_sucessora].tempo_min,
              heroi[heroi_atual].tempo_atual
            );
            
            // Se a quest sucessora não tiver mais dependências, adicioná-la na fila de quests livres.
            if(quest[quest_sucessora].quant_dep == 0)
            {
              quests_livres.push(quest_sucessora);
            }
        }
    }

    for(size_t i = 0; i < num_herois; i++)
    {
      cout << heroi[i].nome << " = {";
      while(!heroi[i].quests_feitas.empty())
      {
        cout << heroi[i].quests_feitas.front();
        heroi[i].quests_feitas.pop();
        if(!heroi[i].quests_feitas.empty()) cout << ",";
      }
      cout << "}" << endl;
    }
    cout << "Tempo mínimo: " << fixed << setprecision(2) << tempo_minimo;
    cout << "\n";
    if(quantidade_testes != 0) cout << "\n";
  }
}

double definir_produtividade(string nivel)
{
  double produtividade;
  if (nivel == "Aprendiz") produtividade = 0.75;
  else if (nivel == "Aventureiro") produtividade = 1;
  else if (nivel == "Cavaleiro") produtividade = 1.2;
  else if (nivel == "Mestre") produtividade = 1.5;
  else if (nivel == "Lenda") produtividade = 2;
  else 
  {
    cout << "Nivel invalido" << endl;
    exit(1);
  }

  return produtividade;
}

void ler_quests(int num_quests, 
                vector<QUEST> &quest, 
                queue<int> &quests_livres)
{
  string linha;
  getline(cin, linha);
  // Obter informação das quests
  for(size_t i = 0; i < num_quests; i++)
  {
    // Inicializar campos
    quest[i].quant_dep = 0;
    quest[i].tempo = 0.0;
    quest[i].tempo_min = 0.0;

    // Obter linha com dados da quest.
    getline(cin, linha);
    
    // Armazena string como um fluxo de entrada.
    istringstream iss (linha);

    int quest_atual; // 1-based
    int tempo_quest; 
    iss >> quest_atual >> tempo_quest;

    // Impor 0-based
    quest_atual--;
    quest[quest_atual].tempo = tempo_quest;

    // id da quest predecessora
    int quest_pred = 0;
    while(iss >> quest_pred)
    {
      // Impor 0-based
      quest_pred--;
      if(quest_pred == -1) 
      {
        // Caso sem dependencias
        quests_livres.push(quest_atual);
        break;
      }
      else
      {
        // Quest atual depende da quest_pred
        // A quest sucessora da atual é a ques_pred
        quest[quest_pred].sucessoras.push(quest_atual);
        quest[quest_atual].quant_dep += 1;
      }
    }
  }
}