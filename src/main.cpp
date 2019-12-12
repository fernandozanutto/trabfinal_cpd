#include <istream>
#include <ostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <QApplication>
#include "Movie.cpp"
#include "mainwindow.h"

using namespace std;

int main(int argc, char *argv[]) {

    const int MAX_LENGTH = 500;
    char* line = new char[MAX_LENGTH];
    clock_t begin = clock();

    Hash<Movie> hashRatings(5807); // ~27k movies
    Hash<User> hashUsers(27701); // ~138k users
    Hash<Tag> hashTags(90000); // ~490k entries
    Hash<Genre> hashGenres(5); // 20 genres
    Trie trieMovies;
    ClearString cl;
    string temp, name, word;
    int movieId, userId;
    double r;
    
    string help_message = "\nComandos: \
    \nmovie <prefix> - Procura por todos os filmes com o prefixo inserido \
    \ntop<N> <genre> [min] - procura pelos filmes melhores avaliados de um dado genero, podendo filtrar apenas os que tem um mínimo de notas recebidas \
    \ntag \"<tag>\" - procura pelos filmes que tenham as tags fornecidas (escrever as tags entre aspas) \
    \nuser <ID> - procura pelos filmes que o usuario avaliou\
    \nhelp - exibe esta mensagem";
    
    cout << "Carregando movie.csv" << endl;

    filebuf fb;
    fb.open ("movie.csv",ios::in);
    istream movieStream(&fb);

    movieStream.getline(line, MAX_LENGTH);
    while (movieStream.getline(line, MAX_LENGTH) && strlen(line) > 0) {

        stringstream s(line);

        getline(s, word, ',');
        movieId = stoi(word);

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

        Movie* a = new Movie(movieId, name, genre);
        hashRatings[movieId] = a;
        trieMovies.insert(cl.clear_string(name), a);
        
        for(int i=0; i < (int) genre.size(); i++){
            if(!hashGenres.search(cl.clear_string(genre[i]))){
                hashGenres[cl.clear_string(genre[i])] = new Genre(genre[i], cl.clear_string(genre[i]));
            }
            
            hashGenres[cl.clear_string(genre[i])]->addMovie(a);
        }
    }

    
    cout << "Carregando rating.csv" << endl;
    fb.close();
    fb.open ("rating.csv",ios::in);
    istream ratingStream(&fb);

    ratingStream.getline(line, MAX_LENGTH);
    while (ratingStream.getline(line, MAX_LENGTH)) {
        stringstream s(line);

        getline(s, word, ',');

        userId = stoi(word);
        getline(s, word, ',');
        movieId = stoi(word);
        getline(s, word, ',');
        r = stod(word);

        Movie* m = hashRatings[movieId];

        ++m->num_ratings;
        m->sum_ratings += r;

        if(!hashUsers.search(userId)){
            hashUsers[userId] = new User(userId);
        }

        hashUsers[userId]->addMovie(m, r);
    }


    cout << "Carregando tag.csv" << endl;
    fb.close();
    fb.open ("tag.csv", ios::in);
    istream tagStream(&fb);
    tagStream.getline(line, MAX_LENGTH);
    while (tagStream.getline(line, MAX_LENGTH)) {

        stringstream s(line);

        getline(s, word, ',');
        getline(s, word, ',');
        
        movieId = stoi(word);

        getline(s, word, '"'); //ignora o primeiro pra poder pegar o nome do filme limpo
        getline(s, word, '"');
        string tag = word;

        if(!hashTags.search(cl.clear_string(tag))){
            hashTags[cl.clear_string(tag)] = new Tag(tag, cl.clear_string(tag));
        }
        
        hashTags[cl.clear_string(tag)]->addMovie(hashRatings[movieId]);
    }
    
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    
    cout << "Tempo para iniciar programa: " << elapsed_secs << " segundos" << endl;

    QApplication a(argc, argv);
    MainWindow w;

    w.load(&hashRatings, &hashUsers, &hashTags, &hashGenres, &trieMovies, &cl);
    w.show();

    return a.exec();
}

