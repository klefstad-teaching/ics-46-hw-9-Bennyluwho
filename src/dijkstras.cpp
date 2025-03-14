#include "dijkstras.h"

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int numVertices = G.numVertices;
    vector<int> distances(numVertices, INF);
    vector<bool> visited(numVertices, false);
    distances[source] = 0;

    // Min-heap with (distance, vertex) order
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;
    minHeap.push({0, source});

    while (!minHeap.empty()) {
        int u = minHeap.top().second;  // Extract the vertex with the smallest distance
        minHeap.pop();
        if (visited[u]) continue;
        visited[u] = true;

        for (const Edge &edge : G[u]) {
            int v = edge.dst;
            int weight = edge.weight;
            if (distances[v] > distances[u] + weight) {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                minHeap.push({distances[v], v}); // Push (new distance, vertex)
            }
        }
    }
    previous[source] = -1;
    return distances;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;

    for (int at = destination; at != -1; at = previous[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());
    return path;
}
void print_path(const vector<int>& v, int total) {
    for (size_t i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl << "Total cost is " << total << endl;
}