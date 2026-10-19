
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

string colorNames[] = {
    "Red", "Green", "Yellow", "Blue",
    "Magenta", "Cyan", "Orange", "Purple"
};

int main() {
    int n, m;

    cout << "Enter number of courses: ";
    cin >> n;

    cout << "Enter number of students: ";
    cin >> m;

    vector<vector<int> > studentCourses(m);
    vector<vector<bool> > conflict(n, vector<bool>(n, false));

    cout << "\nEnter courses for each student.\n";
    cout << "Enter the number of courses followed by course IDs (1 to "
         << n << ").\n";

    // Input courses and build conflict graph
    for (int i = 0; i < m; i++) {
        int k;

        cout << "\nStudent " << i + 1
             << " - number of courses: ";
        cin >> k;

        cout << "Enter course IDs: ";

        for (int j = 0; j < k; j++) {
            int course;
            cin >> course;

            if (course < 1 || course > n) {
                cout << "Invalid course ID!\n";
                return 1;
            }

            studentCourses[i].push_back(course - 1);
        }

        for (int j = 0; j < k; j++) {
            for (int l = j + 1; l < k; l++) {
                int u = studentCourses[i][j];
                int v = studentCourses[i][l];

                if (u != v) {
                    conflict[u][v] = true;
                    conflict[v][u] = true;
                }
            }
        }
    }

    // Calculate degree of each course
    vector<pair<int, int> > courses;

    for (int i = 0; i < n; i++) {
        int degree = 0;

        for (int j = 0; j < n; j++) {
            if (conflict[i][j]) {
                degree++;
            }
        }

        courses.push_back(make_pair(degree, i));
    }

    // Sort by decreasing degree (Welsh-Powell)
    sort(courses.rbegin(), courses.rend());

    // Assign colors using greedy graph coloring
    vector<int> color(n, -1);
    int totalSlots = 0;

    for (int i = 0; i < n; i++) {
        int u = courses[i].second;
        vector<bool> used(n, false);

        for (int v = 0; v < n; v++) {
            if (conflict[u][v] && color[v] != -1) {
                used[color[v]] = true;
            }
        }

        int c = 0;

        while (c < n && used[c]) {
            c++;
        }

        color[u] = c;
        totalSlots = max(totalSlots, c + 1);
    }

    // Display timetable
    cout << "\n--- Examination Timetable ---\n";
    cout << "Course\tTime Slot\tColor\n";

    for (int i = 0; i < n; i++) {
        cout << "C" << i + 1
             << "\tSlot " << color[i] + 1
             << "\t\t" << colorNames[color[i] % 8]
             << "\n";
    }

    cout << "\nTotal time slots required: "
         << totalSlots << "\n";

    // Display graph coloring
    cout << "\n--- Graph Coloring ---\n";

    for (int i = 0; i < n; i++) {
        cout << "[ C" << i + 1 << " ]"
             << " --> Slot " << color[i] + 1
             << " | Color: " << colorNames[color[i] % 8]
             << "\n";
    }

    // Display conflict graph edges
    cout << "\n--- Conflict Graph Edges ---\n";

    bool hasEdges = false;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (conflict[i][j]) {
                cout << "C" << i + 1
                     << " -- C" << j + 1 << "\n";
                hasEdges = true;
            }
        }
    }

    if (!hasEdges) {
        cout << "No conflicts between courses.\n";
    }

    return 0;
}
