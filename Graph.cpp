//
// Created by ricardo on 30-12-2022.
//

#include <set>
#include <queue>
#include <stack>
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

stack<int> Graph::getShortestPath(int src, int dest) {
    stack<int> res;
    vector<int> prevs(3020, 0);
    prevs[src] = -1;
    vector<int> dist(3020, 0);
    queue<int> unvisited;
    for (int v = 1; v < 3020; v++) {nodes[v].visited = false;}
    unvisited.push(src);
    nodes[src].visited = true;
    while (!unvisited.empty() || nodes[dest].visited == false) { //para quando o dest é encontrado ou, se não for, quando não houver mais destinos)
        int u = unvisited.front(); unvisited.pop();
        for (auto e : nodes[u].adj) {
            int des = e.dest;
            if (!nodes[des].visited) {
                prevs[des] = u;
                dist[des] = dist[u] + 1;
                unvisited.push(des);
                nodes[des].visited = true;
            }
        }
    }
    int pathL = dist[dest]; //distancia entre src e dest
    if (pathL == 0) {return res;}
    int temp = dest;
    res.push(dest);
    while (pathL != 0) {
        int prevNode = prevs[temp];
        res.push(prevNode);
        temp = prevNode;
        pathL--;
    }
    return res;
}