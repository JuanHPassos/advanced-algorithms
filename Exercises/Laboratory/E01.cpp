#include<iostream>
#include<map>
using namespace std;

int main(void)
{
    // Ideia eh apenas guardar a quantidade de dias da tarefa
    int t; cin >> t;
    for(int i = 1; i <= t; i++)
    {
        int n; cin >> n;
        map<string, int> mp;
        // pego todas as tarefas e guardo os dias
        for(int i = 0; i < n; i++)
        {
            string nome; int dias;
            cin >> nome >> dias;
            // caso tenha mais de uma tarefa na mesma disciplina
            mp[nome] += dias;
        }
        // Leio prazo maximo de dias e materia do trabalho
        int d; 
        string trab; 
        cin >> d >> trab;

        // Olho apenas para os dias necessarios da disciplina
        cout << "Case " << i << ": ";
        if(!mp.count(trab)) cout << "Do your own homework!";
        else if(mp[trab] <= d) cout << "Yessss";
        else if(mp[trab] <= d+5) cout << "Late";
        else cout << "Do your own homework!";
        cout << endl;
    }

    return 0;
}