#include "header/ClearString.h"

ClearString::ClearString(){
    dictionary.insert ( pair<string,string>("á","a") );
    dictionary.insert ( pair<string,string>("à","a") );
    dictionary.insert ( pair<string,string>("ã","a") );
    dictionary.insert ( pair<string,string>("â","a") );
    dictionary.insert ( pair<string,string>("ä","a") );
    dictionary.insert ( pair<string,string>("å","a") );
    dictionary.insert ( pair<string,string>("æ","a") );

    dictionary.insert ( pair<string,string>("Á","A") );
    dictionary.insert ( pair<string,string>("À","A") );
    dictionary.insert ( pair<string,string>("Ã","A") );
    dictionary.insert ( pair<string,string>("Â","A") );
    dictionary.insert ( pair<string,string>("Ä","A") );
    dictionary.insert ( pair<string,string>("Å","A") );
    dictionary.insert ( pair<string,string>("Æ","A") );

    dictionary.insert ( pair<string,string>("é","e") );
    dictionary.insert ( pair<string,string>("è","e") );
    dictionary.insert ( pair<string,string>("ê","e") );
    dictionary.insert ( pair<string,string>("ë","e") );

    dictionary.insert ( pair<string,string>("É","E") );
    dictionary.insert ( pair<string,string>("È","E") );
    dictionary.insert ( pair<string,string>("Ê","E") );
    dictionary.insert ( pair<string,string>("Ë","E") );

    dictionary.insert ( pair<string,string>("í","i") );
    dictionary.insert ( pair<string,string>("ì","i") );
    dictionary.insert ( pair<string,string>("î","i") );
    dictionary.insert ( pair<string,string>("ï","i") );

    dictionary.insert ( pair<string,string>("Í","I") );
    dictionary.insert ( pair<string,string>("Ì","I") );
    dictionary.insert ( pair<string,string>("Î","I") );
    dictionary.insert ( pair<string,string>("Ï","I") );

    dictionary.insert ( pair<string,string>("ó","o") );
    dictionary.insert ( pair<string,string>("ò","o") );
    dictionary.insert ( pair<string,string>("ô","o") );
    dictionary.insert ( pair<string,string>("ö","o") );
    dictionary.insert ( pair<string,string>("ø","o") );
    dictionary.insert ( pair<string,string>("õ","o") );

    dictionary.insert ( pair<string,string>("Ó","O") );
    dictionary.insert ( pair<string,string>("Ò","O") );
    dictionary.insert ( pair<string,string>("Ô","O") );
    dictionary.insert ( pair<string,string>("Ö","O") );
    dictionary.insert ( pair<string,string>("Ø","O") );
    dictionary.insert ( pair<string,string>("Õ","O") );

    dictionary.insert ( pair<string,string>("ú","u") );
    dictionary.insert ( pair<string,string>("ù","u") );
    dictionary.insert ( pair<string,string>("û","u") );
    dictionary.insert ( pair<string,string>("ü","u") );

    dictionary.insert ( pair<string,string>("Ú","U") );
    dictionary.insert ( pair<string,string>("Ù","U") );
    dictionary.insert ( pair<string,string>("Û","U") );
    dictionary.insert ( pair<string,string>("Ü","U") );

    dictionary.insert ( pair<string,string>("ñ","n") );
    dictionary.insert ( pair<string,string>("Ñ","N") );

    dictionary.insert ( pair<string,string>("ç","c") );
    dictionary.insert ( pair<string,string>("Ç","C") );

    dictionary.insert ( pair<string,string>("ý","y") );
    dictionary.insert ( pair<string,string>("Ý","Y") );
    
    dictionary.insert ( pair<string,string>("¿","?") );
    dictionary.insert ( pair<string,string>("½","") );
    dictionary.insert ( pair<string,string>("§","") );
    dictionary.insert ( pair<string,string>("¡","") );
    dictionary.insert ( pair<string,string>("½","") );
    
    

}
    

string ClearString::clear_string(string in){
    string new_str;

    for (auto it = dictionary.begin(); it != dictionary.end(); it++){
        size_t index = 0;
        while (true) {
            /* Locate the substring to replace. */
            index = in.find(it->first, index);
            if (index == std::string::npos) break;

            /* Make the replacement. */
            in.replace(index, 2, it->second);

            /* Advance index forward so the next iteration doesn't pick it up as well. */
            index += 2;
        }
    }

    for (char c : in){

        c = toupper(c);

        if ( ((c >= 'A') && (c <= 'Z')) || ((c >= '0') && (c <= '9')) ){
            new_str += c;
        }

        if ( (c == ' ') && (new_str.back() != ' ') ){
            new_str += c;
        }

    }

    if (new_str.back() == ' '){
        new_str.pop_back();
    }
    return new_str;
}
