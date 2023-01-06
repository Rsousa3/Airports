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
        string weight; // Airline code
    };

    struct Node {
        list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        bool visited;   // As the node been visited on a search?
        Airport airport;
        int low;
        int num;
    };

    int n;              // Graph size (vertices are numbered from 1 to n)
    bool hasDir;        // false: undirected; true: directed
    vector<Node> nodes; // The list of nodes being represented

public:
    Graph(int nodes, bool dir = false);
    void addAirport(int node, Airport a);
    void addEdge(int src, int des, string weight = "");
    vector<Airport> getDestInfo(int no, int flights = 1); //Recolhe os aeroportos atingíveis no máximo de n flights
    set<string> getAirlines(int no, int flights); //Recolhe as airlines presentes no máximo de n flights
    stack<Airport> getShortestPath(int src, int dest, bool limit = false, set<string> lines = set<string>()); //Obtém o trajeto mais curto entre 2 aeroportos, limitado (ou náo) por airlines WORST CASE O(E x A) (A é número de airlines, se A for 0 é só O(E))
    vector<int> findAirportsByCity(string name); //Recolhe todos os aeroportos numa cidade
    vector<int> findAirportsByCountry(string c); //Recolhe todos os aeroportos num país
    vector<int> findAirportByPos(Position pos, double x); //Recolhe todos os aeroportos a um máximo de x kms de distância da posição pos
    int countFlights(int no); //Conta os voos a partir de um aeroporto
    string getAirportCode(int ap);
    void dfsArt(int v, int& order, list<Airport>& l); //Recolhe os pontos de articulação para a lista l através de um dfs
    list<Airport> ArtPoints(); //Recolhe os pontos de articulação
    int countCountryFlights(vector<int> ns); //Conta voos de uma lista de aeroportos (pelo código)
    int countAirlines(vector<int> ns); //Conta airlines de uma lista de aeroportos
};
#endif //UNTITLED1_GRAPH_H
