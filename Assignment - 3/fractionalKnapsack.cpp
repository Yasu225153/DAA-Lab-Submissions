#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Item {
    double weight;
    double value;
    bool isDivisible;
    double ratio;
};

bool compareRatio(Item a, Item b) {
    return a.ratio > b.ratio;
}

double MaxUtilFractional(vector<Item>& items, double W) {

    for (auto& item : items) {
        item.ratio = item.value / item.weight;
    }

    sort(items.begin(), items.end(), compareRatio);

    double totalValue = 0;
    double remainingCapacity = W;

    for (auto& item : items) {

        if (remainingCapacity == 0)
            break;

        if (item.weight <= remainingCapacity) {
            totalValue += item.value;
            remainingCapacity -= item.weight;
        }
        else if (item.isDivisible) {
            double fraction = remainingCapacity / item.weight;
            totalValue += fraction * item.value;
            remainingCapacity = 0;
        }
        else {
            continue;
        }
    }

    return totalValue;
}

int main() {

    int n;
    double W;

    cout << "Enter number of items: ";
    cin >> n;

    vector<Item> items(n);

    for (int i = 0; i < n; i++) {
        cout << "\nItem " << i + 1 << endl;

        cout << "Enter weight: ";
        cin >> items[i].weight;

        cout << "Enter value: ";
        cin >> items[i].value;

        cout << "Is divisible? (1 = Yes, 0 = No): ";
        cin >> items[i].isDivisible;
    }

    cout << "\nEnter knapsack capacity: ";
    cin >> W;

    double maximumValue = MaxUtilFractional(items, W);

    cout << fixed << setprecision(2);
    cout << "\nMaximum Total Utility Value = " << maximumValue << endl;

    return 0;
}
