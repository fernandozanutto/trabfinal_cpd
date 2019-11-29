#include "header/Trie.h"

TrieNode::TrieNode(){
    isEndOfWord = false;
    
    for(int i=0; i < ALPHABET_SIZE; i++){
        children[i] = NULL;
    }
}


Trie::Trie() {
    rootNode = newNode();
}


TrieNode* Trie::newNode(){
    TrieNode* n = new TrieNode();
    return n; 
}

void Trie::insert(string key, int id){
    auto pCrawl = rootNode;

    for (int i = 0; i < key.length(); i++){

        int index = tolower(key[i]); // ASCII do char
        if (pCrawl->children[index] == NULL){
            pCrawl->children[index] = newNode();
        }
        pCrawl = pCrawl->children[index];
    }
    
    pCrawl->isEndOfWord = true;
    pCrawl->movieId = id;
}


int Trie::search(string key){
    auto pCrawl = rootNode;

    for (int i = 0; i < key.length(); i++){
        int index = tolower(key[i]);
        if (pCrawl->children[index] == NULL){
            return -1;
        }
        pCrawl = pCrawl->children[index];
    }
    if(pCrawl->isEndOfWord)
        return pCrawl->movieId;
    else
        return -1;
}


vector<int> Trie::searchPrefix(string key){
    auto pCrawl = rootNode;
    
    vector<int> ans;
    
    for (int i = 0; i < key.length(); i++){

        int index = tolower(key[i]); // ASCII do char
        if (pCrawl->children[index] == NULL){
            return ans;
        }
        pCrawl = pCrawl->children[index];
    }
    
    stack<int> stack;
    
    
    

}



