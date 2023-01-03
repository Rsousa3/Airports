//
// Created by ricardo on 30-12-2022.
//

#ifndef UNTITLED1_GRAPH_H
#define UNTITLED1_GRAPH_H

#include <string>
#include <list>
#include <vector>
#include <set>
#include <stack>
#include "Position.h"
#include "Airport.h"

using namespace std;

class Graph {
    struct Edge {
        int dest;   // Destination node
        string weight; // Airline code [MAYBE ADD A SPECIFIC PARAMETER FOR AIRLINE]
    };

    struct Node {
        list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        bool visited;   // As the node been visited on a search?
        Airport airport;
    };

    int n;              // Graph size (vertices are numbered from 1 to n)
    bool hasDir;        // false: undirected; true: directed
    vector<Node> nodes; // The list of nodes being represented

public:
    Graph(int nodes, bool dir = false);
    //vector<Node> getNodes() {return nodes;}
    void addAirport(int node, Airport a);
    void addEdge(int src, int des, string weight = "");
    vector<Airport> getDestInfo(int no, int flights = 1);
    //set<string> getCountries(int n);
    set<string> getAirlines(int no, int flights);
    stack<Airport> getShortestPath(int src, int dest, bool limit = false, set<string> lines = set<string>());
    vector<int> findAirportsByCity(string name);
    vector<int> findAirportByPos(Position pos, double x);
    int countFlights(int no);
    string getAirportCode(int ap);
};
#endif //UNTITLED1_GRAPH_H
