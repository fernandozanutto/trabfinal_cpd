struct TrieNone* Trie<K>::getNode(){
    struct TrieNone *pNode = new TrieNode;

    pNode->data = NULL;
    pNode->isEndOfWord = false;

    for (int i = 0; i < ALPHABET_SIZE; i++){
        pNode->children[i] = NULL;
    }
    
    return pNode;
}

void Trie<K>::insert(string key, K data){
    TrieNone *pCrawl = this.children;

    for (int i = 0; i < key.length(); i++){
        int index = key[i]; // ASCII do char
        if (!pCrawl[index]){
            pCrawl[index] = getNode();
        }
        pCrawl = pCrawl[index]->children;
    }
}

K Trie<K>::search(string key){
    TrieNode *pCrawl = this.children;

    for (int i = 0; i < key.length(); i++){
        int index = key[i];
        if (!pCrawl[index]){
            return false;
        }
        pCrawl = pCrawl->children[index];
    }
    return (pCrawl);
}
