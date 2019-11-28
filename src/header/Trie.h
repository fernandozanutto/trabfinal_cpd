#include <string>

using namespace std;

const int ALPHABET_SIZE = 256;

class TrieNode {
public:
    TrieNode *children[ALPHABET_SIZE];
    bool isEndOfWord;
    
    TrieNode();
}; 


class Trie {
public:
    TrieNode *rootNode;
    
    Trie();
    TrieNode *getNode();    
    void insert(string key);
    bool search(string key);
};
