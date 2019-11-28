#include <bits/stdc++.h>

using namespace std;


const int ALPHABET_SIZE = 26;

class Trie {
public:
    Trie *children[ALPHABET_SIZE+1];// acho q tem q botar +1 por causa dos espacos q possivelmente tem no nome
    Movie film;
    /* string name;
    int movie_id; // movie id vai servir pra dizer se é uma palavra ou nao
    string genre;   //string com todos os generos q o filme tem separados por virgula
    */
    Trie *getNode(void){
        Trie *pNode = new TrieNode;

        pNode->film.id = 0;

        for (int i = 0; i < ALPHABET_SIZE; i++)
            pNode->children[i] = NULL;

        return pNode;
    }
    void insert(Trie *root, string key, int id, string gen)
    {
        Trie *pCrawl = root;

        for (int i = 0; i < key.length(); i++)
        {
            int index = key[i] - 'a';
            if (!pCrawl->children[index])
                pCrawl->children[index] = getNode();

            pCrawl = pCrawl->children[index];
        }

        pCrawl->film.id = id;
        strcpy(gen, pCrawl->film.genre);
    }
    bool search(struct TrieNode *root, string key)
    {
        Trie *pCrawl = root;

        for (int i = 0; i < key.length(); i++)
        {
            int index = key[i] - 'a';
            if (!pCrawl->children[index])
                return false;

            pCrawl = pCrawl->children[index];
        }

        return (pCrawl != NULL && pCrawl->movie_id);
    }
};
