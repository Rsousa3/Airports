#include <iostream>
#include "Gestor.h"

using namespace std;

int main() {
    Gestor g;
    g.readAirports();
    g.readAirlines();
    Graph graph = g.readFlights();
    std::cout << "Hello, World!" << std::endl;


    cout << "Verificar funções:\n"; //TESTE DE FUNÇÕES
    Position p(36.999999,14.614400);
    vector<int> iRes = g.findAirportsByPos(p, 90);
    for (auto it : iRes) cout << it << " ";
    cout <<"\n";
    vector<int> res2 = g.findAirportsByCity("Hamburg"); //TESTE
    for (auto p : res2) cout << p << " ";
    cout << "\n";

//--------------MENU--------------------------------------
    cout << "Descobrir a melhor maneira de voar de um local para o outro (menor nº de voos)";

    return 0;
}
