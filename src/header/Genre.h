#include <vector>
#include <utility>
#include <iostream>
#include <sstream>
#include "Movie.h"

using namespace std;

class Genre {
private:
    bool isSorted;
    void sortMovies();
public:
    string genre;
    vector<Movie*> movies;
    
    Genre(string _genre);
    
    string getIdentifier();
    
    void addMovie(Movie* movie);
    vector<Movie*> getTop(int n, int min);
};

