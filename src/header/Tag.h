#include <vector>
#include <utility>
#include <iostream>
#include <sstream>
#include "Movie.h"

using namespace std;

class Tag {
public:
    string tag;
    vector<Movie*> movies;
    
    Tag(string _tag);
    
    string getIdentifier();
    
    void addMovie(Movie* movie);
    vector<Movie*> getIntersection(const vector<Movie*> &another);
};

