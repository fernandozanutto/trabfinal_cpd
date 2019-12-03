#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "header/Hash.h"
#include "header/User.h"
#include "header/Movie.h"
#include "header/Trie.h"

using namespace std;


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    /*
    Loading movies rating
    */
    Hash<Movie> hashRatings(5471); // ~27k movies
    Hash<User> hashUsers(27701); // ~138k users
    Trie films;

    /*
    Loading movies
    */
    fstream movie_trie;
    movie_trie.open("movie.csv", ios::in);
    string temp, name;
    vector<string> genre;
    int movie_id;

    getline(movie_trie,temp);
    while(getline(movie_trie, temp))
    {
        stringstream s(temp);
        string word;
        getline(s, word, ',');
        int movie_id = stoi(word);

        getline(s, word, '"'); //ignora o primeiro pra poder pegar o nome do filme limpo
        getline(s, word, '"');
        name = clear_string(word);

        getline(s, word, '"');// mesma coisa de antes
        getline(s, word, '"');

        //split genres
        std::string delimiter = "|";

        size_t pos = 0;
        std::string token;
        while ((pos = word.find(delimiter)) != std::string::npos)
        {
            genre.push_back(word.substr(0, pos));
            word.erase(0, pos + delimiter.length());
        }
        std::cout << s << std::endl;


        Movie* a = new Movie(movie_id, name, genre);
        hashRatings[movie_id] = a;
        films.insert(name, a);
    }

    fstream rating;
    rating.open("rating.csv", ios::in);
    getline(rating, temp);

    while(getline(rating, temp))
    {

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
    // TODO: salvar generos de filmes como um vector de strings

    //cout << hashUsers[48644]->toString() << endl;

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

