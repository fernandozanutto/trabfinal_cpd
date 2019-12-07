#include "header/Tag.h"

Tag::Tag(string _tag){
    tag = _tag;
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
    return tag;
}

vector<Movie*> Tag::getIntersection(const vector<Movie*> &another){
    int s = another.size();
    
    vector<Movie*> answer;
    
    for(int i=0; i < (int) movies.size(); i++){
        int l=0;
        int r=s;
        
        while(l<r){
            int mid = (r-l) / 2;
            if(another[mid]->id > movies[i]->id){
                r = mid;
            } else if (another[mid]->id < movies[i]->id) {
                l = mid;
            } else {
                answer.push_back(movies[i]);
                break;
            }
        }
    }
    
    return answer;

}
