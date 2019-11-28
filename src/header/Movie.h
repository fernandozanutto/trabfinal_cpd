#include <string>
#include <sstream>
using namespace std;

class Movie {
public:
    string name; // fiz essas modificações para poder usar com a trie ja dai
    string genres;
    int id;
    int num_ratings;
    double sum_ratings;
    
    Movie(int _id);
    
    Movie(int _id, int _n, double _r);
    
    const string toString() const;
};
