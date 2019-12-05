template <class K>
Hash<K>::Hash(int s){
    size = s;
    table.assign(s, vector<K*>());
}


template <class K>
int Hash<K>::hashFunction(int x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;

    return x % size;
}


int exp(int a, int b){
    cout << a << " " << b << endl;
    if(b == 0) return 1;
    if(b == 1) return a;

    int res = exp(a, b>>1);
    res = res * res;
    
    if(b & 1) res = res * a;
        
    return res;
}

template <class K>
int Hash<K>::hashFunction(string x) {
    int hash = 0;
    
    for(int i=0; i < (int)x.size(); i++){
        hash = (hash + ((x[i] - ' ') * exp(PRIME, i)) % size) % size;
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

