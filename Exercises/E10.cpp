#include<iostream>
#include<cmath>
#include<vector>
using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
// Square
#define SQ(a) (a)*(a)

// Função para checar se um número é primo.
bool prime(ll n) 
{
  // 0 e 1 não são primos.
  if (n < 2) return false;

  // pior caso: primo é sqrt(n)
  for (ll x = 2; SQ(x) <= n; x++) 
  {
    // Se n div por primo, logo não é primo.
    if (n%x == 0) return false;
  }
  return true;
}

ll find(ll n)
{
  // Começar pelo próximo número.
  n++;

  // Sempre existe um número primo entre 
  // (sqrt(n + 1))^2 e (sqrt(n + 1) + 1)^2
  for(ll i = n; ; i++)
  {
    // Checar se é primo
    if(prime(i)) return i;
  }
}

// Função de multiplicação modular segura (a*b)%m
ll modmul(ll a, ll b, ll m) 
{
  ll res = 0;
  a %= m;
  // Multiplicação realizada de forma iterativa.
  // O(log b)
  while (b > 0) 
  {
    // Se b é ímpar, adiciona 'a' ao resultado
    if (b % 2 == 1) res = (res + a) % m;
    
    // Dobra 'a' (com módulo)
    a = (a + a) % m;
    
    // Divide b por 2
    b /= 2;
  }
  return res;
}

// Agora, use modmul dentro da modpow
ll modpow(ll b, ll exp, ll mod) 
{
  // Num^0 == 1, e tirasse o mod.
  if (exp == 0) return 1; // 1 % mod é 1 (assumindo mod > 1)

  // u^n buscasse descobrir u^{n/2}
  ll u = modpow(b, exp/2, mod);
  // u^n = u^{n/2}*u^{n/2}, se n par.
  u = modmul(u, u, mod);
  // Caso n impar, deve-se aumentar o expoente de u em 1.
  if (exp%2 == 1) u = modmul(u, b, mod);
  // Retorna valor de u calculado.
  return u;
}

int main(void)
{
  // n = Primo base e t = valor do tom
  ll n; cin >> n;
  ll t; cin >> t;

  // Achar valor do módulo
  ll p = find(n);

  /*
    x^{-1}.x mod m = 1 
    Se existe inverso modular:
    x^{-1} = x^{\phi(m) - 1}
    \phi(m) = Função Totiente de Euler de m
    Para sempre existir inverso, m deve ser primo,
    porem \phi(nº primo) = m - 1.
    logo x^{-1} = x^{m - 2}
  */

  ll a = modpow(t, p - 2, p);
  cout << a;

  return 0;
}