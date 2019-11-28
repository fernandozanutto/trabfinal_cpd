#include "header/Trie.h"

TrieNode::TrieNode(){
    isEndOfWord = false;
    
    for(int i=0; i < ALPHABET_SIZE; i++){
        children[i] = NULL;
    }
}


Trie::Trie() {
    rootNode = getNode();
}


TrieNode* Trie::getNode(){
    TrieNode* n = new TrieNode();
    return n; 
}


void Trie::insert(string key){
    auto pCrawl = rootNode;

    for (int i = 0; i < key.length(); i++){

        int index = tolower(key[i]); // ASCII do char
        if (pCrawl->children[index] == NULL){
            pCrawl->children[index] = getNode();
        }
        pCrawl = pCrawl->children[index];
    }
    
    pCrawl->isEndOfWord = true;
}


bool Trie::search(string key){
    auto pCrawl = rootNode;

    for (int i = 0; i < key.length(); i++){
        int index = tolower(key[i]);
        if (pCrawl->children[index] == NULL){
            return false;
        }
        pCrawl = pCrawl->children[index];
    }
    return pCrawl->isEndOfWord;
}
