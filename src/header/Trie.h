#include <bits/stdc++.h>

using namespace std;
const int ALPHABET_SIZE = 256;

template <class K>
struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    bool isEndOfWord;
    K *data;
}; 

template <class K>
class Trie {
private:
    struct TrieNone *getNode();
    
public:
    struct TrieNode *children[ALPHABET_SIZE];
    
    void insert(string key, K data);
    K *search(string key);
};

#include "../Trie.cpp"
