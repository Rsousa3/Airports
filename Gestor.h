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
    unordered_map<string, Airport> code_airp; //talvez não seja necessário
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
    void getAirportInfo(string aCode, int flights);
    void getFlightAirlines(string aCode, int flights);
    void getAirportByLocal(string aCode, int flights, bool city);
    //void getShortPath(string src, string des, set<string> Airlines, bool filter = false); NOW USELESS
    void getFlightCount(string aCode);
    void getShortestPath(vector<int> srcs, vector<int> dests, set<string> Alines, bool filter = false);
    void getArticulationPoints();
    void getStats(string country);
    bool checkInput(string inp, bool code = true);
    bool checkInputLocal(string inp, bool city = true);
};
#endif //UNTITLED1_GESTOR_H
