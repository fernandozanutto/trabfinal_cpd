#pragma once
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class Movie {
public:
    int id;
    int num_ratings;
    double sum_ratings;
    string name;
    vector<string> genres;

    Movie();
    Movie(int _id);
    Movie(int _id, int _n, double _r);
    Movie(int _id, string _name, vector<string> _genre);

    const string toString() const;
};

