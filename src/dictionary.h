#ifndef  _DICTIONARY_H_ 
#define  _DICTIONARY_H_

#include  <iostream>
#include  <vector>
#include  <list>
#include  <algorithm>
#include  <string>
#include  <stdlib.h>

#include  "hashset.h"
#include  "hashset.cpp"

using namespace std;

class hash_function
{
public:

    unsigned int operator()( const string& s )  const
    {
        unsigned int hash = 0;
        int pow = 1;
        const int p = 37;
        for(int i = 0; i < s.length(); i++)
        {
            hash += s[i] * pow;
            pow *= p;
        }
        return  hash;
    }
};

class equality
{
public:
    equality() {}
    bool  operator()( const string& A, const string& B )  const 
    {
        return  (A == B);
    }
};

class Dictionary: public HashSet<string, hash_function, equality> {

    // Complete definition
public:
	Dictionary(string filename);

};
#endif // _DICTIONARY_H_
