# shortest-path-finder
This program is used to find a shortest path from a vertex to any destination vertex in weighted-directed graph.

## Description
Using the path to the input file specified as the command line argument, this program takes a single csv file with start vertices, destination vertices, and their corresponding weights. The program then constructs a weighted-directed graph and calculates the shortest path from a start vertex to a destination vertex using Dijkstra's algorithm. 

## How to use the program
1. Clone the repository onto local machine
```
git clone https://github.com/gerardklee/shortest-path-finder.git
```
2. Have the CSV file ready. First column is start vertex, second column is destination vertex, and third column is weight.
```
los angeles,san francisco,4,
new york,san francisco, 14,
new york, mississippi,4
```
3. Compile the program and output it. In this example, the output is named as graph
```
g++ Driver.cpp Graph.cpp -o graph
```
4. Run
```
./graph path_to_CSV_file
