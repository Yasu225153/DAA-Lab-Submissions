#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

struct Record {
    string id;
    string name;
    string timestamp;
};

void merge(vector<Record>& arr, int left, int mid, int right) {

    vector<Record> temp;

    int i = left;
    int j = mid + 1;

    while (i <= mid && j <= right) {

        if (arr[i].timestamp <= arr[j].timestamp) {
            temp.push_back(arr[i]);
            i++;
        }
        else {
            temp.push_back(arr[j]);
            j++;
        }
    }

    while (i <= mid) {
        temp.push_back(arr[i]);
        i++;
    }

    while (j <= right) {
        temp.push_back(arr[j]);
        j++;
    }

    for (int k = left; k <= right; k++) {
        arr[k] = temp[k - left];
    }
}

void mergeSort(vector<Record>& arr, int left, int right) {

    if (left >= right)
        return;

    int mid = left + (right - left) / 2;

    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);

    merge(arr, left, mid, right);
}

int main() {

    vector<Record> data;

    ifstream file("test.csv");

    if (!file.is_open()) {
        cout << "Error: Could not open test.csv" << endl;
        return 1;
    }

    string line;

    // Skip header
    getline(file, line);

    while (getline(file, line)) {

        if (line.empty())
            continue;

        stringstream ss(line);

        Record r;

        getline(ss, r.id, ',');
        getline(ss, r.name, ',');
        getline(ss, r.timestamp);

        // Remove possible \r from Windows CSV files
        if (!r.timestamp.empty() && r.timestamp.back() == '\r') {
            r.timestamp.pop_back();
        }

        data.push_back(r);
    }

    file.close();

    cout << "Number of records read: " << data.size() << endl;

    if (data.empty()) {
        cout << "No records found!" << endl;
        return 0;
    }

    mergeSort(data, 0, data.size() - 1);

    cout << "\nSorted Data:\n";
    cout << "---------------------------------------------\n";

    for (const auto& r : data) {
        cout << r.id << " "
             << r.name << " "
             << r.timestamp << endl;
    }

    return 0;
}
