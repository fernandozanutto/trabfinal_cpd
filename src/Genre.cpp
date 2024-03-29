#include "header/Genre.h"

Genre::Genre(string _genre){
    genre = _genre;
    id = _genre;
    isSorted = false;
}

Genre::Genre(string _genre, string _id){
    genre = _genre;
    id = _id;
    isSorted = false;
}

void Genre::addMovie(Movie* movie){
    movies.push_back(movie);
}

string Genre::getIdentifier(){
    return id;
}

vector<Movie*> Genre::getTop(int n, int min){
    vector<Movie*> ans;
    if(!isSorted){
        sortMovies();
        isSorted = true;
    }
    
    for(int i=0; ((int)ans.size() < n || n == 0) && i < (int)movies.size(); i++){
        if(min == 0 || movies[i]->num_ratings >= min)
            ans.push_back(movies[i]);
    }
    
    return ans;
}

double avRating(Movie *m){
    return m->sum_ratings / m->num_ratings;
}

void Genre::sortMovies(){
    // sort movies based on their average rating
    // insertion sort 'cause laziness is real (actually the reason is because there is no need to use a better algo, not because we're lazy)
    int i,j;
    for(i=1; i < (int) movies.size(); i++){
        for(j=0; j < i; j++){
            if((avRating(movies[i]) > avRating(movies[j]))
            || (avRating(movies[i]) == avRating(movies[j]) && movies[i]->num_ratings > movies[j]->num_ratings)){
                break;
            }
        }
        int x = i;
        while(x > j){
            Movie *temp = movies[x];
            movies[x] = movies[x-1];
            movies[x-1] = temp;
            --x;
        }
    }
}
