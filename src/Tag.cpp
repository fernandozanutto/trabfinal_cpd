#include "header/Tag.h"

Tag::Tag(string _tag){
    tag = _tag;
}

void Tag::addMovie(Movie* movie){
    movies.push_back(movie);
}

string Tag::getIdentifier(){
    return tag;
}
