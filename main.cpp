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

    cout << "Indique a operação que pretende realizar:\n 1. Descobrir trajeto mais curto entre dois aeroportos.\n 2. Obter informações sobre um aeroporto.\n 3. Obter pontos de articulação.\n 4. Estatísticas de país.\n";
    int opc;
    string input;
    int ninput;
    cin >> opc;
    if (opc == 1) {
//-------------------------------------SHORTEST_PATH----------------
        vector<int> partidas;
        vector<int> chegadas;
        set<string> companhias;

        double pLat, pLon, dist;
        Position position;

        bool filter = false;

        cout << "Que aeroporto(s) de partida pretende selecionar?\n 1. Aeroporto específico.\n 2. Aeroportos por cidade.\n 3. Aeroportos por posição.\n";
        cin >> opc;
//----------------1 AEROPORTO-------------------------------
        if (opc == 1) {
            cout << "Indique o código do aeroporto:\n";
            cin >> input;
            if (!g.checkInput(input)) {cout << "Input inválido!"; return 0;}
            partidas.push_back(codes[input]);
        }
//-----------------2 CIDADE--------------------------------------------
        else if (opc == 2) {
            cout << "Indique a cidade:\n";
            cin.ignore();
            getline(cin, input);
            if (!g.checkInputLocal(input)) {cout << "Input inválido!"; return 0;}
            partidas = graph.findAirportsByCity(input);
        }
//------------------3 POSIÇÃO------------------------------------------------------
        else if (opc == 3) {
            cout << "Indique a posição:\n Latitude: ";
            cin >> pLat;
            cout <<"Longitude: ";
            cin >> pLon;
            position = Position(pLat, pLon);
            cout << "A que distância máxima os aeroportos devem estar distanciados (em quilômetros): ";
            cin >> dist; cout << "\n";
            partidas = graph.findAirportByPos(position, dist);
            if (partidas.size() == 0) {cout << "Não existem aeroportos com as condições dadas."; return 0;}
        }
        else {cout << "Input inválido"; return 0;}
//------------------------------CHEGADAS------------------------------------------------------
        cout << "Que aeroporto(s) de chegada pretende selecionar?\n 1. Aeroporto específico.\n 2. Aeroportos por cidade.\n 3. Aeroportos por posição.\n";
        cin >> opc;
//-----------------1 AEROPORTO-----------------------
        if (opc == 1) {
            cout << "Indique o código do aeroporto:\n";
            cin >> input;
            if (!g.checkInput(input)) {cout << "Input inválido!"; return 0;}
            chegadas.push_back(codes[input]);
        }
//-------------------2 CIDADE------------------------------
        else if (opc == 2) {
            cout << "Indique a cidade:\n";
            cin.ignore();
            getline(cin, input);
            if (!g.checkInputLocal(input)) {cout << "Input inválido!"; return 0;}
            chegadas = graph.findAirportsByCity(input);
        }
//-------------------3 POSIÇÃO-----------------------------------------
        else if (opc == 3) {
            cout << "Indique a posição:\n Latitude: ";
            cin >> pLat;
            cout <<"Longitude: ";
            cin >> pLon;
            position = Position(pLat, pLon);
            cout << "A que distância máxima os aeroportos devem estar distanciados (em quilômetros): ";
            cin >> dist; cout << "\n";
            chegadas = graph.findAirportByPos(position, dist);
            if (chegadas.size() == 0) {cout << "Não existem aeroportos com as condições dadas."; return 0;}
        }
        else {cout << "Input inválido"; return 0;}
//----------------FILTRAR POR AIRLINE?------------------------------
        cout << "Pretende filtrar os voos por companhia aérea?\n 1. Sim\n 2. Não\n";
        cin >> opc;
        if (opc != 1 && opc != 2) {cout << "Input inválido."; return 0;}
        if (opc == 1) {
            filter = true;
            cout << "Introduza o código da companhia aérea:\n";
            cin >> input;
            if (!g.checkInput(input, false)) {cout << "Input inválido!"; return 0;}
            companhias.insert(input);
            bool loop = true;
            while (loop) {
                cout << "Acrescentar companhia aérea?\n 1. Sim\n 2. Não\n";
                cin >> opc;
                if (opc == 1) {
                    cout << "Introduza o código da companhia aérea:\n";
                    cin >> input;
                    if (!g.checkInput(input, false)) {cout << "Input inválido! Introduza o código novamente.\n"; continue;}
                    companhias.insert(input);}
                if (opc == 2) {loop = false;}
            }
        }
//-----------------------------APLICAR A FUNÇÃO-------------------------------------------
        cout << "Trajeto mais curto entre os aeroportos selecionados:\n";
        g.getShortestPath(partidas, chegadas, companhias, filter);
    }
    else if (opc == 2) {
//-------------------------INFORMATION----------------------------
        cout << "Selecione o tipo de informação que pretende obter:\n 1. Nº de voos de um aeroporto\n 2. Informações de voos\n";
        cin >> opc;
//------------------------COUNT VOOS------------------------------------------
        if (opc == 1) {
            cout << "Introduza o código do aeroporto:\n";
            cin >> input;
            if (!g.checkInput(input)) {cout << "Input inválido!"; return 0;}
            g.getFlightCount(input);
        }
//-------------------------INFO VOOS--------------------------------------
        else if (opc == 2) {
            cout << "Introduza o código do aeroporto: ";
            cin >> input;
            if (!g.checkInput(input)) {cout << "Input inválido!"; return 0;}
            cout << "Introduza um número máximo de voos permitidos a partir do aeroporto para obter informação: "; //se calhar mudar phrasing
            cin >> ninput;
            cout << "Que tipo de informação pretende obter?\n 1. Destinos\n 2. Local\n 3. Companhias aéreas\n";
            cin >> opc;
//-------------------------DESTINOS----------------------------------------
            if (opc == 1) {
                g.getAirportInfo(input, ninput);
            }
//-------------------------LOCAL----------------------------------------------
            else if (opc == 2) {
                cout << "Pretende obter informação das cidades alcançadas ou dos países?\n 1. Cidades\n 2. Países\n";
                cin >> opc;
                if (opc == 1) g.getAirportByLocal(input, ninput, true);
                else if (opc == 2) g.getAirportByLocal(input, ninput, false);
                else {cout << "Input inválido."; return 0;}
            }
//-------------------------COMPANHIAS AEREAS--------------------------------------
            else if (opc == 3) {
                g.getFlightAirlines(input, ninput);
            }
            else {cout << "Input inválido."; return 0;}
        }
        else {cout << "Input inválido."; return 0;}
    }
//------------------------ARTICULATE POINTS---------------------------------------
    else if (opc == 3) {
        g.getArticulationPoints();
    }
//------------------------STATS-DE-PAÍS-----------------------------------------
    else if (opc == 4) {
        cout << "Introduza o país:\n";
        cin.ignore();
        getline(cin, input);
        if (!g.checkInputLocal(input, false)) {cout << "Input inválido!"; return 0;}
        g.getStats(input);
    }
    else {cout << "Input inválido."; return 0;}
    return 0;
}
