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
    
    fstream rating;
    rating.open("minirating.csv", ios::in);
    string temp,b,name,genre;
    getline(rating, temp);
    
    while(getline(rating, temp)){

        stringstream s(temp);
        string word;
        
        getline(s, word, ',');
        //cout << word << endl;
        
        int userId = stoi(word);
        getline(s, word, ',');
        int movieId = stoi(word);
        getline(s, word, ',');
        double r = stod(word);
        
        hashRatings[movieId].num_ratings += 1;
        hashRatings[movieId].sum_ratings += r;
        
        //cout << hashRatings[movieId].toString() << endl;
        
    }
    
    /*
    Loading movies
    */
    
    fstream movie_trie;
    movie_trie.open("movie.csv", ios::in);
    
    int movie_id;
    getline(movie_trie,temp);
    while(getline(movie_trie, temp)){
        stringstream s(temp);
        string word;
        getline(s, word, ',');
        int movieId = stoi(word);
        getline(s, word, '"'); //ignora o primeiro pra poder pegar o nome do filme limpo
        getline(s, word, '"');
        name = word;
        getline(s, word, '"'); // mesma coisa de antes
        getline(s, word, '"');

        genre = word;
        films.insert(name, movieId);
        hashRatings[movieId].genres = genre;
    }
 
    /*
    Searching
    */
    /*
    string option;
    string name;
    cin >> option >> name;
    
    //n sei se vai funcionar com essa simples transformacao
    switch (stoi(option)) {
    case stoi(movie):
        Trie aux;
        aux=films.search(films,name); //isso vai retornar o nodo da ultima letra pesquisada
        while(aux->children!=NULL)
        {

            //percorrer todos os nodos filhos do nodo aux
            //pegando as info
            
        }
        break;
    
    default:
        break;
    }
    */
    return 0;
}

