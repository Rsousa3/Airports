//
// Created by ricardo on 29-12-2022.
//

#ifndef UNTITLED1_GESTOR_H
#define UNTITLED1_GESTOR_H

#include <unordered_map>
#include <string>
#include "Airport.h"
#include "Airline.h"
#include "Graph.h"

using namespace std;

class Gestor {
    unordered_map<string, int> codes;
    unordered_map<int, Airport> airports;
    unordered_map<string, Airport> code_airp; //talvez não seja necessário
    unordered_map<string, Airline> code_airline;
    Graph graph;

public:
    Gestor();
    void readAirports();
    void readAirlines();
    void readFlights();
    double Haversine(Position p1, Position p2);
    vector<int> findAirportsByPos(Position pos, double x);
    vector<int> findAirportsByCity(string code);
    void getAirportInfo(string aCode, bool allD = false);
    void getFlightAirlines(string aCode);
    void getAirportByLocal(string aCode);
};
#endif //UNTITLED1_GESTOR_H
