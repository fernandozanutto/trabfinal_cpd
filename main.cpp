#include <bits/stdc++.h>
#include <boost/algorithm/string.hpp>
using namespace std;


class User  {
public:
    int id;

    User(int _id){
        id = _id;
    }

    vector<pair<int,int>> ratings; // pair <movieId, rating>
};

class Movie {
public:
    string name; // fiz essas modificações para poder usar com a trie ja dai
    string genres;
    int id;
    int num_ratings;
    double sum_ratings;

    Movie(int _id){
        id = _id;
        num_ratings = 0;
        sum_ratings = 0;
    }

    Movie(int _id, int _n, double _r){
        id = _id;
        num_ratings = _n;
        sum_ratings = _r;
    }

    const string toString() const {
        ostringstream buffer;

        buffer << "ID: " << id << " Num ratings: " << num_ratings << " Soma: " << sum_ratings << endl;
        return buffer.str();
    }

};

template <class K>
class Hash {

private:

    int size;
    vector<vector<K>> table;

public:
    Hash(int s){
        size = s;
        table.assign(s, vector<K>());
    }

    int hashFunction(int x) {
        x = ((x >> 16) ^ x) * 0x45d9f3b;
        x = ((x >> 16) ^ x) * 0x45d9f3b;
        x = (x >> 16) ^ x;

        return x % size;
    }

    void insert(K s){
        int pos = hashFunction(s.getIdentifier());
        table[pos].push_back(s);
    }

    int search(int s){
        int pos = hashFunction(s);

        for(int i=0; i < table[pos].size(); i++){
            if(s == table[pos][i])
                return table[pos][i];
        }
        return -1;
    }

    K &operator[](int index){
        int pos = hashFunction(index);

        if (table[pos].size() == 0){

            K novo(index);
            table[pos].push_back(novo);
            return table[pos][0];
        } else {
            int i;
            for(i=0; i < table[pos].size(); i++){
                if(table[pos][i].id == index){
                    return table[pos][i];
                }
            }

            table[pos].push_back(K(index));
            return table[pos][i];
        }
    }
};
const int ALPHABET_SIZE = 26;

class Trie
{
public:
    Trie *children[ALPHABET_SIZE+1];// acho q tem q botar +1 por causa dos espaços q possivelmente tem no nome
    Movie film;
    /* string name;
    int movie_id; // movie id vai servir pra dizer se é uma palavra ou nao
    string genre;   //string com todos os generos q o filme tem separados por virgula
    */
    Trie *getNode(void)
    {
        Trie *pNode = new TrieNode;

        pNode->film.id = 0;

        for (int i = 0; i < ALPHABET_SIZE; i++)
            pNode->children[i] = NULL;

        return pNode;
    }
    void insert(Trie *root, string key, int id, string gen)
    {
        Trie *pCrawl = root;

        for (int i = 0; i < key.length(); i++)
        {
            int index = key[i] - 'a';
            if (!pCrawl->children[index])
                pCrawl->children[index] = getNode();

            pCrawl = pCrawl->children[index];
        }

        pCrawl->film.id = id;
        strcpy(gen, pCrawl->film.genre);
    }
    bool search(struct TrieNode *root, string key)
    {
        Trie *pCrawl = root;

        for (int i = 0; i < key.length(); i++)
        {
            int index = key[i] - 'a';
            if (!pCrawl->children[index])
                return false;

            pCrawl = pCrawl->children[index];
        }

        return (pCrawl != NULL && pCrawl->movie_id);
    }
};
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
