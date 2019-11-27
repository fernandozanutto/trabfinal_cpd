#include <bits/stdc++.h>

using namespace std;

template <class T>
class Hash {

public:
    int size;
    vector<vector<T>> table;
    
    virtual int hashFunction(T s) = 0;

    Hash(int s){
        size = s;
        table.assign(s, vector<T>());
    }
    
    void insert(T s){
        int pos = hashFunction(s);
        table[pos].push_back(s);
    }
    
    T search(T s){
        int pos = hashFunction(s);
        
        for(int i=0; i < table[pos].size(); i++){
            if(s == table[pos][i])
                return table[pos][i];
        }
        return ;
    }


};


class HashFilmes: public Hash<int> {
public:
    HashFilmes(int s) : Hash(s) {}
    
    int hashFunction(int i){
        return i;
    }
};




int main(){

    freopen("out.txt", "w", stdout);
    freopen("minirating.csv", "r",stdin);
    
    HashFilmes teste(50);

    return 0;

}
