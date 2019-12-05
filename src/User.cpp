#include "header/User.h"

User::User(int _id){
    id = _id;
}

void User::addMovie(Movie* movie, double rating){
    ratings.push_back({movie, rating});
}

int User::getIdentifier(){
    return id;
}

const string User::toString() const {
    ostringstream buffer;
    
    buffer << "ID User: " << id << " Filmes: ";
    for(pair<Movie*,int> m: ratings){
        buffer << m.first->name << " --- ";
    }
    buffer << endl;
    
    return buffer.str();
}
