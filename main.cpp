#include <iostream>
#include "Gestor.h"

using namespace std;

int main() {
    Gestor g;
    g.readAirports();
    g.readAirlines();
    Graph graph = g.readFlights();
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
