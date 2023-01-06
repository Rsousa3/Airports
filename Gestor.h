//
// Created by ricardo on 29-12-2022.
//

#ifndef UNTITLED1_GESTOR_H
#define UNTITLED1_GESTOR_H

#include <unordered_map>
#include <string>
#include <unordered_set>
#include "Airport.h"
#include "Airline.h"
#include "Graph.h"

using namespace std;

class Gestor {
    unordered_map<string, int> codes;
    //unordered_map<int, Airport> airports; //now useless. DELETE LATER
    unordered_map<string, Airport> code_airp;
    unordered_map<string, Airline> code_airline;
    unordered_set<string> cities;
    unordered_set<string> countries;
    Graph graph;

public:
    Gestor();
    Graph getGraph();
    unordered_map<string, int> getCodes();
    void readAirports();
    void readAirlines();
    void readFlights();
    //double Haversine(Position p1, Position p2);
    //vector<int> findAirportsByPos(Position pos, double x);
    //vector<int> findAirportsByCity(string code); TEMP
    void getAirportInfo(string aCode, int flights); //Faz return aos aeroportos atingiveis a partir de aCode no máximo de x flights
    void getFlightAirlines(string aCode, int flights); //Faz return às airlines disponíveis a partir de aCode no máximo de x flights
    void getAirportByLocal(string aCode, int flights, bool city); //Faz return aos locais (cidades ou países) atingiveis a partir de aCode no máximo de x flights
    //void getShortPath(string src, string des, set<string> Airlines, bool filter = false); NOW USELESS
    void getFlightCount(string aCode); //Faz return ao nº de voos disponíveis a partir de um aeroporto
    void getShortestPath(vector<int> srcs, vector<int> dests, set<string> aLines, bool filter = false); //Obtem o path mais curto entre 2 aeroportos, filtrado (ou não) por airlines aLines
    void getArticulationPoints(); //Obtem articulation points
    void getStats(string country); //Recolhe n de aeroportos, voos e airlines num país
    bool checkInput(string inp, bool code = true); //Verifica se o código de aeroporto ou de airline dado no input é válido
    bool checkInputLocal(string inp, bool city = true); //Verifica se o input dado para nome de cidade ou país é válido
};
#endif //UNTITLED1_GESTOR_H
