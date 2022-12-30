//
// Created by ricardo on 30-12-2022.
//

#include "Graph.h"

using namespace std;

Graph::Graph(int nodes, bool dir): n(nodes), hasDir(dir), nodes(nodes + 1) {}

void Graph::addEdge(int src, int des, string weight) {
    if (src < 1 || src > n || des < 1 || des > n) return;
    nodes[src].adj.push_back({des, weight});
    if (!hasDir) nodes[des].adj.push_back({src, weight});
}