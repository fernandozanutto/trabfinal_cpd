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
   
   
   /*fstream movie_trie;
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

   }*/
   Trie films;
   

   films.insert("ToyStory");
   cout << "inseriu" << endl;

   
   bool a = films.search("ToyStory");
   cout << "buscou um que existe " << a << endl;
   cout << endl;
   bool b = films.search("ToyStoryaaa");
   cout << "buscou um que nao existe " << b << endl;
   cout << endl;

   return 0;

}
