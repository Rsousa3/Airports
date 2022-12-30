#include <iostream>
#include "Gestor.h"

using namespace std;

int main() {
    Gestor g;
    g.readAirports();
    g.readAirlines();
    Graph graph = g.readFlights();
    std::cout << "Hello, World!" << std::endl;
    cout << "Verificar qual o aeroporto mais perto de lat 31 lon 30\n"; //TESTE DE FUNÇÕES
    Position p(37.000000,14.614400);
    int iRes = g.findAirportByPos(p);
    cout << iRes << "\n";

//--------------MENU--------------------------------------
    cout << "Descobrir a melhor maneira de voar de um local para o outro (menor nº de voos)";

    return 0;
}
