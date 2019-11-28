#include "header/Movie.h"

Movie::Movie(int _id){
    id = _id;
    num_ratings = 0;
    sum_ratings = 0;
}
    
Movie::Movie(int _id, int _n, double _r){
    id = _id;
    num_ratings = _n;
    sum_ratings = _r;
}

const string Movie::toString() const {
    ostringstream buffer;
    
    buffer << "ID: " << id << " Num ratings: " << num_ratings << " Soma: " << sum_ratings << endl;
    return buffer.str();
}
