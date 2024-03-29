#include "header/Trie.h"

TrieNode::TrieNode(){
    movie = NULL;
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

void Trie::insert(string key, Movie* movie){
    auto pCrawl = rootNode;

    for (int i = 0; i < (int)key.length(); i++){

        int index = tolower(key[i]) - ' ';

        if (pCrawl->children[index] == NULL){
            pCrawl->children[index] = newNode();
        }
        pCrawl = pCrawl->children[index];
    }
    pCrawl->movie = movie;
}


Movie* Trie::search(string key){
    auto pCrawl = rootNode;

    for (int i = 0; i < (int)key.length(); i++){
        int index = tolower(key[i]) - ' ';
        if (pCrawl->children[index] == NULL){
            return NULL;
        }
        pCrawl = pCrawl->children[index];
    }
    return pCrawl->movie;
}


void dfs(vector<Movie*> &ans, TrieNode* node){

    if(node->movie != NULL){
        ans.push_back(node->movie);
    }
    
    for(int i=0; i < ALPHABET_SIZE; i++){
    
        if(node->children[i] != NULL){
            dfs(ans, node->children[i]);
        }
    }
}

vector<Movie*> Trie::searchPrefix(string key){
    auto pCrawl = rootNode;
    
    vector<Movie*> ans;
    
    for (int i = 0; i < (int)key.length(); i++){

        int index = tolower(key[i]) - ' '; // ASCII do char
        if (pCrawl->children[index] == NULL){
            return ans;
        }
        pCrawl = pCrawl->children[index];
    }
    
    dfs(ans, pCrawl);
    
    return ans;
}



