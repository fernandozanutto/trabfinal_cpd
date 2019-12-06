#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "header/Hash.h"
#include "header/User.h"
#include "header/Movie.h"
#include "header/Trie.h"
#include "header/Tag.h"

using namespace std;


int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Hash<Movie> hashRatings(5807); // ~27k movies
    Hash<User> hashUsers(27701); // ~138k users
    Hash<Tag> hashTags(90000); // ~490k entries
    Trie trieMovies;                 // ~27k movies

    fstream movie_trie;
    movie_trie.open("movie_clean.csv", ios::in);
    string temp, name;

    getline(movie_trie,temp);
    while(getline(movie_trie, temp)){

        stringstream s(temp);
        string word;
        getline(s, word, ',');
        int movie_id = stoi(word);

        getline(s, word, '"'); //ignora o primeiro pra poder pegar o nome do filme limpo
        getline(s, word, '"');
        name = word;

        getline(s, word, '"');// mesma coisa de antes
        getline(s, word, '"');

        //split genres
        vector<string> genre;
        std::string delimiter = "|";

        size_t pos = 0;
        std::string token;
        while ((pos = word.find(delimiter)) != std::string::npos){
            genre.push_back(word.substr(0, pos));
            word.erase(0, pos + delimiter.length());
        }

        genre.push_back(word);

        Movie* a = new Movie(movie_id, name, genre);
        hashRatings[movie_id] = a;
        trieMovies.insert(name, a);
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

        if(!hashUsers.search(userId)){
            hashUsers[userId] = new User(userId);
        }

        hashUsers[userId]->addMovie(m, r);
    }


    fstream tags;
    tags.open("tags.csv", ios::in);
    getline(tags, temp);

    while(getline(tags, temp)){

        stringstream s(temp);
        string word;
        getline(s, word, ',');
        int userId = stoi(word);

        getline(s, word, ',');
        int movieId = stoi(word);

        getline(s, word, '"'); //ignora o primeiro pra poder pegar o nome do filme limpo
        getline(s, word, '"');
        string tag = word;

        if(!hashTags.search(tag)){
            hashTags[tag] = new Tag(tag);
        }

        hashTags[tag]->addMovie(hashRatings[movieId]);
    }


    // TODO: terminar modo de linha de comando
    // TODO: fazer a intersec��o de filmes em cada tag
    cout << "TA TUDO CARREGADO. LETs DALE" << endl;

    while(true){
        string entrada;
        string option;      // movie, user, top or tag


        cout << "\n\nO que deseja fazer? " << flush;



        getline(cin, entrada);
        stringstream linha_terminal(entrada);

        getline(linha_terminal, option, ' ');
        cout << "DEBUG: " << entrada << " ---- " << option << endl;

        if(option.compare("movie") == 0){

            getline(linha_terminal, option);

            vector<Movie*> key = trieMovies.searchPrefix(option);

            cout << "Movie Id" << '\t' << "Title"<< '\t' << "Genres" << '\t' << "Rating" << '\t' << "Counting"<< endl;
            cout <<"---------------------------------------------------------------------"<< endl;

            for(int i=0; i<(int)key.size(); i++){

                cout << key[i]->id <<'\t' << key[i]->name << '\t';

                for(int j=0; j < (int)key[i]->genres.size(); j++){
                    cout << key[i]->genres[j] << "|";
                }

                int rate = key[i]->num_ratings != 0 ? (key[i]->sum_ratings)/(key[i]->num_ratings) : 0;
                cout << rate << '\t' << key[i]->num_ratings << endl;
            }

        }

        else if (option.compare("user") == 0)
        {
            getline(linha_terminal,option);
            cout << "Title"<<'\t'<< "User Rating"<< '\t'<< "Global Rating"<<'\t'<< "Counting"<< endl;
            cout <<"---------------------------------------------------------------------"<< endl;
            int user_id=stoi(option);
            for(int i=0;i<hashUsers[user_id]->ratings.size();i++)
            {
                cout << hashUsers[user_id]->ratings[i].first->name << '\t';
                cout << hashUsers[user_id]->ratings[i].second <<'\t';
                vector<Movie*> key = trieMovies.searchPrefix(hashUsers[user_id]->rating[i].fist->name);
                int rate = key[i]->num_ratings != 0 ? (key[i]->sum_ratings)/(key[i]->num_ratings) : 0;
                cout << rate << '\t' << key[i]->num_ratings << endl;

            }
        }

        else if (option.compare("top") == 0)
        {
            //ranking dos filmes de um genero
        }

        else if(option.compare("tag") == 0)
        {
            //lista os filme com a tag dada
        }
        else if(option.compare("exit") == 0){
            break;
        }
    }

    return 0;
}


