
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int main() {
    int n, m;

    cout << "Enter number of courses: ";
    cin >> n;

    cout << "Enter number of students: ";
    cin >> m;

    vector<vector<int>> studentCourses(m);

    cout << "\nEnter courses for each student.\n";
    cout << "Enter number of courses followed by course IDs (1 to "
         << n << ").\n";

    vector<vector<bool>> conflict(
        n, vector<bool>(n, false)
    );

    for (int i = 0; i < m; i++) {
        int k;
        cout << "Student " << i + 1
             << " - number of courses: ";
        cin >> k;

        cout << "Enter course IDs: ";
        for (int j = 0; j < k; j++) {
            int course;
            cin >> course;
            studentCourses[i].push_back(course - 1);
        }

        // Build conflict graph
        for (int j = 0; j < k; j++) {
            for (int l = j + 1; l < k; l++) {
                int u = studentCourses[i][j];
                int v = studentCourses[i][l];

                conflict[u][v] = true;
                conflict[v][u] = true;
            }
        }
    }

    // Calculate degree of each course
    vector<pair<int, int>> courses;

    for (int i = 0; i < n; i++) {
        int degree = 0;

        for (int j = 0; j < n; j++) {
            if (conflict[i][j])
                degree++;
        }

        courses.push_back({degree, i});
    }

    // Welsh-Powell: sort by decreasing degree
    sort(courses.rbegin(), courses.rend());

    vector<int> color(n, -1);
    int totalSlots = 0;

    // Greedy graph colouring
    for (auto course : courses) {
        int u = course.second;
        vector<bool> used(n, false);

        for (int v = 0; v < n; v++) {
            if (conflict[u][v] && color[v] != -1)
                used[color[v]] = true;
        }

        int c = 0;
        while (c < n && used[c])
            c++;

        color[u] = c;
        totalSlots = max(totalSlots, c + 1);
    }

    // Display timetable
    cout << "\n--- Examination Timetable ---\n";
    cout << "Course\tTime Slot\n";

    for (int i = 0; i < n; i++) {
        cout << "C" << i + 1 << "\tSlot "
             << color[i] + 1 << "\n";
    }

    cout << "\nTotal time slots required: "
         << totalSlots << "\n";

    return 0;
}
