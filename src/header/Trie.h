#include <string>
#include <cctype>
#include <vector>
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
private:
    TrieNode *rootNode;
    TrieNode *newNode();    
public:    
    Trie();
    void insert(string key, int id);
    int search(string key);
    vector<pair<string,int>> searchPrefix(string key);
};
