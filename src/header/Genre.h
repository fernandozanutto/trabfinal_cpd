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
    string id;
    vector<Movie*> movies;
    
    Genre(string _genre);
    Genre(string _genre, string _id);
    
    string getIdentifier();
    
    void addMovie(Movie* movie);
    vector<Movie*> getTop(int n, int min);
};

