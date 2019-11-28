#include <bits/stdc++.h>

using namespace std;
const int ALPHABET_SIZE = 256;

template <class K>
class TrieNode {
public:
    TrieNode<K> *children[ALPHABET_SIZE];
    bool isEndOfWord;
    K *data;
    
    TrieNode();
}; 

template <class K>
class Trie {
public:
    TrieNode<K> *rootNode;
    
    Trie();
    TrieNode<K> *getNode();    
    void insert(string key, K data);
    void search(string key);
};

#include "../Trie.cpp"
