#include <vector>
#include <utility>
#include "header/User.h"

using namespace std;

class User  {
public:
    int id;
    std::vector<std::pair<int,int>> ratings; // pair <movieId, rating>
    
    User(int _id){
        id = _id;        
    }
};
