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

using namespace std;

class Graph {
    struct Edge {
        int dest;   // Destination node
        string weight; // Airline code
    };

    struct Node {
        list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        bool visited;   // As the node been visited on a search?
    };

    int n;              // Graph size (vertices are numbered from 1 to n)
    bool hasDir;        // false: undirected; true: directed
    vector<Node> nodes; // The list of nodes being represented

public:
    Graph(int nodes, bool dir = false);
    //vector<Node> getNodes() {return nodes;}
    void addEdge(int src, int des, string weight = "");
    vector<int> getDestInfo(int n, bool allDest = false);
    //set<string> getCountries(int n);
    set<string> getAirlines(int n);
    stack<int> getShortestPath(int src, int dest);
};
#endif //UNTITLED1_GRAPH_H
