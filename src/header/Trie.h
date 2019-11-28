#include <string>
#include <cctype>
using namespace std;

const int ALPHABET_SIZE = 256;

class TrieNode {
public:
    TrieNode *children[ALPHABET_SIZE];
    bool isEndOfWord;
    int movieId;
    TrieNode();
}; 


class Trie {
public:
    TrieNode *rootNode;
    
    Trie();
    TrieNode *getNode();    
    void insert(string key, int id);
    int search(string key);
};
