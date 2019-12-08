#include <iostream>
#include <fstream>
#include <string>
#include "dictionary.h"

using namespace std;

Dictionary::Dictionary(string filename)
{
    string s;
    ifstream in(filename);
    if (!in.is_open())
        throw invalid_argument("invalid filename");
    while (getline(in, s))
        insert(s);
    in.close();
}



