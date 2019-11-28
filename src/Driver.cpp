#include "Graph.hpp"
using namespace std;

/**
 * This program takes a single csv file, parses it, and constructs a 
 * directed graph. It can obtain the shortest path from a specific start node
 * to a destination node using Dijkstra's algorithm. The program can be called
 * using the command line argument after compiled.
 */

int main(int arc, char* argv[]) {
    string inputPath = "";
    if (arc == 1) {
        cout << "please provide input path!" << endl;
        return 0;
    } else if (arc == 2) {
        inputPath = argv[1];
    } else {
        cout << "unnecessary inputs provided! check your command line inputs!" << endl;
        return 0;
    }
    ifstream file(inputPath.c_str());
    string line;
    if (file.fail()) {
        cout << "file doesn't exist in the directory provided" << endl;
    } else {
        string line;
        Graph graph;
        while (getline(file, line)) {
            stringstream ss(line);
            string source;
            getline(ss, source, ',');

            string destination;
            getline(ss, destination, ',');
            if (ss.rdbuf()->in_avail() == 0) {
                destination = "NO_DESTINATION";
            }
            
            string weightData;
            getline(ss, weightData, ',');
            if (weightData == "") {
                weightData = "-1";
            }

            int cost = stoi(weightData);
            graph.addEdge(source, destination, cost);
        }

        // if you want to see {vertex: {destination:cost}} pair, uncomment below
        //graph.printPair();
        //graph.shortestPath("A", "F");
    }
}
