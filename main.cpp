#include <iostream>
#include "Gestor.h"

using namespace std;

int main() {
    Gestor g;
    g.readAirports();
    g.readAirlines();
    g.readFlights();
    Graph graph = g.getGraph();
    std::cout << "Hello, World!" << std::endl;

/*
    cout << "Verificar funções:\n"; //TESTE DE FUNÇÕES
    Position p(36.999999,14.614400);
    //vector<int> iRes = g.findAirportsByPos(p, 90);
    vector<int> iRes = graph.findAirportByPos(p, 90); // res deve ser 636, 3019
    for (auto it : iRes) cout << it << " ";
    cout <<"\n";
    //vector<int> res2 = g.findAirportsByCity("Hamburg"); //TESTE
    vector<int> res2 = graph.findAirportsByCity("Hamburg"); //res deve ser 173, 185
    for (auto p : res2) cout << p << " ";
    cout << "\n";

//--------------MENU--------------------------------------
    //cout << "Descobrir a melhor maneira de voar de um local para o outro (menor nº de voos)";
    string a = "MAG";
    cout << "Descobrir os voos do aeroporto " << a << ":\n";

    //g.getAirportInfo(a, 1); // 161 para JFK, 7 para MAG, 61 para OPO

    cout << "Descobrir as airlines com voos num aeroporto \n";
    g.getFlightAirlines(a, 2);

    cout << "Descobrir locais para os quais um aeroporto possui um voo:\n";
    g.getAirportByLocal(a, 1, false);
*/
    string s1 = "JFK";
    string s2 = "LIS";
    cout << "Descobrir o caminho mais curto de " << s1 << " a " << s2 << ": \n";
    string ar1 = "RYR";
    string ar2 = "TAP";
    string ar3 = "USA";
    vector<string> lines;
    //lines.push_back(ar1); lines.push_back(ar2);
    lines.push_back(ar3);
    g.getShortPath(s1, s2, lines, true);
    cout << "FIM";
    return 0;
}
