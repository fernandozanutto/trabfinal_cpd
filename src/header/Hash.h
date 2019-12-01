#include <vector>

using namespace std;

template <class K>
class Hash {
private:
    int size;
    vector<vector<K*>> table;
    
public:   
    
    Hash(int s);
    
    int hashFunction(int x);

    void insert(K* s);
    
    int search(int s);
    
    K* &operator[](int index);
};


#include "../Hash.cpp"
