#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "header/Hash.h"
#include "header/User.h"
#include "header/Movie.h"

using namespace std;


int main(){
    /*
    Loading movies
    */
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
        nome = word;
        getline(s, word, '"'); // mesma coisa de antes
        getline(s, word, '"');

        genre = word;
        films.insert(name, movie_id);
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
