#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Movie {
    string title;
    double rating;
    int releaseYear;
    int popularity;
};

// Compare movies
bool compareMovies(const Movie& a, const Movie& b, int choice) {
    if (choice == 1)
        return a.rating > b.rating;
    else if (choice == 2)
        return a.releaseYear > b.releaseYear;
    else
        return a.popularity > b.popularity;
}

// Partition Function
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

// QuickSort Function
void quickSort(vector<Movie>& movies, int low, int high, int choice) {
    if (low < high) {
        int pivotIndex = partition(movies, low, high, choice);

        quickSort(movies, low, pivotIndex - 1, choice);
        quickSort(movies, pivotIndex + 1, high, choice);
    }
}

// Display first 10 records
void displayMovies(const vector<Movie>& movies) {
    cout << "\n-------------------------------------------------------------\n";
    cout << "Title\t\tRating\tYear\tPopularity\n";
    cout << "-------------------------------------------------------------\n";

    int limit = min(10, (int)movies.size());

    for (int i = 0; i < limit; i++) {
        cout << movies[i].title << "\t"
             << movies[i].rating << "\t"
             << movies[i].releaseYear << "\t"
             << movies[i].popularity << endl;
    }
}

int main() {

    vector<Movie> movies;

    // Read CSV Records
    ifstream file("movies_real_titles .csv");

    if (!file.is_open()) {
        cout << "Error: Could not open movies_real_titles.csv" << endl;
        return 1;
    }

    string line;

    // Skip header
    getline(file, line);

    while (getline(file, line)) {

        if (line.empty())
            continue;

        stringstream ss(line);

        Movie movie;

        string rating;
        string year;
        string popularity;

        getline(ss, movie.title, ',');
        getline(ss, rating, ',');
        getline(ss, year, ',');
        getline(ss, popularity);

        movie.rating = stod(rating);
        movie.releaseYear = stoi(year);
        movie.popularity = stoi(popularity);

        movies.push_back(movie);
    }

    file.close();

    cout << "Total movies loaded: " << movies.size() << endl;

    if (movies.empty()) {
        cout << "No movie records found." << endl;
        return 1;
    }

    // Select Sorting Parameter
    int choice;

    cout << "\n========== STREAMFLIX MOVIE SORTING ==========\n";

    cout << "\nSelect sorting parameter:\n";
    cout << "1. IMDB Rating\n";
    cout << "2. Release Year\n";
    cout << "3. Popularity\n";

    cout << "\nEnter your choice: ";
    cin >> choice;

    if (choice < 1 || choice > 3) {
        cout << "Invalid choice!" << endl;
        return 1;
    }

    // Apply QuickSort
    quickSort(movies, 0, movies.size() - 1, choice);

    cout << "\nSorted Movie Data:\n";

    if (choice == 1)
        cout << "(Highest IMDB Rating First)\n";
    else if (choice == 2)
        cout << "(Latest Release Year First)\n";
    else
        cout << "(Highest Popularity First)\n";

    // Display only 10 records
    displayMovies(movies);

    // Create Output CSV
    ofstream output("movies_sorted_output.csv");

    if (!output.is_open()) {
        cout << "Error: Could not create output file." << endl;
        return 1;
    }

    output << "title,rating,release_year,popularity\n";

    for (const Movie& movie : movies) {
        output << movie.title << ","
               << movie.rating << ","
               << movie.releaseYear << ","
               << movie.popularity << "\n";
    }

    output.close();

    cout << "\n---------------------------------------------\n";
    cout << "Sorting completed successfully!\n";
    cout << "First 10 sorted records displayed above.\n";
    cout << "Complete sorted data saved in: movies_sorted_output.csv\n";

    return 0;
}
