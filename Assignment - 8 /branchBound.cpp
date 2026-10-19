
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

struct Node {
    vector<int> path;
    vector<bool> visited;
    int cost, bound, time;

    bool operator>(const Node& other) const {
        return bound > other.bound;
    }
};

int n, timeLimit;
int cost[20][20], travelTime[20][20];
int bestCost = INT_MAX, bestTime;
vector<int> bestPath;

int lowerBound(const Node& u) {
    int b = u.cost;

    for (int i = 0; i < n; i++) {
        if (!u.visited[i]) {
            int mn = INT_MAX;

            for (int j = 0; j < n; j++) {
                if (i != j && (!u.visited[j] || j == 0))
                    mn = min(mn, cost[i][j]);
            }

            b += mn;
        }
    }

    return b;
}

void branchAndBound() {
    priority_queue<Node, vector<Node>, greater<Node>> pq;

    Node root;
    root.path = {0};
    root.visited.assign(n, false);
    root.visited[0] = true;
    root.cost = root.time = 0;
    root.bound = lowerBound(root);

    pq.push(root);

    while (!pq.empty()) {
        Node u = pq.top();
        pq.pop();

        if (u.bound >= bestCost)
            continue;

        int current = u.path.back();

        if (u.path.size() == n) {
            int totalCost = u.cost + cost[current][0];
            int totalTime = u.time + travelTime[current][0];

            if (totalTime <= timeLimit &&
                totalCost < bestCost) {
                bestCost = totalCost;
                bestTime = totalTime;
                bestPath = u.path;
                bestPath.push_back(0);
            }
            continue;
        }

        for (int next = 0; next < n; next++) {
            if (!u.visited[next]) {
                Node v = u;
                v.path.push_back(next);
                v.visited[next] = true;
                v.cost += cost[current][next];
                v.time += travelTime[current][next];

                if (v.time > timeLimit)
                    continue;

                v.bound = lowerBound(v);

                if (v.bound < bestCost)
                    pq.push(v);
            }
        }
    }
}

int main() {
    cout << "Enter number of cities: ";
    cin >> n;

    cout << "Enter cost matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> cost[i][j];

    cout << "Enter travel-time matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> travelTime[i][j];

    cout << "Enter maximum allowed time: ";
    cin >> timeLimit;

    branchAndBound();

    if (bestCost == INT_MAX) {
        cout << "\nNo feasible route exists "
             << "within the time limit.\n";
    } else {
        cout << "\nOptimal Route: ";
        for (int city : bestPath)
            cout << city + 1 << " ";

        cout << "\nMinimum Cost: " << bestCost;
        cout << "\nTotal Time: " << bestTime << endl;
    }

    return 0;
}
