#include <bits/stdc++.h>

using namespace std;

template <class T>
class Hash {

private:
    int size;
    vector<vector<T>> table;
    
    int hashFunction(T s){
            
    }
    

public:
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


int main(){

    freopen("out.txt", "w", stdout);
    freopen("minirating.csv", "r",stdin);

    return 0;

}
