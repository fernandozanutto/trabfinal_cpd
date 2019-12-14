#pragma once
#include "header/Movie.h"

Movie::Movie(){
    num_ratings = 0;
    sum_ratings = 0;
}

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

Movie::Movie(int _id, string _name, vector<string> _genre){
    id = _id;
    name = _name;
    genres = _genre;
    num_ratings = 0;
    sum_ratings = 0;
}

const string Movie::toString() const {
    ostringstream buffer;

    buffer << "ID: " << id << "\tNome: " << name <<  "\tMedia: " << sum_ratings/num_ratings << "\tNº avaliacoes: " << num_ratings << endl;

    return buffer.str();
}

int Movie::getIdentifier(){
    return id;
}
