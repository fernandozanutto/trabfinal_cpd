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
   
    Trie films;
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
        
        films.insert(name, a);
    }   
   
    auto c = films.searchPrefix("Toy");
   
    cout << c.size() << endl;
   
    for(auto d: c){
        cout << d.second->toString() << endl;
    }
    
    cout << "fim" << endl;

   return 0;

}
