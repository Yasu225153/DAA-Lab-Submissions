#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Movie {
    string title;
    double rating;
    int releaseYear;
    int watchTime;
};

// Display movies
void displayMovies(const vector<Movie>& movies) {

    cout << "\n-------------------------------------------------------------\n";
    cout << "Title\t\tRating\tYear\tWatch Time\n";
    cout << "-------------------------------------------------------------\n";

    for (const Movie& m : movies) {
        cout << m.title << "\t\t"
             << m.rating << "\t"
             << m.releaseYear << "\t"
             << m.watchTime << endl;
    }
}

// Compare two movies according to selected parameter
bool compareMovies(const Movie& a, const Movie& b, int choice) {

    if (choice == 1)
        return a.rating > b.rating;          // Higher rating first

    else if (choice == 2)
        return a.releaseYear > b.releaseYear; // Newer movies first

    else
        return a.watchTime > b.watchTime;    // Higher watch time first
}

// Partition function
int partition(vector<Movie>& movies, int low, int high, int choice) {

    Movie pivot = movies[high];

    int i = low - 1;

    for (int j = low; j < high; j++) {

        if (compareMovies(movies[j], pivot, choice)) {

            i++;

            swap(movies[i], movies[j]);
        }
    }

    swap(movies[i + 1], movies[high]);

    return i + 1;
}

// QuickSort function
void quickSort(vector<Movie>& movies, int low, int high, int choice) {

    if (low < high) {

        int pivotIndex = partition(movies, low, high, choice);

        quickSort(movies, low, pivotIndex - 1, choice);

        quickSort(movies, pivotIndex + 1, high, choice);
    }
}

int main() {

    vector<Movie> movies = {

        {"Inception", 8.8, 2010, 950},
        {"Interstellar", 8.7, 2014, 1200},
        {"Avatar", 7.8, 2009, 1500},
        {"Joker", 8.4, 2019, 1100},
        {"Titanic", 7.9, 1997, 1800},
        {"Oppenheimer", 8.6, 2023, 900},
        {"Avengers", 8.0, 2012, 1600},
        {"Parasite", 8.5, 2019, 700},
        {"The Batman", 7.8, 2022, 1000},
        {"Dune", 8.0, 2021, 850}
    };

    int choice;

    cout << "========== STREAMFLIX MOVIE SORTING ==========\n";

    cout << "\nOriginal Movie Data:";
    displayMovies(movies);

    cout << "\nChoose sorting parameter:\n";
    cout << "1. IMDB Rating\n";
    cout << "2. Release Year\n";
    cout << "3. Watch Time Popularity\n";

    cout << "\nEnter your choice: ";
    cin >> choice;

    if (choice < 1 || choice > 3) {
        cout << "Invalid choice!" << endl;
        return 0;
    }

    // Apply QuickSort
    quickSort(movies, 0, movies.size() - 1, choice);

    cout << "\nSorted Movie Data:";

    if (choice == 1)
        cout << " (Highest IMDB Rating First)\n";

    else if (choice == 2)
        cout << " (Latest Release First)\n";

    else
        cout << " (Highest Watch Time First)\n";

    displayMovies(movies);

    return 0;
}
