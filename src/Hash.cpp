template <class K>
Hash<K>::Hash(int s){
    size = s;
    table.assign(s, vector<K*>());
}


template <class K>
int Hash<K>::hashFunction(int key) {
    key = (key ^ 61) ^ (key >> 16);
    key = key + (key << 3);
    key = key ^ (key >> 4);
    key = key * 0x27d4eb2d; // a prime or an odd constant
    key = key ^ (key >> 15);

    return key % size;
}

template <class K>
int Hash<K>::hashFunction(string x) {

    int hash = 0;
    int p = 1;
    for(int i=0; i < (int) x.size(); i++){

        hash = (hash + (((x[i] - ' ') * p) % size)) % size;
        p = (p * PRIME) % size;
    }

    return hash % size;
}


template <class K>
void Hash<K>::insert(K* s){
    int pos = hashFunction(s->getIdentifier());
    table[pos].push_back(s);
}

template <class K>
bool Hash<K>::search(int s){
    int pos = hashFunction(s);
    
    for(int i=0; i < (int)table[pos].size(); i++){
        if(s == table[pos][i]->getIdentifier())
            return true;
    }
    return false;
}

template <class K>
bool Hash<K>::search(string s){
    int pos = hashFunction(s);
    
    for(int i=0; i < (int)table[pos].size(); i++){
        if(s == table[pos][i]->getIdentifier())
            return true;
    }
    return false;
}

template <class K>
K* &Hash<K>::operator[](int index){
    int pos = hashFunction(index);

    if (table[pos].size() == 0){
        table[pos].push_back(NULL);
        return table[pos][0];
    } else {
        int i;
        for(i=0; i < (int)table[pos].size(); i++){
            if(table[pos][i]->getIdentifier() == index){
                return table[pos][i];
            }
            
        }

        table[pos].push_back(NULL);
        return table[pos][i];
    }
}


template <class K>
K* &Hash<K>::operator[](string index){
    int pos = hashFunction(index);

    if (table[pos].size() == 0){
        table[pos].push_back(NULL);
        return table[pos][0];
    } else {
        int i;
        for(i=0; i < (int)table[pos].size(); i++){
            if(table[pos][i]->getIdentifier() == index){
                return table[pos][i];
            }
        }

        table[pos].push_back(NULL);
        return table[pos][i];
    }
}

