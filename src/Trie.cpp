template<class K>
Trie<K>::Trie() {
    for(int i=0; i < ALPHABET_SIZE; i++){
        children[i] = NULL;
    }
}

template<class K>
struct TrieNode<K>* Trie<K>::getNode(){
    struct TrieNode<K> *pNode = new TrieNode<K>;

    pNode->data = NULL;
    pNode->isEndOfWord = false;

    for (int i = 0; i < ALPHABET_SIZE; i++){
        pNode->children[i] = NULL;
    }
    
    return pNode;
}

template<class K>
void Trie<K>::insert(string key, K data){
    auto pCrawl = children;

    for (int i = 0; i < key.length(); i++){
        int index = key[i]; // ASCII do char
        if (pCrawl[index] == NULL){
            pCrawl[index] = getNode();
        }
        pCrawl = pCrawl[index]->children;
    }
}

template<class K>
void Trie<K>::search(string key){
    auto pCrawl = children;

    for (int i = 0; i < key.length(); i++){
        int index = key[i];
        if (pCrawl[index] == NULL){
            cout << "nao achou" << endl;
            return;
        }
        cout << key[i];
        pCrawl = pCrawl[index]->children;
    }
    //return (pCrawl->data);
}
