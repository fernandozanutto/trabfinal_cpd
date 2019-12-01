#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "header/Hash.h"
#include "header/User.h"
#include "header/Movie.h"
#include "header/Trie.h"

using namespace std;


int main(){

    /*
    Loading movies rating
    */
    Hash<Movie> hashRatings(5471); // ~27k movies
    Trie films;
    
    /*
    Loading movies
    */
    fstream movie_trie;
    movie_trie.open("movie.csv", ios::in);
    string temp, name, genre;
    int movie_id;
    
    getline(movie_trie,temp);
    
    while(getline(movie_trie, temp)){
        
        stringstream s(temp);
        string word;
        getline(s, word, ',');
        int movie_id = stoi(word);
        
        getline(s, word, '"'); //ignora o primeiro pra poder pegar o nome do filme limpo
        getline(s, word, '"');
        name = word;
        
        getline(s, word, '"'); // mesma coisa de antes
        getline(s, word, '"');
        genre = word;
        
        Movie* a = new Movie(movie_id, name, genre);
        hashRatings[movie_id] = a;
        films.insert(name, a);
    }
    
    fstream rating;
    rating.open("minirating.csv", ios::in);
    getline(rating, temp);
    
    while(getline(rating, temp)){

        stringstream s(temp);
        string word;
        
        getline(s, word, ',');
        
        int userId = stoi(word);
        getline(s, word, ',');
        int movieId = stoi(word);
        getline(s, word, ',');
        double r = stod(word);
        
        hashRatings[movieId]->num_ratings += 1;
        hashRatings[movieId]->sum_ratings += r;
        
        //cout << hashRatings[movieId]->toString() << endl;
    }
    
   
    auto c = films.searchPrefix("Toy");
   
    cout << c.size() << endl;
   
    for(auto d: c){
        cout << d.second->toString() << endl;
    }
 
    /*
    Searching
    */
    /*
    auto c = films.searchPrefix("Toy");
   
    cout << c.size() << endl;
   
    for(auto d: c){
        cout << d.second->toString() << endl;
    }
    */
    return 0;
}

