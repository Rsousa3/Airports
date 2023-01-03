//
// Created by ricardo on 30-12-2022.
//

#include <set>
#include <queue>
#include <stack>
#include "Graph.h"

using namespace std;

Graph::Graph(int nodes, bool dir): n(nodes), hasDir(dir), nodes(nodes + 1) {}

void Graph::addAirport(int node, Airport a) {
    nodes[node].airport = a;
}

void Graph::addEdge(int src, int des, string weight) {
    if (src < 1 || src > n || des < 1 || des > n) return;
    nodes[src].adj.push_back({des, weight});
    if (!hasDir) nodes[des].adj.push_back({src, weight});
}

/* vector<Airport> Graph::getDestInfo(int n, bool allDest) {
    vector<Airport> res;
    auto node = nodes[n];
    if (!allDest) {
        set<int> temp;
        for (auto i: node.adj) {
            temp.insert(i.dest);
        }
        for (auto t : temp) {
            res.push_back(nodes[t].airport);
        }
    }
    if (allDest) {
        for (auto i: node.adj) {
            res.push_back(nodes[i.dest].airport);
        }
    }
    return res;
} */

vector<Airport> Graph::getDestInfo(int no, int flights) {
    vector<Airport> res;
    queue<int> q;
    set<int> temp;
    for (int v = 1; v <= n; v++) nodes[v].visited = false;
    q.push(no);
    nodes[no].visited = true;
    while (!q.empty() && flights != 0) {
        int u = q.front(); q.pop();
        for (auto i: nodes[u].adj) {
            if (!nodes[i.dest].visited) {
                auto w = i.dest;
                res.push_back(nodes[w].airport);
                nodes[w].visited = true;
                q.push(i.dest);
            }
        }
        flights--;
    }
    return res;
}

set<string> Graph::getAirlines(int no, int flights) {
    set<string> res;
    queue<int> q;
    for (int v = 1; v <= n; v++) nodes[v].visited = false;
    q.push(no);
    nodes[no].visited = true;
    while (!q.empty() && flights != 0) {
        int u = q.front(); q.pop();
        for (auto dest : nodes[u].adj) {
            int w = dest.dest;
            if (!nodes[w].visited) {
                res.insert(dest.weight);
                q.push(w);
                nodes[w].visited = true;
            }
        }
        flights--;
    }
    return res;
}

stack<Airport> Graph::getShortestPath(int src, int dest, bool limit, vector<string> lines) {
    stack<Airport> res;
    vector<int> prevs(n + 1, 0);
    prevs[src] = -1;
    vector<int> dist(n + 1, 0);
    queue<int> unvisited;
    for (int v = 1; v <= n; v++) {nodes[v].visited = false;}
    unvisited.push(src);
    nodes[src].visited = true;
    while (!unvisited.empty() && !nodes[dest].visited) { //para quando o dest é encontrado ou, se não for, quando não houver mais destinos)
        int u = unvisited.front(); unvisited.pop();
        for (auto e : nodes[u].adj) {
            if (limit) {
                bool add = false;
                for (auto l : lines) {
                    if (l == e.weight) add = true;
                }
                if (!add) continue;
            }
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
    Airport cA = nodes[temp].airport;
    res.push(cA);
    while (pathL != 0) {
        int prevNode = prevs[temp];
        Airport pA = nodes[prevNode].airport;
        res.push(pA);
        temp = prevNode;
        pathL--;
    }
    return res;
}


vector<int> Graph::findAirportsByCity(string name) {
    vector<int> values;
    for (int i = 1; i <= n; i++) {
        Airport a = nodes[i].airport;
        if (a.getCityName() == name) {
            values.push_back(i);
        }
    }
    return values;
}

vector<int> Graph::findAirportByPos(Position pos, double x) {
    vector<int> values;
    double curDist;
    string curAirp;
    for (int i = 1; i <=n; i++) {
        Airport a = nodes[i].airport;
        Position p = a.getPosition();
        curDist = pos.Haversine(p);
        if (curDist < x) {
            values.push_back(i);
        }
    }
    return values;
}