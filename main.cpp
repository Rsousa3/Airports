#include <iostream>
#include "Gestor.h"

using namespace std;

int main() {
    Gestor g;
    g.readAirports();
    g.readAirlines();
    Graph graph = g.readFlights();
    //std::cout << "Hello, World!" << std::endl;

//--------------MENU--------------------------------------
    cout << "Descobrir a melhor maneira de voar de um local para o outro (menor nº de voos)";

    return 0;
}
