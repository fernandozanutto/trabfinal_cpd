#include <vector>
#include <utility>
#include <iostream>
#include <sstream>
#include "Movie.h"

using namespace std;

class User {
public:
    int id;
    vector<pair<Movie*, double>> ratings;

    User(int _id);
    void addMovie(Movie* movie, double rating);
    int getIdentifier();
    const string toString() const;
};

