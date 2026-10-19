#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, W;

    cout << "Enter number of items: ";
    cin >> N;

    vector<int> weight(N), value(N);

    cout << "Enter weight and utility value of each item:\n";
    for (int i = 0; i < N; i++) {
        cin >> weight[i] >> value[i];
    }

    cout << "Enter truck capacity: ";
    cin >> W;

    // Initialize DP table
    vector<vector<int>> dp(N + 1, vector<int>(W + 1, 0));

    // Fill DP table
    for (int i = 1; i <= N; i++) {
        for (int w = 1; w <= W; w++) {
            if (weight[i - 1] <= w) {
                dp[i][w] = max(
                    value[i - 1] + dp[i - 1][w - weight[i - 1]],
                    dp[i - 1][w]
                );
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    cout << "\nMaximum Utility: " << dp[N][W] << endl;

    // Traceback to find selected items
    int w = W;
    vector<int> selectedItems;

    for (int i = N; i >= 1; i--) {
        if (dp[i][w] != dp[i - 1][w]) {
            selectedItems.push_back(i);
            w -= weight[i - 1];
        }
    }

    reverse(selectedItems.begin(), selectedItems.end());

    cout << "Selected Items: ";
    if (selectedItems.empty()) {
        cout << "None";
    } else {
        for (int item : selectedItems) {
            cout << item << " ";
        }
    }

    cout << endl;
    return 0;
}
