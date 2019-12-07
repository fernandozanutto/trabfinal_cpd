#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "header/Hash.h"
#include "header/User.h"
#include "header/Movie.h"
#include "header/Trie.h"
#include "header/Tag.h"
#include "header/Genre.h"
#include "header/ClearString.h"

using namespace std;


int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Hash<Movie> hashRatings(5807); // ~27k movies
    Hash<User> hashUsers(27701); // ~138k users
    Hash<Tag> hashTags(90000); // ~490k entries
    Hash<Genre> hashGenres(5000); // TODO: review size, no ideia how many different genres there are
    Trie trieMovies;                 // ~27k movies
    ClearString cl;

    fstream movie_trie;
    movie_trie.open("movie.csv", ios::in);
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
        string token;
        while ((pos = word.find(delimiter)) != string::npos){
            genre.push_back(word.substr(0, pos));
            word.erase(0, pos + delimiter.length());
        }

        genre.push_back(word);

        Movie* a = new Movie(movie_id, name, genre);
        hashRatings[movie_id] = a;
        trieMovies.insert(cl.clear_string(name), a);
        
        for(int i=0; i < (int) genre.size(); i++){
            if(!hashGenres.search(genre[i])){
                hashGenres[genre[i]] = new Genre(genre[i]);
            }
            
            hashGenres[genre[i]]->addMovie(a);
        }
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
    tags.open("tag.csv", ios::in);

    getline(tags, temp);

    while(getline(tags, temp)){

        stringstream s(temp);
        string word;
        
        getline(s, word, ',');
        getline(s, word, ',');
        
        int movieId = stoi(word);

        getline(s, word, '"'); //ignora o primeiro pra poder pegar o nome do filme limpo
        getline(s, word, '"');
        string tag = word;

        if(!hashTags.search(cl.clear_string(tag))){
            hashTags[cl.clear_string(tag)] = new Tag(tag, cl.clear_string(tag));
        }
        
        hashTags[cl.clear_string(tag)]->addMovie(hashRatings[movieId]);
    }

    // TODO: revisar modo de linha de comando
    // TODO: limpar arquivo de tag / ler de forma correta a tag
    
    cout << "TA TUDO CARREGADO. LETs DALE" << endl;

    while(true){
        string entrada;
        string option;      // movie, user, top or tag

        cout << "\n\nO que deseja fazer? " << flush;

        getline(cin, entrada);
        stringstream linha_terminal(entrada);

        getline(linha_terminal, option, ' ');   
        /////////////////////////////////////////////////////////////////////////////////
        if(option.compare("movie") == 0){

            getline(linha_terminal, option);

            vector<Movie*> key = trieMovies.searchPrefix(cl.clear_string(option));

            cout << "Movie Id" << '\t' << "Title"<< '\t' << "Genres" << '\t' << "Rating" << '\t' << "Counting"<< endl;
            cout <<"---------------------------------------------------------------------"<< endl;

            for(int i=0; i < (int)key.size(); i++){

                cout << key[i]->id <<'\t' << key[i]->name << '\t';

                for(int j=0; j < (int)key[i]->genres.size(); j++){
                    cout << key[i]->genres[j] << "|";
                }

                int rate = key[i]->num_ratings != 0 ? (key[i]->sum_ratings)/(key[i]->num_ratings) : 0;
                cout << rate << '\t' << key[i]->num_ratings << endl;
            }
        }
        /////////////////////////////////////////////////////////////////////////////////
        else if (option.compare("user") == 0){
        
            getline(linha_terminal, option);
            cout << "Title"<<'\t'<< "User Rating"<< '\t'<< "Global Rating"<<'\t'<< "Counting"<< endl;
            cout <<"---------------------------------------------------------------------"<< endl;
            int user_id = stoi(option);
            vector<pair<Movie*, double>> movies = hashUsers[user_id]->ratings;
            for(int i=0; i < (int) movies.size(); i++){
            
                cout << movies[i].first->name << '\t';
                cout << movies[i].second <<'\t';
                
                int rate = movies[i].first->num_ratings != 0 ? (movies[i].first->sum_ratings)/(movies[i].first->num_ratings) : 0;
                cout << rate << '\t' << movies[i].first->num_ratings << endl;

            }
        }
        /////////////////////////////////////////////////////////////////////////////////
        else if (option.substr(0,3).compare("top") == 0){
            //TODO: make an option to filter movies with at least N numbers of ratings
            int n = stoi(option.substr(3,option.size()-3));
            getline(linha_terminal, option);
            if(hashGenres.search(option)){   
                for(auto a: hashGenres[option]->getTop(n)){
                    cout << a->toString() << endl;
                }
                
            } else {
                cout << "Nenhum gênero encontrado com este nome" << endl;
            }
            //ranking dos filmes de um genero
        }
        /////////////////////////////////////////////////////////////////////////////////
        else if(option.compare("tag") == 0){
            //lista os filme com a tag dada
            vector<string> tags;
            getline(linha_terminal, option, '"');
            while(getline(linha_terminal, option, '"')){
                tags.push_back(cl.clear_string(option));
                getline(linha_terminal, option, '"');
            }
            
            vector<Movie*> ans;
            if(hashTags.search(tags[0])){
                ans = hashTags[tags[0]]->movies;

                for(int i=1; i < (int)tags.size(); i++){
                    if(hashTags.search(tags[i])){
                        ans = hashTags[tags[i]]->getIntersection(ans);
                    } else {
                        ans.clear();
                        break;
                    }
                }
            }
            cout << "size: " << ans.size() << endl;
            if(ans.size() == 0){
                cout << "Não foram encontrados resultado." << endl;
            } else {
                for(int i=0; i < (int)ans.size(); i++){
                    cout << ans[i]->toString() << endl;
                }
            }
        }
        /////////////////////////////////////////////////////////////////////////////////
        else if(option.compare("exit") == 0){
            break;
        }
    }

    return 0;
}


