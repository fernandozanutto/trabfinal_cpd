#include "header/Trie.h"

TrieNode::TrieNode(){
    movieId = -1;
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
    return pCrawl->movieId;
}


void dfs(vector<pair<string,int>> &ans, TrieNode* node, string key){

    if(node->movieId != -1){
        ans.push_back({key, node->movieId});
    }
    
    for(int i=0; i < ALPHABET_SIZE; i++){
    
        if(node->children[i] != NULL){
            dfs(ans, node->children[i], key+(char)i);
        }
    }
    
}

vector<pair<string,int>> Trie::searchPrefix(string key){
    auto pCrawl = rootNode;
    
    vector<pair<string,int>> ans;
    
    for (int i = 0; i < key.length(); i++){

        int index = tolower(key[i]); // ASCII do char
        if (pCrawl->children[index] == NULL){
            return ans;
        }
        pCrawl = pCrawl->children[index];
    }
    
    dfs(ans, pCrawl, key);
    
    return ans;
}



