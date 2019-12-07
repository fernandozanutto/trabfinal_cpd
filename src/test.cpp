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
      
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    /*
    Loading movies rating
    */
    Hash<Movie> hashRatings(5807); // ~27k movies
    Hash<User> hashUsers(27701); // ~138k users
    Trie trieMovies;
    Hash<Tag> hashTags(90000); // ~490k entries
    Hash<Genre> hashGenres(5000); // no ideia how many different genres there are
    
    /*
    Loading movies
    */
    fstream movie_trie;
    movie_trie.open("movie_clean.csv", ios::in);
    string temp, name;
    
    getline(movie_trie,temp);
    cout << "lendo filmes" << endl;
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
        trieMovies.insert(name, a);
        
        for(int i=0; i < (int) genre.size(); i++){
            if(!hashGenres.search(genre[i])){
                hashGenres[genre[i]] = new Genre(genre[i]);
            }
            
            hashGenres[genre[i]]->addMovie(a);
        }
    }
    
    fstream rating;
    rating.open("minirating.csv", ios::in);
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
    
    for(auto a: hashGenres["War"]->getTop(15)){
        cout << a->toString() << endl;
    }
    
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    
    cout << "Time: " << elapsed_secs << " segundos" << endl;
    
    return 0;
}
