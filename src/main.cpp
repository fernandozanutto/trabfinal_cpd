#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "header/Hash.h"
#include "header/User.h"
#include "header/Movie.h"
#include "header/Trie.h"
#include "header/ClearString.h"

using namespace std;


int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    /*
    Loading movies rating
    */
    Hash<Movie> hashRatings(5471); // ~27k movies
    Hash<User> hashUsers(27701); // ~138k users
    Trie films;                 // ~27k movies
    ClearString cl;
    
    /*
    Loading movies
    */
    fstream movie_trie;
    movie_trie.open("movie.csv", ios::in);
    string temp, name;
    
    int movie_id;

    getline(movie_trie,temp);
    while(getline(movie_trie, temp)){
    
        stringstream s(temp);
        string word;
        getline(s, word, ',');
        int movie_id = stoi(word);

        getline(s, word, '"'); //ignora o primeiro pra poder pegar o nome do filme limpo
        getline(s, word, '"');
        name = cl.clear_string(word);

        getline(s, word, '"');// mesma coisa de antes
        getline(s, word, '"');

        //split genres
        vector<string> genre;
        std::string delimiter = "|";

        size_t pos = 0;
        std::string token;
        while ((pos = word.find(delimiter)) != std::string::npos)
        {
            genre.push_back(word.substr(0, pos));
            word.erase(0, pos + delimiter.length());
        }
        genre.push_back(word);


        Movie* a = new Movie(movie_id, name, genre);
        hashRatings[movie_id] = a;
        films.insert(name, a);
    }

    fstream rating;
    rating.open("rating.csv", ios::in);
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

        Movie* m = hashRatings[movieId];

        m->num_ratings += 1;
        m->sum_ratings += r;

        if(!hashUsers.search(userId))
        {
            hashUsers[userId] = new User(userId);
        }
        hashUsers[userId]->addMovie(m, r);
    }

    

    // TODO: carregar csv de tags
    // TODO: fazer modo linha de comando dps de carregar tudo
    

    cout << 'TA TUDO CARREGADO. LETs DALE'<< endl;
    cout << 'Entre com a função' << endl;
    string linha_terminal;
    string option;      // movie, user or tag
    cin >> linha_terminal; 
    getline(linha_terminal,option,' ');

    if(strcmp(option,"movie"))
    {
        //pesquisa pelo nomes do filme
    }

    else if (strcmp(option,"user"))
    {
        //listar os filmes avaliados
    }

    else if (strcmp(option,"top"))
    {
        //ranking dos filmes de um genero
    }

    else if(strcmp(option,"tag"))
    {
        //lista os filme com a tag dada
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

