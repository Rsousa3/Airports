//
// Created by ricardo on 30-12-2022.
//

#include <set>
#include "Graph.h"

using namespace std;

Graph::Graph(int nodes, bool dir): n(nodes), hasDir(dir), nodes(nodes + 1) {}

void Graph::addEdge(int src, int des, string weight) {
    if (src < 1 || src > n || des < 1 || des > n) return;
    nodes[src].adj.push_back({des, weight});
    if (!hasDir) nodes[des].adj.push_back({src, weight});
}

vector<int> Graph::getDestInfo(int n, bool allDest) {
    vector<int> res;
    auto node = nodes[n];
    if (!allDest) {
        set<int> temp;
        for (auto i: node.adj) {
            temp.insert(i.dest);
        }
        for (auto t : temp) {
            res.push_back(t);
        }
    }
    if (allDest) {
        for (auto i: node.adj) {
            res.push_back(i.dest);
        }
    }
    return res;
}

set<string> Graph::getAirlines(int n) {
    set<string> res;
    auto node = nodes[n];
    for (auto dest : node.adj) {
        res.insert(dest.weight);
    }
    return res;
}