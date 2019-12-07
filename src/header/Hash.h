#include <vector>
#include <iostream>
#include <string>

#define PRIME 37

using namespace std;

template <class K>
class Hash {
private:
    int size;
    vector<vector<K*>> table;

public:
    Hash(int s);
    
    int hashFunction(int x);
    int hashFunction(string x);

    void insert(K* s);
    
    bool search(int s);
    bool search(string s);
    
    K* &operator[](int index);
    K* &operator[](string index);
};


#include "../Hash.cpp"
