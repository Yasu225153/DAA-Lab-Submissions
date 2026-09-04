#include <bits/stdc++.h>
using namespace std;

void dijkstra(int source, vector<vector<pair<int, int>>> &graph,
              vector<int> &dist, vector<int> &parent) {

    int V = graph.size();

    dist.assign(V, INT_MAX);
    parent.assign(V, -1);

    priority_queue<pair<int, int>,
                   vector<pair<int, int>>,
                   greater<pair<int, int>>> pq;

    dist[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {

        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d > dist[u])
            continue;

        for (auto &edge : graph[u]) {

            int v = edge.first;
            int w = edge.second;

            if (dist[u] != INT_MAX &&
                dist[v] > dist[u] + w) {

                dist[v] = dist[u] + w;
                parent[v] = u;

                pq.push({dist[v], v});
            }
        }
    }
}

void printPath(int destination, vector<int> &parent) {

    vector<int> path;

    for (int v = destination; v != -1; v = parent[v])
        path.push_back(v);

    reverse(path.begin(), path.end());

    for (int i = 0; i < path.size(); i++) {

        char node = 'A' + path[i];

        cout << node;

        if (i != path.size() - 1)
            cout << " -> ";
    }

    cout << endl;
}

void updateEdge(vector<vector<pair<int, int>>> &graph,
                int u, int v, int newWeight) {

    for (auto &edge : graph[u]) {
        if (edge.first == v) {
            edge.second = newWeight;
        }
    }

    for (auto &edge : graph[v]) {
        if (edge.first == u) {
            edge.second = newWeight;
        }
    }
}

int main() {

    int V, E;

    cout << "Enter number of intersections (vertices): ";
    cin >> V;

    cout << "Enter number of roads (edges): ";
    cin >> E;

    vector<vector<pair<int, int>>> graph(V);

    cout << "Enter edges (u v w):\n";

    for (int i = 0; i < E; i++) {

        int u, v, w;

        cin >> u >> v >> w;

        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    int source;

    cout << "Enter ambulance start location (source): ";
    cin >> source;

    int H;

    cout << "Enter number of hospitals: ";
    cin >> H;

    vector<int> hospitals(H);

    cout << "Enter hospital nodes: ";

    for (int i = 0; i < H; i++)
        cin >> hospitals[i];

    vector<int> dist;
    vector<int> parent;

    dijkstra(source, graph, dist, parent);

    int minTime = INT_MAX;
    int nearestHospital = -1;

    cout << "\nInitial Traffic Condition:\n";

    for (int h : hospitals) {

        cout << "Hospital " << char('A' + h)
             << " : " << dist[h] << " minutes\n";

        if (dist[h] < minTime) {

            minTime = dist[h];
            nearestHospital = h;
        }
    }

    cout << "\nNearest hospital is Hospital "
         << char('A' + nearestHospital)
         << " with travel time "
         << minTime << " minutes.\n";

    cout << "Shortest path: ";
    printPath(nearestHospital, parent);

    cout << "\nDynamic Traffic Update\n";

    int u, v, newWeight;

    cout << "Enter road to update (u v): ";
    cin >> u >> v;

    cout << "Enter new travel time: ";
    cin >> newWeight;

    updateEdge(graph, u, v, newWeight);

    dijkstra(source, graph, dist, parent);

    minTime = INT_MAX;
    nearestHospital = -1;

    cout << "\nAfter Traffic Update:\n";

    for (int h : hospitals) {

        cout << "Hospital " << char('A' + h)
             << " : " << dist[h] << " minutes\n";

        if (dist[h] < minTime) {

            minTime = dist[h];
            nearestHospital = h;
        }
    }

    if (nearestHospital == -1 ||
        minTime == INT_MAX) {

        cout << "No hospital reachable.\n";
    }
    else {

        cout << "\nUpdated nearest hospital is Hospital "
             << char('A' + nearestHospital)
             << " with travel time "
             << minTime << " minutes.\n";

        cout << "Updated shortest path: ";
        printPath(nearestHospital, parent);
    }

    return 0;
}
