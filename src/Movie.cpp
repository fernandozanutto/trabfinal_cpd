#include <string>
#include <sstream>
#include "header/Movie.h"

using namespace std;


class Movie {
public:
    string name; // fiz essas modificações para poder usar com a trie ja dai
    string genres;
    int id;
    int num_ratings;
    double sum_ratings;
    
    Movie(int _id){
        id = _id;
        num_ratings = 0;
        sum_ratings = 0;
    }
    
    Movie(int _id, int _n, double _r){
        id = _id;
        num_ratings = _n;
        sum_ratings = _r;
    }
    
    const string toString() const {
        ostringstream buffer;
        
        buffer << "ID: " << id << " Num ratings: " << num_ratings << " Soma: " << sum_ratings << endl;
        return buffer.str();
    }
    
};
