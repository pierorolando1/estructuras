#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;


unordered_map <int, string> m = {
    {0, "Zubiaga"},
    {1, "Piero"},
    {2, "Lizarraga"},
    {3, "Carlos"},
    {4, "Jordan"},
    {5, "Laurente"},
    {6, "Alexis"},
    {7, "Mantilla"},
    {8, "Ledesma"}
};


struct Graph {
    unordered_map<int, vector<int>> *adj;
};

Graph *createGraph() {
    Graph *graph = new Graph();
    graph->adj = new unordered_map<int, vector<int>>();
    return graph;
}

void addEdge(Graph *graph, int src, int dest) {
    (*graph->adj)[src].push_back(dest);
    (*graph->adj)[dest].push_back(src);
}

void displayGraph(Graph *graph) {
    for (auto x : *graph->adj) {
        cout << m[x.first] << " -> ";
        for (auto y : x.second) {
            cout << m[y] << " ";
        }
        cout << endl;
    }

}

void howToReach(Graph *graph, int src, int dest) {
    if (src == dest) {
        cout << "You are already here" << endl;
        return;
    }
    unordered_map<int, bool> visited;
    unordered_map<int, int> parent;
    vector<int> queue;
    queue.push_back(src);
    visited[src] = true;
    parent[src] = -1;
    while (!queue.empty()) {
        int current = queue[0];
        queue.erase(queue.begin());
        for (auto x : (*graph->adj)[current]) {
            if (!visited[x]) {
                queue.push_back(x);
                visited[x] = true;
                parent[x] = current;
            }
        }
    }
    if (!visited[dest]) {
        cout << "There is no path between " << m[src] << " and " << m[dest] << endl;
        return;
    }
    vector<int> path;
    int current = dest;
    while (current != -1) {
        path.push_back(current);
        current = parent[current];
    }

    cout << "Para contactar a " << m[dest];
    cout << " contactar a " << m[path[path.size() - 2]];

    for (int i = path.size() - 3; i >= 0; i--) {
        cout << " y el contactar a " << m[path[i]] << " ";
    }
    cout << endl;
}

int main() {
    Graph *graph = createGraph();
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 4);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);
    addEdge(graph, 3, 8);
    displayGraph(graph);
    howToReach(graph, 0, 8);
    return 0;
}