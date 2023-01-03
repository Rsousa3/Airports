#include <iostream>
#include "Gestor.h"

using namespace std;

int main() {
    Gestor g;
    g.readAirports();
    g.readAirlines();
    g.readFlights();
    Graph graph = g.getGraph();
    auto codes = g.getCodes();
    cout << "-------------------------------------menu-------------------------------------------------------\n";

    cout << "Indique a operação que pretende realizar:\n 1. Descobrir trajeto mais curto entre dois aeroportos.\n 2. Obter informações sobre um aeroporto.\n";
    int opc;
    cin >> opc;
    if (opc == 1) {
//-------------------------------------SHORTEST_PATH----------------
        vector<int> partidas;
        vector<int> chegadas;
        set<string> companhias;
        string input;

        double pLat, pLon, dist;
        Position position;

        bool filter = false;

        cout << "Que aeroporto(s) de partida pretende selecionar?\n 1. Aeroporto específico.\n 2. Aeroportos por cidade.\n 3. Aeroportos por posição.\n";
        cin >> opc;
//----------------1 AEROPORTO-------------------------------
        if (opc == 1) {
            cout << "Indique o código do aeroporto:\n";
            cin >> input;
            partidas.push_back(codes[input]);
        }
//-----------------2 CIDADE--------------------------------------------
        else if (opc == 2) {
            cout << "Indique a cidade:\n";
            cin.ignore();
            //cin >> input;
            getline(cin, input);
            partidas = graph.findAirportsByCity(input);
        }
//------------------3 POSIÇÃO------------------------------------------------------
        else if (opc == 3) {
            cout << "Indique a posição:\n Latitude: ";
            cin >> pLat;
            cout <<"\n Longitude: ";
            cin >> pLon; cout <<"\n";
            position = Position(pLat, pLon);
            cout << "A que distância máxima os aeroportos devem estar distanciados (em quilômetros): ";
            cin >> dist; cout << "\n";
            partidas = graph.findAirportByPos(position, dist);
        }
//------------------------------CHEGADAS------------------------------------------------------
        cout << "Que aeroporto(s) de chegada pretende selecionar?\n 1. Aeroporto específico.\n 2. Aeroportos por cidade.\n 3. Aeroportos por posição.\n";
        cin >> opc;
//-----------------1 AEROPORTO-----------------------
        if (opc == 1) {
            cout << "Indique o código do aeroporto:\n";
            cin >> input;
            chegadas.push_back(codes[input]);
        }
//-------------------2 CIDADE------------------------------
        else if (opc == 2) {
            cout << "Indique a cidade:\n";
            cin.ignore();
            getline(cin, input);
            //cin >> input;
            chegadas = graph.findAirportsByCity(input);
        }
//-------------------3 POSIÇÃO-----------------------------------------
        else if (opc == 3) {
            cout << "Indique a posição:\n Latitude: ";
            cin >> pLat;
            cout <<"\n Longitude: ";
            cin >> pLon; cout <<"\n";
            position = Position(pLat, pLon);
            cout << "A que distância máxima os aeroportos devem estar distanciados (em quilômetros): ";
            cin >> dist; cout << "\n";
            chegadas = graph.findAirportByPos(position, dist);
        }
//----------------FILTRAR POR AIRLINE?------------------------------
        cout << "Pretende filtrar os voos por companhia aérea?\n 1. Sim\n 2. Não\n";
        cin >> opc;
        if (opc == 1) {
            filter = true;
            cout << "Introduza o código da companhia aérea:\n";
            cin >> input;
            companhias.insert(input);
            bool loop = true;
            while (loop) {
                cout << "Acrescentar companhia aérea?\n 1. Sim\n 2. Não\n";
                cin >> opc;
                if (opc == 1) {companhias.insert(input);}
                if (opc == 2) {loop = false;}
            }
        }
//-----------------------------APLICAR A FUNÇÃO-------------------------------------------
        cout << "Trajeto mais curto entre os aeroportos selecionados:\n";
        g.getShortestPath(partidas, chegadas, companhias, filter);
    }
    else if (opc == 2) {
//-------------------------INFORMATION----------------------------
    }


    /*cout << "Ver caminho mais curto em Portugal para "

    std::cout << "Hello, World!" << std::endl;

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
    cout << "Contar voos que saem do aeroporto " << s1 << " :\n";
    g.getFlightCount(s1);
    cout << "FIM";
    */



    return 0;
}
