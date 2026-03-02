#include<iostream>
#include<map>
using namespace std;

int main(void)
{
    int n, m;
    cin >> n >> m;
    map<string, string> ip_command;
    // Pego a lista de ips
    for(int i = 0; i < n; i++)
    {
        string command, ip;
        cin >> command >> ip;
        ip_command[ip] = command;
    }

    // Para cada ip passado, comento seu command
    for(int i = 0; i < m; i++)
    {
        string command, ip;
        cin >> command >> ip;

        cout << command << " " << ip << " #";
        ip.pop_back();
        cout << ip_command[ip] << endl;
    }

    return 0;
}