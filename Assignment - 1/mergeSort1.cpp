#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Function to merge two sorted halves
    void merge(vector<string>& orders, int low, int mid, int high) {
        vector<string> temp;

        int left = low;
        int right = mid + 1;

        // Compare timestamps and store smaller one
        while (left <= mid && right <= high) {
            if (orders[left] <= orders[right]) {
                temp.push_back(orders[left]);
                left++;
            } else {
                temp.push_back(orders[right]);
                right++;
            }
        }

        // Copy remaining elements from left half
        while (left <= mid) {
            temp.push_back(orders[left]);
            left++;
        }

        // Copy remaining elements from right half
        while (right <= high) {
            temp.push_back(orders[right]);
            right++;
        }

        // Copy sorted elements back to original array
        for (int i = low; i <= high; i++) {
            orders[i] = temp[i - low];
        }
    }

    // Recursive Merge Sort function
    void mergeSort(vector<string>& orders, int low, int high) {
        if (low >= high)
            return;

        // Find middle position
        int mid = low + (high - low) / 2;

        // Sort left half
        mergeSort(orders, low, mid);

        // Sort right half
        mergeSort(orders, mid + 1, high);

        // Merge both sorted halves
        merge(orders, low, mid, high);
    }
};

int main() {
    int n;

    cout << "Enter number of customer orders: ";
    cin >> n;

    vector<string> orders(n);

    cout << "Enter order timestamps (HH:MM):" << endl;

    for (int i = 0; i < n; i++) {
        cin >> orders[i];
    }

    Solution sol;

    // Apply Merge Sort
    sol.mergeSort(orders, 0, n - 1);

    cout << "\nSorted customer orders by timestamp:" << endl;

    for (int i = 0; i < n; i++) {
        cout << orders[i] << " ";
    }

    cout << endl;

    return 0;
}
