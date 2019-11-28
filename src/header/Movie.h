#include <string>

class Movie {
public:

    Movie(int _id){}
    
    Movie(int _id, int _n, double _r){}
    
    std::string name; // fiz essas modificações para poder usar com a trie ja dai
    std::string genres;
    int id;
    int num_ratings;
    double sum_ratings;
    
    const std::string toString() const {}
};
