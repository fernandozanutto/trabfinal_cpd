template <class K>

Hash<K>::Hash(int s){
    size = s;
    table.assign(s, vector<K>());
}


template <class K>
int Hash<K>::hashFunction(int x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;

    return x % size;
}


template <class K>
void Hash<K>::insert(K s){
    int pos = hashFunction(s.getIdentifier());
    table[pos].push_back(s);
}

template <class K>
int Hash<K>::search(int s){
    int pos = hashFunction(s);
    
    for(int i=0; i < table[pos].size(); i++){
        if(s == table[pos][i])
            return table[pos][i];
    }
    return -1;
}

template <class K>
K& Hash<K>::operator[](int index){
    int pos = hashFunction(index);

    if (table[pos].size() == 0){

        K novo(index);
        table[pos].push_back(novo);
        return table[pos][0];
    } else {
        int i;
        for(i=0; i < table[pos].size(); i++){
            if(table[pos][i].id == index){
                return table[pos][i];
            }
        }

        table[pos].push_back(K(index));
        return table[pos][i];
    }
}

