#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "header/Hash.h"
#include "header/User.h"
#include "header/Movie.h"

using namespace std;


int main(){
    
    /*
    Loading movies rating
    */
    Hash<Movie> hashRatings(5471); // ~27k movies
    Hash<User> hashUsers(1000);
    
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
        
        hashUsers[userId].ratings.push_back({movieId, r});
        
        //cout << hashRatings[movieId].toString() << endl;   
    }

    return 0;

}
