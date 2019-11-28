#include <bits/stdc++.h>
#include <boost/algorithm/string.hpp>
using namespace std;


int main(){

    /*Loading movies
    */
   Trie films
   fstream movie_trie;
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

   }
    /*
    Loading movies rating
    */
    Hash<Movie> hashRatings(5471); // ~27k movies
    Hash<User> hashUsers(1000);

    fstream rating;
    rating.open("minirating.csv", ios::in);
    string temp;
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

        hashRatings[movieId].num_ratings += 1;
        hashRatings[movieId].sum_ratings += r;

        hashUsers[userId].ratings.push_back({movieId, r});

        //cout << hashRatings[movieId].toString() << endl;
    }

    return 0;

}
