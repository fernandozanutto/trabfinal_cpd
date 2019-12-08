#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "header/Hash.h"
#include "header/User.h"
#include "header/Movie.h"
#include "header/Trie.h"
#include "header/Tag.h"
#include "header/Genre.h"
#include "header/ClearString.h"

using namespace std;

#include <ctime>

int main(){

    clock_t begin = clock();
 
    Hash<Movie> hashRatings(5807); // ~27k movies
    Hash<User> hashUsers(27701); // ~138k users
    Hash<Tag> hashTags(90000); // ~490k entries
    Hash<Genre> hashGenres(5); // 20 genres
    Trie trieMovies;
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
    int tagsss= 0;
    while(getline(tags, temp)){

        stringstream s(temp);
        string word;
        
        getline(s, word, ',');
        getline(s, word, ',');
        
        int movieId = stoi(word);

        getline(s, word, '"'); //ignora o primeiro pra poder pegar o nome do filme limpo
        getline(s, word, '"');
        string tag = word;
        string cleartag = cl.clear_string(tag);
        
        if(!hashTags.search(cl.clear_string(tag))){
            tagsss++;
            hashTags[cleartag] = new Tag(tag, cleartag);
        }
        
        hashTags[cleartag]->addMovie(hashRatings[movieId]);
    }
    
    // TODO: revisar linha de comando e se tudo esta funcionando
    
    cout << "TA TUDO CARREGADO. LETs DALE" << endl;
    
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    
    cout << "Time: " << elapsed_secs << " segundos" << endl;
    
    return 0;
}
