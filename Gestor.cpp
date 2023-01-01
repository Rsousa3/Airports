//
// Created by ricardo on 29-12-2022.
//

#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <iostream>
#include <set>
#include <stack>
#include "Gestor.h"
#include "Airport.h"
#include "Graph.h"

using namespace std;


Gestor::Gestor(): graph(3019, true) {}

void Gestor::readAirports() {
    vector<string> actLine(6);
    ifstream in("/home/ricardo/CLionProjects/untitled1/data/airports.csv");
    string line, word;
    string airCode, airName, city, country;
    double lat, lon;

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
        airports.insert({count, a});
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

void Gestor::readFlights() {
    //Graph graph(3019, true);

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
    //return graph;
}

double Gestor::Haversine(Position p1, Position p2) {
    //distâncias
    double dLat = (p2.getLat() - p1.getLat()) * M_PI / 180.0;
    double dLon = (p2.getLon() - p1.getLon()) * M_PI / 180.0;

    // converter lat e lon para radianos
    double lat1 = p1.getLat() * M_PI / 180.0;
    double lat2 = p2.getLat() * M_PI / 180.0;

    // aplicar fórmula
    double a = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(lat1) * cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}

vector<int> Gestor::findAirportsByPos(Position pos, double x) {
    vector<int> values;
    float curDist;
    string curAirp;
    for (int i = 1; i < 3020; i++) {
        Airport a = airports[i];
        Position p = a.getPosition();
        curDist = Haversine(pos, p);
        if (curDist < x) {
            curAirp = a.getCode();
            values.push_back(codes[curAirp]);
        }
    }
    return values;
}

vector<int> Gestor::findAirportsByCity(string code) {
    vector<int> values;
    for (int i = 1; i < 3020; i++) {
        Airport a = airports[i];
        if (a.getCityName() == code) {
            values.push_back(codes[a.getCode()]);
        }
    }
    return values;
}

void Gestor::getAirportInfo(string aCode, bool allD) {
    int n = codes[aCode];
    vector<int> dests;
    dests = graph.getDestInfo(n, allD);
    Airport src = airports[n];
    if (!allD) {
        cout << "Existe(m) " << dests.size() << " voo(s) para destinos diferentes a partir do aeroporto " << src.getName() << ":\n";
    }
    else {
        cout << "Existe(m) " << dests.size() << " voo(s) a partir do aeroporto " << src.getName() << " :\n";
    }
    for (int dest : dests) {
        Airport a = airports[dest];
        cout << "Aeroporto " << a.getName() << ", " << a.getCityName() << "\n";
    }
}

void Gestor::getFlightAirlines(string aCode) {
    int n = codes[aCode];
    set<string> airlines = graph.getAirlines(n);
    Airport src = airports[n];
    cout << "Existe(m) " << airlines.size() << " companhia(s) aérea(s) diferente(s) com voos em " << src.getName() << ":\n";
    for (string line : airlines) {
        Airline aLine = code_airline[line];
        cout << aLine.getName() << "\n";
    }
}

void Gestor::getAirportByLocal(string aCode) {
    int n = codes[aCode];
    vector<int> airps = graph.getDestInfo(n);
    Airport src = airports[n];
    set<City> locais;
    for (auto a : airps) {
        Airport cur = airports[a];
        locais.insert(cur.getCity());
    }
    cout << "O aeroporto " << src.getName() << " possui voos para " << locais.size() << " locais diferentes:\n";
    for (auto p : locais) {
        cout << p.getCity() << " - " << p.getCountry() << "\n";
    }
}

void Gestor::getShortPath(string src, string des, bool filterLine) {
    int s = codes[src];
    int d = codes[des];
    stack<int> path = graph.getShortestPath(s, d);
    int cur;
    while (path.top() != d) {
        cur = path.top();
        Airport curPort = airports[cur];
        cout << curPort.getCode() << " - ";
        path.pop();
    }
    Airport last = airports[d];
    cout << last.getCode() << "\n";
}