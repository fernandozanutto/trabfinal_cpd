#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include "header/Hash.h"
#include "header/User.h"
#include "header/Movie.h"
#include "header/Trie.h"
#include "header/Tag.h"
#include "header/Genre.h"
#include "header/ClearString.h"

using namespace std;


int main() {
    clock_t begin = clock();

    Hash<Movie> hashRatings(5807); // ~27k movies
    Hash<User> hashUsers(27701); // ~138k users
    Hash<Tag> hashTags(90000); // ~490k entries
    Hash<Genre> hashGenres(5); // 20 genres
    Trie trieMovies;
    ClearString cl;
    string temp, name;
    
    string help_message = "\nComandos: \
    \nmovie <prefix> - Procura por todos os filmes com o prefixo inserido \
    \ntop<N> <genre> [min] - procura pelos filmes melhores avaliados de um dado genero, podendo filtrar apenas os que tem um mínimo de notas recebidas \
    \ntag \"<tag>\" - procura pelos filmes que tenham as tags fornecidas (escrever as tags entre aspas) \
    \nuser <ID> - procura pelos filmes que o usuario avaliou\
    \nhelp - exibe esta mensagem";
    
    
    cout << "Carregando movie.csv" << endl;
    fstream movie_file;
    movie_file.open("movie.csv", ios::in);
    
    getline(movie_file,temp);
    while(getline(movie_file, temp)){

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
                hashGenres[cl.clear_string(genre[i])] = new Genre(genre[i], cl.clear_string(genre[i]));
            }
            
            hashGenres[cl.clear_string(genre[i])]->addMovie(a);
        }
    }
    movie_file.close();
    
    cout << "Carregando rating.csv" << endl;
    fstream rating_file;
    rating_file.open("rating.csv", ios::in);
    getline(rating_file, temp);

    while(getline(rating_file, temp)){

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
    rating_file.close();

    cout << "Carregando tag.csv" << endl;
    fstream tag_file;
    tag_file.open("tag.csv", ios::in);
    getline(tag_file, temp);

    while(getline(tag_file, temp)){

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
    tag_file.close();

    // TODO: revisar linha de comando e se tudo esta funcionando
    
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    
    cout << "Tempo para iniciar programa: " << elapsed_secs << " segundos" << endl;
    
    
    cout << help_message << endl;
    while(true){
        string entrada;
        string option; // movie, user, top or tag

        cout << "\n\nO que deseja fazer? " << flush;

        getline(cin, entrada);
        stringstream linha_terminal(entrada);

        getline(linha_terminal, option, ' ');   
        /////////////////////////////////////////////////////////////////////////////////
        if(option.compare("movie") == 0){

            getline(linha_terminal, option);

            vector<Movie*> key = trieMovies.searchPrefix(cl.clear_string(option));

            cout << "ID" << '\t' << "Title" << "\t\t\t\t\t\t\t" << "Genres" << "\t\t\t\t\t\t\t\t\t" << "Av. Rating" << '\t' << "Rating Count"<< endl;
            cout << "---------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

            for(int i=0; i < (int)key.size(); i++){
                ostringstream buffer;
                
                buffer << key[i]->id << "\t";
                buffer << (key[i]->name.size() > 48 ? (key[i]->name.substr(0,45) + "...") : key[i]->name) << "\t";
                
                if(key[i]->name.size() < 48){
                    int m = ceil(6 - key[i]->name.size()/8.0);
                    for(int i=0; i < m; i++){
                        buffer << "\t";
                    }
                }
                
                int j;
                int temp = 0;
                
                for(j=0; j < (int)key[i]->genres.size()-1; j++){
                    buffer << key[i]->genres[j] << "|";
                    temp += key[i]->genres[j].size()+1;
                }
                buffer << key[i]->genres[j] << "\t";
                temp += key[i]->genres[j].size();
                
                if(temp < 64){
                    for(int i=0; i < ceil((64-temp)/8.0); i++)
                        buffer << "\t";
                }
                
                int rate = key[i]->num_ratings != 0 ? (key[i]->sum_ratings)/(key[i]->num_ratings) : 0;
                buffer << rate << "\t\t" << key[i]->num_ratings;
                
                
                cout << buffer.str() << endl;
            }

        }
        /////////////////////////////////////////////////////////////////////////////////
        else if (option.compare("user") == 0){
        
            getline(linha_terminal, option);
            cout << "Title" << "\t\t\t\t\t\t\t" << "User Rating" << "\t" << "Av. Global Rating" << '\t' << "Rating Count"<< endl;
            cout << "------------------------------------------------------------------------------------------------------------" << endl;
            int user_id = stoi(option);
            
            if(hashUsers.search(user_id)){
                vector<pair<Movie*, double>> movies = hashUsers[user_id]->ratings;
                
               
                int i,j;
                for(i=1; i < (int) movies.size(); i++){
                    for(j=0; j < i; j++){
                        if(movies[i].first->name.compare(movies[j].first->name) < 0){
                            break;
                        }
                    }
                    
                    int x = i;
                    while(x > j){
                        pair<Movie*, double> temp = movies[x];
                        movies[x] = movies[x-1];
                        movies[x-1] = temp;
                        --x;
                    }
                }
                
                for(int i=0; i < (int) movies.size(); i++){
                    ostringstream buffer;
                    
                    buffer << (movies[i].first->name.size() > 48 ? (movies[i].first->name.substr(0,46) + "...") : movies[i].first->name) << "\t";
                    
                    if(movies[i].first->name.size() < 48){
                        int m = ceil((48 - movies[i].first->name.size())/8.0);
                        for(int i=0; i < m; i++){
                            buffer << "\t";
                        }
                    }
                    
                    buffer << movies[i].second << "\t\t";
                    
                    double rate = movies[i].first->num_ratings != 0 ? (movies[i].first->sum_ratings)/(movies[i].first->num_ratings) : 0;
                    buffer << rate << "\t\t\t" << movies[i].first->num_ratings << endl;
                
                    cout << buffer.str();
                }
            } else {
                cout << "Usuario nao encontrado." << endl;
            }
        }
        /////////////////////////////////////////////////////////////////////////////////
        else if (option.size() > 3 && option.substr(0,3).compare("top") == 0){
            cout << "Title" << "\t\t\t\t\t\t\t" << "Genres" << "\t\t\t\t\t\t\t\t\t" << "Av. Rating" << "\t" << "Rating Count"<< endl;
            cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
            int n = stoi(option.substr(3,option.size()-3));
            int min = 0;
            getline(linha_terminal, option, ' ');
            string genre = option;

            getline(linha_terminal, option, ' ');

            if(option != genre){
                min = stoi(option);
            }
            
            genre = cl.clear_string(genre);
            if(hashGenres.search(genre)){
            
                for(Movie* movie: hashGenres[genre]->getTop(n, min)){
                    ostringstream buffer;
                    
                    buffer << (movie->name.size() > 48 ? (movie->name.substr(0,45) + "...") : movie->name) << "\t";
                
                    if(movie->name.size() < 48){
                        int m = ceil(6 - movie->name.size()/8.0);
                        for(int i=0; i < m; i++){
                            buffer << "\t";
                        }
                    }
                    
                    int j;
                    int temp = 0;
                    
                    for(j=0; j < (int)movie->genres.size()-1; j++){
                        buffer << movie->genres[j] << "|";
                        temp += movie->genres[j].size()+1;
                    }
                    
                    buffer << movie->genres[j] << "\t";
                    temp += movie->genres[j].size();
                    
                    if(temp < 64){
                        for(int i=0; i < ceil((64-temp)/8.0); i++)
                            buffer << "\t";
                    }
                    
                    double rate = movie->num_ratings != 0 ? (movie->sum_ratings)/(movie->num_ratings) : 0;
                    buffer << rate << "\t\t" << movie->num_ratings << endl;
                    
                    cout << buffer.str();
                }
                
            } else {
                cout << "Nenhum genero encontrado com este nome" << endl;
            }
        }
        /////////////////////////////////////////////////////////////////////////////////
        else if(option.substr(0,3).compare("tag") == 0){
            cout << "Title" << "\t\t\t\t\t\t\t" << "Genres" << "\t\t\t\t\t\t\t\t\t" << "Av. Rating" << "\t" << "Rating Count"<< endl;
            cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
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
            
            if(ans.size() == 0){
                cout << "Nao foram encontrados resultados." << endl;
            } else {
            
            
                int i,j;
                for(i=1; i < (int) ans.size(); i++){
                    for(j=0; j < i; j++){
                        if(ans[i]->name.compare(ans[j]->name) < 0){
                            break;
                        }
                    }
                    
                    int x = i;
                    while(x > j){
                        Movie *temp = ans[x];
                        ans[x] = ans[x-1];
                        ans[x-1] = temp;
                        --x;
                    }
                }
            
            
                for(int i=0; i < (int) ans.size(); i++){
                    ostringstream buffer;
                    Movie *movie = ans[i];
                    
                    buffer << (movie->name.size() > 48 ? (movie->name.substr(0,45) + "...") : movie->name) << "\t";
                
                    if(movie->name.size() < 48){
                        int m = ceil(6 - movie->name.size()/8.0);
                        for(int i=0; i < m; i++){
                            buffer << "\t";
                        }
                    }
                    
                    int j;
                    int temp = 0;
                    
                    for(j=0; j < (int)movie->genres.size()-1; j++){
                        buffer << movie->genres[j] << "|";
                        temp += movie->genres[j].size()+1;
                    }
                    
                    buffer << movie->genres[j] << "\t";
                    temp += movie->genres[j].size();
                    
                    if(temp < 64){
                        for(int i=0; i < ceil((64-temp)/8.0); i++)
                            buffer << "\t";
                    }
                    
                    double rate = movie->num_ratings != 0 ? (movie->sum_ratings)/(movie->num_ratings) : 0;
                    buffer << rate << "\t\t" << movie->num_ratings << endl;
                    
                    cout << buffer.str();
                }
            }
        }
        /////////////////////////////////////////////////////////////////////////////////
        else if(option.compare("exit") == 0){
            break;
        } else if(option.compare("help") == 0){
            cout << help_message << endl;
        }
    }

    return 0;
}


