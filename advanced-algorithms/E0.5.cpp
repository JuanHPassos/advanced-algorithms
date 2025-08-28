#include<iostream>
#include<iomanip>
#include<math.h>
#include<queue>
using namespace std;

// Raio médio da Terra
const int R = 6371;

double calc_dist(double LatC, double LonC, double Lat, double Lon)
{
  double phi_1 = (M_PI/180)*LatC;
  double phi_2 = (M_PI/180)*Lat;
  
  double lambda_1 = (M_PI/180)*LonC;
  double lambda_2 = (M_PI/180)*Lon;
  
  double delta_phi = phi_2 - phi_1; 
  double delta_lambda = lambda_2 - lambda_1;

  double d = 2*R*asin(sqrt(pow(sin(delta_phi/2), 2) + 
                          cos(phi_1)*cos(phi_2)*pow(sin(delta_lambda/2), 2)));

  return d;
}

int main(void)
{
  // Número de jogadores
  int num_jog; 
  cin >> num_jog;

  // latitude e longitude do ponto correto
  double lat_c, lon_c;
  cin >> lat_c >> lon_c;

  // Guarda distância, ordem de palpite e nome
  priority_queue<pair<double, pair<int, string>>> palpites;

  for(int i = 0; i < num_jog; i++)
  {
    string temp_nome;
    double temp_lat, temp_lon;
    cin >> temp_nome >> temp_lat >> temp_lon;
    // A ordem na pq é dado pela dist, caso seja igual, prioriza-se a ordem.
    // Os resultados são negados para que obtenha-se o menor.
    palpites.push({-calc_dist(lat_c, lon_c, temp_lat, temp_lon), {-i, temp_nome}});
    // fixed força o numero a ser expresso em decimal
    // setprecision(n) -> quantas casas decimais depois da vírgula vão aparecer
    cout << "> [AVISO] MELHOR PALPITE: " 
          << fixed << setprecision(3) << -palpites.top().first << "km\n";
  }

  // Formatação da saída.
  cout << "\nRANKING\n" << "-------\n";

  for(int i = 1; !palpites.empty(); i++)
  {
    string temp_nome = palpites.top().second.second;
    double temp_dist = -palpites.top().first;
    palpites.pop();
    // setw -> quantos caracteres de largura aquela próxima impressão deve ocupar, 
    // preenche o excesso com espaço.
    // left -> Diz para alinhar o conteúdo à esquerda dentro do setw.
    // right -> Diz para alinhar o conteúdo à direita dentro do setw.
    cout << setw(2) << i << ". "
          << left << setw(20) << temp_nome << " : "
          << right << setw(6) << fixed << setprecision(3) << temp_dist << " km";
    if(temp_dist < 0.05) cout << " [FANTASTICO]";
    cout << "\n";
  }

  return 0;
}