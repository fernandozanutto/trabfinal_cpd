#include <bits/stdc++.h>

using namespace std;
const int ALPHABET_SIZE = 256;

template <class K>
struct TrieNode {
    struct TrieNode<K> *children[ALPHABET_SIZE];
    bool isEndOfWord;
    K *data;
}; 

template <class K>
class Trie {
public:
    struct TrieNode<K> *getNode();
    struct TrieNode<K> *children[ALPHABET_SIZE];
    

    Trie();
    
    void insert(string key, K data);
    void search(string key);
};

#include "../Trie.cpp"
