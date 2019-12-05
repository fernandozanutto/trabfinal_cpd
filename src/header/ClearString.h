#include <map>
#include <string>
#include <utility>

using namespace std;

class ClearString {

public:
    map<string, string> dictionary;

    ClearString();
    string clear_string(string in);
};
