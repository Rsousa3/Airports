#include <iostream>
#include "Gestor.h"

using namespace std;

int main() {
    Gestor g;
    g.readAirports();
    g.readAirlines();
    g.readFlights();
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
    //cout << "Descobrir a melhor maneira de voar de um local para o outro (menor nº de voos)";
    //cout << "Descobrir os voos do aeroporto VDB:\n";
    string a = "JFK";
    //g.getAirportInfo(a);

    //cout << "Descobrir as airlines com voos num aeroporto \n";
    //g.getFlightAirlines(a);

    //cout << "Descobrir locais para os quais um aeroporto possui um voo:\n";
    //g.getAirportByLocal(a);

    cout << "Descobrir o caminho mais curto de MAG a JFK: \n";
    string s1 = "JFK";
    string s2 = "MAG";
    g.getShortPath(s1, s2);
    return 0;
}
