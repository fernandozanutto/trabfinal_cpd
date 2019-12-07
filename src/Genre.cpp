#include "header/Genre.h"

Genre::Genre(string _genre){
    genre = _genre;
    isSorted = false;
}

void Genre::addMovie(Movie* movie){
    movies.push_back(movie);
}

string Genre::getIdentifier(){
    return genre;
}

vector<Movie*> Genre::getTop(int n){
    vector<Movie*> ans;

    if (!isSorted){
        sortMovies();
        isSorted = true;
    }
    
    for(int i=0; i < n && i < movies.size(); i++){
        ans.push_back(movies[i]);
    }
    
    return ans;
}

double avRating(Movie *m){
    return m->sum_ratings / m->num_ratings;
}

void Genre::sortMovies(){
    // sort movies based on their average rating
    // insertion sort 'cause laziness is real
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
