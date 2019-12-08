#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cctype>
#include <set>
#include <iomanip> // setw


#include "dictionary.h"

using namespace std;

void lower(string& s);
string stripPunct(const string& s);
void checkSpelling(ifstream& in, Dictionary& dict);
void checkTransposing(string s, Dictionary& dict, set<string>& sset);
void checkRemoval(string s, Dictionary& dict, set<string>& sset);
void checkReplacement(string s, Dictionary& dict, set<string>& sset);
void checkInserting(string s, Dictionary& dict, set<string>& sset);


// program arguments to run, example: main.exe ../../res/wordlist.txt ../../res/test.txt
int main(int argc, char* argv[]) {

	// Output usage message if improper command line args were given.
	if (argc != 3)
    {
		cerr << "Usage: " << argv[0] << " wordlist_filename input_file\n";
		return EXIT_FAILURE;
	}

	ifstream inf(argv[2]);
	if (! inf) 
    {
		cerr << "Could not open " << argv[2] << "\n";
		return EXIT_FAILURE;
	}
	
	// Read dictionary, but let user know what we are working on.
	cout << "Loading dictionary, this may take awhile...\n";

	Dictionary d(argv[1]);
	checkSpelling(inf, d);
	inf.close();

	return EXIT_SUCCESS;
}


void checkSpelling(ifstream& in, Dictionary& dict) {

	int line_number = 0;

	while (in) 
    {
		line_number++;
		set<string> totest;
		string line;
		getline(in, line);

  	    stringstream ss (stringstream::in | stringstream::out);
		ss << line;
		
		string word;
		while (ss >> word) 
        {
		    word = stripPunct(word);
		    lower(word);
            if(dict.search(word))
            {
                std::cout<<word<<": spelled correctly"<<"\n";
                continue;
            }
            checkTransposing(word, dict, totest);
            checkRemoval(word, dict, totest);
            checkReplacement(word, dict, totest);
            checkInserting(word, dict, totest);
            cout << word << "(" << line_number << "): ";
            for (auto it = totest.begin(); it != totest.end(); it++)
                cout << *it << ", ";
            cout << '\n';
            totest.clear();
		}
	}
}

void checkTransposing(string word, Dictionary& dict, set<string>& totest)
{
    for (int i = 0; i < word.length() - 1; i++) {
        string s = word;
        char sym = s[i];
        s[i] = s[i + 1];
        s[i + 1] = sym;
        if (dict.search(s))
            totest.insert(s);
    }
}

void checkRemoval(string word, Dictionary& dict, set<string>& totest)
{
    for(int i = 0; i < word.length(); i++)
    {
        string s = word;
        s.erase(i, 1);
        if(dict.search(s))
            totest.insert(s);
    }
}

void checkReplacement(string word, Dictionary& dict, set<string>& totest)
{
    for(int i = 0; i < word.length(); i++)
    {
        string s = word;
        for(int j = int('a'); j <= int('z'); j++)
        {
            s[i] = char(j);
            if(dict.search(s))
                totest.insert(s);
        }
    }
}

void checkInserting(string word, Dictionary& dict, set<string>& totest)
{
    for(int i = 0; i <= word.length(); i++)
        for(int j = int('a'); j <= int('z'); j++)
        {
            string s = word;
            s.insert(i, string(1,char(j)));
            if(dict.search(s))
                totest.insert(s);
        }
}

void lower(string& s)
{

    // Ensures that a word is lowercase
	for (int i = 0; i < s.length(); i++)
    {
		s[i] = tolower(s[i]);
	}
}

string stripPunct(const string& s)
{

	// Remove any single trailing
	// punctuation character from a word.  
	if (ispunct(s[s.length() - 1]) ) 
    {
		return s.substr (0, s.length() - 1);
	}
	else 
    {
		return s;
	}
}
