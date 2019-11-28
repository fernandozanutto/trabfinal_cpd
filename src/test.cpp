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
     /*Loading movies
    */
    /*
   Trie films
   fstream movie_trie;
   movie_trie.open("movie.csv", ios :: in);
   string temp;
   getline(movie_trie,temp);
   while(getline(movie_trie, temp)){

        stringstream s(temp);
        string word;
        getline(s, word, ',');
        int movie_id = stoi(word);
        getline(s, word, '"'); //ignora o primeiro pra poder pegar o nome do filme limpo
        getline(s, word, '"');
        string name;
        strcpy(word,name);
        boost::algorithm::to_lower(name); // deixa tudo em minuscula mas n sei se vai ficar lento
        getline(s, word, '"'); // mesma coisa de antes
        getline(s, word, '"');
        string genre;
        strcpy(word,genre);
        films.insert(films,name,movie_id,genre);

   }
   */
    /*
    Loading movies rating
    */
    Hash<Movie> hashRatings(5471); // ~27k movies
    Hash<User> hashUsers(1000);
    
    fstream rating;
    rating.open("minirating.csv", ios::in);
    string temp;
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
        
        hashRatings[movieId].num_ratings += 1;
        hashRatings[movieId].sum_ratings += r;
        
        hashUsers[userId].ratings.push_back({movieId, r});
        
        cout << hashRatings[movieId].toString();
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
