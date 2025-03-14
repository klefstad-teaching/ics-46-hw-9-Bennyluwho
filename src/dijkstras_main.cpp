#include "dijkstras.h"

using namespace std;

int  main() {
    Graph graph;
    file_to_graph("src/small.txt", graph);
    int source = 0;
    int destination = 1;
    vector<int> previous(graph.numVertices, -1);
    vector<int> distances = dijkstra_shortest_path(graph, source, previous);
    vector<int> shortest_path = extract_shortest_path(distances, previous, destination);

    print_path(shortest_path, distances[destination]);

}