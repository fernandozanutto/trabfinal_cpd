#pragma once
#include <string>
#include <sstream>
using namespace std;

class Movie {
public:
    int id;
    int num_ratings;
    double sum_ratings;
    string name; // fiz essas modificações para poder usar com a trie ja dai
    string genres;
    
    Movie();
    Movie(int _id);
    Movie(int _id, int _n, double _r);
    Movie(int _id, string _name, string _genre);
    
    const string toString() const;
};

