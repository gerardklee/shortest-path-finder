#ifndef Graph_hpp
#define Graph_hpp
#include <sstream>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <queue>
using namespace std;

class Graph {
    private:
        map<string, map<string, int> > graphMap;

    public:
        Graph();
        bool addEdge(string source, string dest, int cost);
        void addVertex(string source, map<string, int> &adjList);
        bool contains(string source);
        bool contains(string source, string dest);
        void dijkstra(map<string, int> distances, string start, string destination, int INF);
        vector<string> getSelfEdgeVertices();
        map<string, int> getHeaviestWeightPair();
        int getTotalVertices();
        vector<string> get0InboundVertices();
        vector<string> get0OutboundVertices();
        bool removeEdges(string source, string destination);
        bool removeVertex(string source);
        void shortestPath(string start, string destination);
        void printPair();
        void printPair(map<string, int> heavyWeight);
        void printVertx(vector<string> vertx);
};

#endif