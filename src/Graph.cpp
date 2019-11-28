#include "Graph.hpp"
using namespace std;

/**
 * Constructor for constructing graph.
 */
Graph::Graph() {
    map<string, map<string, int> > graphMap;
}

/**
 * Adds vertex-edge pair to the graph.
 * @param source source(start) node
 * @param destination destination node
 * @cost cost the cost from source node to destination node
 * @return true if source exists and false otherwise
 */
bool Graph::addEdge(string source, string des, int cost) {
    // if source already exists in graphMap, just add destination to 
    // the existing adjacency list.
    if (graphMap.count(source)) {
        map<string, map<string, int> >::iterator graphIt = graphMap.begin();
        map<string, map<string, int> >::iterator pos;
        for (pos = graphMap.begin(); pos != graphMap.end(); ++pos) {
            map<string, int>::iterator second;
            if (pos->first == source) {
                pos->second.insert(pair<string, int>(des, cost));
            }
        }
        return true;
    // if source does not exist, add both source and corresponding
    // adjacency list into the graphMap
    } else { 
        map<string, int> adjList;
        map<string, int>::iterator adjIt = adjList.begin();
        adjList.insert(adjIt, pair<string, int>(des, cost));
        addVertex(source, adjList);
        return false;
    }
}

/**
 * Removes the edge between a source node and a destination node.
 * @param source source(start) node
 * @param destination destination node
 * @return true if the edge is removed and false otherwise
 */
bool Graph::removeEdges(string source, string destination) {
    if (graphMap.count(source)) {
        map<string, map<string, int> >::iterator pos;
        for (pos = graphMap.begin(); pos != graphMap.end(); ++pos) {
            map<string, int>::iterator second;
            for (second = pos->second.begin(); second != pos->second.end(); second++) {
                if (second->first == destination) {
                    pos->second.erase(destination);
                    return true;
                }
            }
        }
    }
    return false;
}

/** 
 * Adds a vertex with its adjacency list to the graph.
 * @param source source(start) node
 * @param adjList adjacency list of the source node
 */
void Graph::addVertex(string source, map<string, int> &adjList) {
    if (graphMap.count(source)) {
        return;
    }
    map<string, map<string, int> >::iterator graphIt = graphMap.begin();
    graphMap.insert(graphIt, pair<string, map<string, int> >(source, adjList));
}

/** 
 * Removes a vertex and its adjacency list from the graph
 * @param source source(start) node
 * @return true if source node is removed and false otherwise
 */
bool Graph::removeVertex(string source) {
    if (graphMap.count(source)) {
        map<string, map<string, int> >::iterator pos;
        for (pos = graphMap.begin(); pos != graphMap.end(); ++pos) {
            if (pos->first == source) {
                graphMap.erase(source);
                return true;
            }
        }
    }
    return false;
}

/** 
 * Checks if a given source node is in the graph
 * @param source source(start) node
 * @return true if source node is in the graph and false otherwise
 */
bool Graph::contains(string source) {
    return graphMap.count(source) > 0;
}

/** 
 * Checks if a there is an edge between source node and a destination node
 * @param source source(start) node
 * @param destination destination node
 * @return true if there is an edge and false otherwise.
 */
bool Graph::contains(string source, string dest) {
    map<string, map<string, int> >::iterator pos;
    for (pos = graphMap.begin(); pos != graphMap.end(); ++pos) {
        if (pos->first == source) {
            map<string, int>::iterator second;
            for (second = pos->second.begin(); second != pos->second.end(); second++) {
                if (second->first == dest) {
                    return true;
                }
            }
        }
    }
    return false;
}

/** 
 * Get total number of vertices in the graph.
 * @return total number of vertices.
 */
int Graph::getTotalVertices() {
    return graphMap.size();
}

/** 
 * Checks if there are any vertices with zero inbound vertices.
 * @return vector with the vertices with zero inbound edges
 */
vector<string> Graph::get0InboundVertices() {
    vector<string> zeroInboundVertices;
    vector<string> destinations;
    map<string, map<string, int> >::iterator pos;

    // inserting all the destinations into vector
    for (pos = graphMap.begin(); pos != graphMap.end(); ++pos) {
        map<string, int>::iterator second;
        for (second = pos->second.begin(); second != pos->second.end(); second++) {
            if (find(destinations.begin(), destinations.end(), second->first) != destinations.end()) {
                continue;
            }
            destinations.push_back(second->first);
        }
    }

    // go through start vertex in graphMap and see if destinations vector has it
    // if it does, then it means there is incoming edge for the start vertex
    for (pos = graphMap.begin(); pos != graphMap.end(); ++pos) {
        if (find(destinations.begin(), destinations.end(), pos->first) != destinations.end()) {
            continue;
        } else {
            if (find(destinations.begin(), destinations.end(), pos->first) != destinations.end()) {
                continue;
            } else {
                zeroInboundVertices.push_back(pos->first);
            }
        }
    }
    return zeroInboundVertices;
}

/**
 * Checks if there are any vertices with edges pointing to themselves.
 * @return vector with self-edge vertices
 */
vector<string> Graph::getSelfEdgeVertices() {
    map<string, map<string, int> >::iterator pos;
    vector<string> selfEdgeVerts;
    for (pos = graphMap.begin(); pos != graphMap.end(); ++pos) {
        map<string, int>::iterator second;
        cout << "first: " << pos->first << endl;
        for (second = pos->second.begin(); second != pos->second.end(); second++) {
            cout << "second: " << second->first << endl;
            if (pos->first == second->first) {
                if (find(selfEdgeVerts.begin(), selfEdgeVerts.end(), pos->first) != selfEdgeVerts.end()) {
                    break;
                } else {
                    selfEdgeVerts.push_back(pos->first);
                    break;
                }
            }
        }
    }
    return selfEdgeVerts;
}

/**
 * Checks if there are any vertices with zero outbound vertices.
 * @return vector with vertices with zero outbound edges
 */
vector<string> Graph::get0OutboundVertices() {
    map<string, map<string, int> >::iterator pos;
    vector<string> zeroOutboundVertices;
    for (pos = graphMap.begin(); pos != graphMap.end(); ++pos) {
        map<string, int>::iterator second;
        int numOfDest = 0;
        bool noDestinationExist = false;
        for (second = pos->second.begin(); second != pos->second.end(); second++) {
            if (second->first == "NO_DESTINATION") {
                numOfDest++;
                noDestinationExist = true;
            } else {
                numOfDest++;
            }
        }
        if (numOfDest == 1 && noDestinationExist == true) {
            zeroOutboundVertices.push_back(pos->first);
        }
        numOfDest = 0;
        noDestinationExist = false;
    }
    return zeroOutboundVertices;
}

/**
 * Searches for heaviest cost and its corresponding node.
 * @return map with node and its weight pair
 */
map<string, int> Graph::getHeaviestWeightPair() {
    map<string, map<string, int> >::iterator pos;
    map<string, int> heaviestPair;
    map<string, int>::iterator it = heaviestPair.begin();
    string maxEdge = "";
    int maxVal = 0;
    for (pos = graphMap.begin(); pos != graphMap.end(); ++pos) {
        map<string, int>::iterator second;
        for (second = pos->second.begin(); second != pos->second.end(); second++) {
            if (second->second > maxVal) {
                maxEdge = second->first;
                maxVal = second->second;
            }
        }
    }
    heaviestPair.insert(it, pair<string, int>(maxEdge, maxVal));
    return heaviestPair;
}


/**
 * Searches for the shortest path from a given start node and a destination.
 * @param start start node
 * @param destination destination node
 */
void Graph::shortestPath(string start, string destination) {
    map<string, int> distances;
    map<string, map<string, int> >::iterator pos;
    int INF = 1000000000;
    
    // initializing
    for (pos = graphMap.begin(); pos != graphMap.end(); pos++) {
        distances[pos->first] = INF;
        map<string, int>::iterator second;
        for (second = pos->second.begin(); second != pos->second.end(); second++) {
            distances[second->first] = INF;
        }
    }
    distances[start] = 0;

    dijkstra(distances, start, destination, INF);
}

/**
 * Dijkstra's algorithm to find the shortest path from a start node and a destination node.
 * @param distances all the existing nodes in the graph with INF-initialized costs
 * @param start start node
 * @param destination destination node
 * @param INF pre-set large value
 */
void Graph::dijkstra(map<string, int> distances, string start, string destination, int INF) {
    priority_queue<pair<int, string>, vector<pair<int, string> >, greater<pair<int, string> > > Q;
    map<string, int>::iterator distancesIt;
    map<string, map<string, int> >::iterator graphIt;

    // insert initial node to priority queue
    Q.push(make_pair(0, start));

    // dijkstra using priority queue (min priority)
    while (!Q.empty()) {
        int cost = Q.top().first;
        string currentNode = Q.top().second;
        Q.pop();
        for (graphIt = graphMap.begin(); graphIt != graphMap.end(); graphIt++) {
            if (graphIt->first == currentNode) {
                map<string, int>::iterator second;
                for (second = graphIt->second.begin(); second != graphIt->second.end(); second++) {
                    string nextLocation = second->first;
                    int nextCost = cost + second->second;
                    if (nextCost < distances[nextLocation]) {
                        distances[nextLocation] = nextCost;
                        Q.push(make_pair(nextCost, nextLocation));
                    }
                }
            }
        }
    }
    
    // printing distances
    for (distancesIt = distances.begin(); distancesIt != distances.end(); distancesIt++) {
        cout << "node: " << distancesIt->first << ", cost: " << distancesIt->second << endl;
    }
}

/**
 * Prints start node-destination node pairs
 */
void Graph::printPair() {
    map<string, map<string, int> >::iterator pos;
    for (pos = graphMap.begin(); pos != graphMap.end(); ++pos) {
        cout << "start vertex: " << pos->first << endl;
        map<string, int>::iterator second;
        for (second = pos->second.begin(); second != pos->second.end(); second++) {
            cout << "destination is " << second->first << " and " << "the cost is " << second->second << endl;
        }
    }
}

/**
 * Prints node and cost(weight) pair
 * @param heavyWeight map that contains a node and its corresponding heaviest cost
 */
void Graph::printPair(map<string, int> heavyWeight) {
    map<string, int>::iterator pos;
    for (pos = heavyWeight.begin(); pos!= heavyWeight.end(); ++pos) {
        cout << "key: " << pos->first << endl;
        cout << "weight: " << pos->second << endl;
    }
}

/**
 * Prints list of vertices. Specifically used for zero inbound edge vertices and
 * zero outbound vertices.
 * @param vertx vector with list of vertices
 */
void Graph::printVertx(vector<string> vertx) {
    vector<string>::iterator it;
    if (vertx.size() == 0) {
        cout << "there is no corresponding elements" << endl;
    }
    for (it = vertx.begin(); it != vertx.end(); it++) {
        cout << *it << endl;
    }
}
