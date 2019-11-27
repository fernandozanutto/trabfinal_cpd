#include <bits/stdc++.h>

using namespace std;


class User{
    int id;
    vector<pair<int,int>> ratings;
};

class Movie {
public:
    int id;
    int num_ratings;
    double sum_ratings;
    
    Movie(int _id){
        id = _id;
        num_ratings = 0;
        sum_ratings = 0;
    }
    
    Movie(int _id, int _n, double _r){
        id = _id;
        num_ratings = _n;
        sum_ratings = _r;
    }
    
    const string toString() const {
        ostringstream buffer;
        
        buffer << "ID: " << id << " Num ratings: " << num_ratings << " Soma: " << sum_ratings << endl;
        return buffer.str();
    }
    
};

template <class K>
class Hash {

private:

    int size;
    vector<vector<K>> table;
    
public:   
    Hash(int s){
        size = s;
        table.assign(s, vector<K>());
    }
    
    int hashFunction(int x) {
        x = ((x >> 16) ^ x) * 0x45d9f3b;
        x = ((x >> 16) ^ x) * 0x45d9f3b;
        x = (x >> 16) ^ x;

        return x % size;
    }

    void insert(K s){
        int pos = hashFunction(s.getIdentifier());
        table[pos].push_back(s);
    }
    
    int search(int s){
        int pos = hashFunction(s);
        
        for(int i=0; i < table[pos].size(); i++){
            if(s == table[pos][i])
                return table[pos][i];
        }
        return -1;
    }
    
    K &operator[](int index){
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
};

int main(){
    
    /*
    Loading movies rating
    */
    Hash<Movie> hashRatings(5471); // ~27k movies
    
    fstream rating;
    rating.open("minirating.csv", ios::in);
    string temp;
    getline(rating, temp);
    
    while(getline(rating, temp)){
    
        stringstream s(temp);
        string word;
        
        getline(s, word, ',');
        
        int userId = stoi(word);
        getline(s, word, ',');
        int movieId = stoi(word);
        getline(s, word, ',');
        double r = stod(word);
        
        hashRatings[movieId].num_ratings += 1;
        hashRatings[movieId].sum_ratings += r;
        
        //cout << hashRatings[movieId].toString() << endl;   
    }

    return 0;

}
