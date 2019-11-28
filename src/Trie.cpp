template<class K>
TrieNode<K>::TrieNode(){
    data = NULL;
    isEndOfWord = false;
    
    for(int i=0; i < ALPHABET_SIZE; i++){
        children[i] = NULL;
    }
}

template<class K>
Trie<K>::Trie() {
    rootNode = getNode();
}

template<class K>
TrieNode<K>* Trie<K>::getNode(){
    TrieNode<K>* n = new TrieNode<K>();
    return n;  
}

template<class K>
void Trie<K>::insert(string key, K data){
    auto pCrawl = rootNode->children;

    for (int i = 0; i < key.length(); i++){
        int index = key[i]; // ASCII do char
        if (pCrawl[index] == NULL){
            pCrawl[index] = getNode();
        }
        pCrawl = pCrawl[index]->children;
    }
    //pCrawl->data = NULL;
}

template<class K>
void Trie<K>::search(string key){
    auto pCrawl = rootNode->children;

    for (int i = 0; i < key.length(); i++){
        int index = key[i];
        if (pCrawl[index] == NULL){
            cout << "nao achou" << endl;
            return;
        }
        cout << key[i];
        pCrawl = pCrawl[index]->children;
    }
    //cout << (pCrawl->isEndOfWord) << endl;
    //return (pCrawl->data);
}
