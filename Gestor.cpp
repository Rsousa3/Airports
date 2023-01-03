//
// Created by ricardo on 29-12-2022.
//

#include <utility>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <set>
#include <stack>
#include <climits>
#include "Gestor.h"
#include "Airport.h"
#include "Graph.h"

using namespace std;


Gestor::Gestor(): graph(3019, true) {}

Graph Gestor::getGraph() {return graph;}

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

        graph.addAirport(count, a);

        codes.insert({airCode, count});
        code_airp.insert({airCode, a});
        //airports.insert({count, a});
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

/*double Gestor::Haversine(Position p1, Position p2) {
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
} */

/*vector<int> Gestor::findAirportsByPos(Position pos, double x) {
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
} */

/*vector<int> Gestor::findAirportsByCity(string code) {
    vector<int> values;
    for (int i = 1; i < 3020; i++) {
        Airport a = airports[i];
        if (a.getCityName() == code) {
            values.push_back(codes[a.getCode()]);
        }
    }
    return values;
} */

void Gestor::getAirportInfo(string aCode, int flights, bool allD) {
    int n = codes[aCode];
    vector<Airport> dests;
    dests = graph.getDestInfo(n, flights);
    Airport src = code_airp[aCode];
    cout << "Existe(m) " << dests.size() << " voo(s) para destinos diferentes a partir do aeroporto " << src.getName() << ":\n";
    for (auto dest : dests) {
        cout << "Aeroporto " << dest.getName() << ", " << dest.getCityName() << "\n";
    }
}

void Gestor::getFlightAirlines(string aCode, int flights) {
    int n = codes[aCode];
    set<string> airlines = graph.getAirlines(n, flights);
    //Airport src = airports[n];
    Airport src = code_airp[aCode];
    cout << "Existe(m) " << airlines.size() << " companhia(s) aérea(s) diferente(s) com voos em " << src.getName() << ":\n";
    for (string line : airlines) {
        Airline aLine = code_airline[line];
        cout << aLine.getName() << "\n";
    }
}

void Gestor::getAirportByLocal(string aCode, int flights, bool city) {
    int n = codes[aCode];
    vector<Airport> airps = graph.getDestInfo(n, flights);
    Airport src = code_airp[aCode];
    set<City> locais;
    set<string> paises;
    for (auto a : airps) {
        locais.insert(a.getCity());
        paises.insert(a.getCity().getCountry());
    }
    if (city) {
        cout << "O aeroporto " << src.getName() << " possui voo(s) para " << locais.size() << " cidade(s) diferente(s):\n";
        for (auto p : locais) {
            cout << p.getCity() << " - " << p.getCountry() << "\n";
        }
    }
    else {
        cout << "O aeroporto " << src.getName() << " possui voo(s) para " << paises.size() << " país(es) diferente(s):\n";
        for (auto p : paises) {
            cout << p << "\n";
        }
    }
}

void Gestor::getShortPath(string src, string des, set<string> Airlines, bool filter) {
    int s = codes[src];
    int d = codes[des];
    stack<Airport> path = graph.getShortestPath(s, d, filter, Airlines);
    Airport cur;
    if (path.empty()) {cout << "Não existe trajeto que satisfaça as condições dadas.\n";}
    else {
        while (path.top().getCode() != des) {
            cur = path.top();
            //Airport curPort = airports[cur];
            cout << cur.getCode() << " - ";
            path.pop();
        }
        Airport last = code_airp[des];
        cout << last.getCode() << "\n";
    }
}

void Gestor::getFlightCount(string aCode) {
    int n = codes[aCode];
    Airport a = code_airp[aCode];
    int count = graph.countFlights(n);
    cout << "Existe(m) " << count << " voo(s) a partir do aeroporto " << a.getName() << ".\n";
}

void Gestor::getShortestPath(vector<int> srcs, vector<int> dests, set<string> aLines, bool limit) {
    int min = INT_MAX;
    int bestSrc, bestDes;
    stack<Airport> path;
    for (int s : srcs) {
        for (int d : dests) {
            path = graph.getShortestPath(s, d, limit, aLines);
            if (path.empty()) continue;
            if (path.size() < min) {min = path.size(); bestSrc = s; bestDes = d;}
        }
    }
    path = graph.getShortestPath(bestSrc, bestDes, limit, aLines);
    Airport cur;
    string cDes = graph.getAirportCode(bestDes);
    if (path.empty()) {cout << "Não existe trajeto que satisfaça as condições dadas.\n";}
    else {
        while (path.top().getCode() != cDes) {
            cur = path.top();
            cout << cur.getCode() << " - ";
            path.pop();
        }
        Airport last = code_airp[cDes];
        cout << last.getCode() << "\n";
    }
}

unordered_map<string, int> Gestor::getCodes() {
    return codes;
}
