//
// Created by ricardo on 29-12-2022.
//

#include <vector>
#include <fstream>
#include <sstream>
#include "Gestor.h"
#include "Airport.h"
#include "Graph.h"

using namespace std;

void Gestor::readAirports() {
    vector<string> actLine(6);
    ifstream in("/home/ricardo/CLionProjects/untitled1/data/airports.csv");
    string line, word;
    string airCode, airName, city, country;
    float lat, lon;

    getline(in, line);
    int count = 1;
    while (getline(in, line)) {
        actLine.clear();
        istringstream iss(line);
        while (getline(iss, word, ',')) {
            actLine.push_back(word);
        }


        airCode = actLine[0];
        airName = actLine[1];
        city = actLine[2];
        country = actLine[3];
        lat = stof(actLine[4]);
        string temp = actLine[5];
        lon = stof(actLine[5]);

        if (!temp.empty() && temp[temp.size() - 1] == '\r')
            temp.erase(temp.size() - 1);

        City c(city, country);
        Position pos(lat, lon);
        Airport a(airCode, airName, c, pos);

        codes.insert({airCode, count});
        code_airp.insert({airCode, a});
        count++;
    }
}

void Gestor::readAirlines() {
    vector<string> actLine(4);
    ifstream in("/home/ricardo/CLionProjects/untitled1/data/airlines.csv");
    string line, word;
    string lineCode, name, sign, country;

    getline(in, line);
    while (getline(in, line)) {
        actLine.clear();
        istringstream iss(line);
        while (getline(iss, word, ',')) {
            actLine.push_back(word);
        }

        lineCode = actLine[0];
        name = actLine[1];
        sign = actLine[2];
        country = actLine[3];

        if (!country.empty() && country[country.size() - 1] == '\r')
            country.erase(country.size() - 1);

        Airline al(lineCode, name, sign, country);
        code_airline.insert({lineCode, al});
    }
}

Graph Gestor::readFlights() {
    Graph graph(63832, true);

    vector<string> actLine(3);
    ifstream in("/home/ricardo/CLionProjects/untitled1/data/flights.csv");
    string line, word;
    string src, targ, airline;

    getline(in, line);
    while (getline(in, line)) {
        actLine.clear();
        istringstream iss(line);
        while (getline(iss, word, ',')) {
            actLine.push_back(word);
        }

        src = actLine[0];
        targ = actLine[1];
        airline = actLine[2];

        int nsrc, ntarg;
        nsrc = codes[src];
        ntarg = codes[targ];
        graph.addEdge(nsrc, ntarg, airline);
    }
    return graph;
}