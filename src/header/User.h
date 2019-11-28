#include <vector>
#include <utility>

using namespace std;

class User {
public:
    int id;
    vector<pair<int,int>> ratings;
    
    User(int _id);
};

