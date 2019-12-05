#include <string>
#include <cctype>
#include <iostream>
#include <vector>
#include "Movie.h"
using namespace std;

const int ALPHABET_SIZE = 96;

class TrieNode {
public:
    TrieNode *children[ALPHABET_SIZE];
    bool isEndOfWord;
    Movie *movie;
    TrieNode();
}; 


class Trie {
private:
    TrieNode *rootNode;
    TrieNode *newNode();    
public:    
    Trie();
    void insert(string key, Movie *movie);
    Movie* search(string key);
    vector<Movie*> searchPrefix(string key);
};

