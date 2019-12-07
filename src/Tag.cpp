#include "header/Tag.h"

Tag::Tag(string _tag){
    tag = _tag;
    identifier = _tag;
}


Tag::Tag(string _tag, string _id){
    tag = _tag;
    identifier = _id;
}


void Tag::addMovie(Movie* movie){
    int i;
    for(i=0; i < (int) movies.size(); i++){
        if(movies[i]->id > movie->id){
            break;
        }
    }
    movies.insert(movies.begin() + i, movie);
}

string Tag::getIdentifier(){
    return identifier;
}

vector<Movie*> Tag::getIntersection(const vector<Movie*> &another){
    
    vector<Movie*> answer;
    
    for(int i=0; i < (int) movies.size(); i++){
        int l=0;
        int r=another.size();
        
        while(l<r){
            int mid = (l+r) / 2;
            
            if(another[mid]->id > movies[i]->id){
                r = mid;
            } else if (another[mid]->id < movies[i]->id) {
                l = mid + 1;
            } else {
                answer.push_back(movies[i]);
                break;
            }
        }
    }
    
    return answer;

}
