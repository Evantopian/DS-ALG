// Evan Huang
// spell_check.cc: A simple spell checker.

#include <fstream>
#include <iostream>
#include <string>

// You can change to quadratic probing if you
// haven't implemented double hashing.
#include "quadratic_probing.h"
using namespace std;

// You can add more functions here.
void inDict(HashTable<string> &dict, string x, string y, char z)
{
  if (dict.Contains(y) > 0)
    cout << "** " << x << " -> " << y << " **"
         << " case " << z << endl;
}

// Creates and fills quadratically probed hash table with all words from
// dictionary_file
HashTable<string> MakeDictionary(const string &dictionary_file)
{
  HashTable<string> dictionary_hash;
  ifstream dict_file(dictionary_file);

  // insert each word of the file int othe dictionary
  string db_line;
  while (getline(dict_file, db_line))
  {
    dictionary_hash.Insert(db_line);
  }

  return dictionary_hash;
}

// For each word in the document_file, it checks the 3 cases for a word being
// misspelled and prints out possible corrections
void SpellChecker(HashTable<string> &dictionary, const string &document_file)
{

  // change stream buffer to cin
  ifstream doc_file(document_file);
  string db_word;
  if (doc_file.is_open())
  {
    cin.rdbuf(doc_file.rdbuf());
  }

  // iterate over each word in the document
  while (!cin.fail() && cin >> db_word)
  {
    // runs through each char of the word and checks if its alphabetical.
    // if not alphanumeric, remove trailing spaces.
    for (size_t i = 0, j = db_word.size() - 1; i < db_word.size(); i++, j--)
    {
      if (isalnum(db_word[i]) && isalnum(db_word[j]))
        break;

      if (isalnum(db_word[i]))
        db_word.erase(j, db_word.size());
      else
        db_word.erase(i, db_word.size());
    }

    // change all values to lowercase
    for (char &ch : db_word)
      ch = tolower(ch);

    // check if the word is in the dictionary
    bool valid = dictionary.get(db_word).empty() ? false : true;
    cout << db_word << " is " << (valid ? "CORRECT" : "INCORRECT") << endl;

    if (!valid)
    {
      // Case A: Adding one character in any possible position.
      for (size_t i = 0; i < db_word.size() + 1; i++)
      {
        string tmp = db_word;
        for (int j = 0; j < ('z' - 'a' + 1); j++)
        {
          tmp = tmp.substr(0, i) + (char)('a' + j) + tmp.substr(i, tmp.size());
          inDict(dictionary, db_word, tmp, 'A');
          tmp = tmp.substr(0, i) + tmp.substr(i + 1, tmp.size());
        }
      }

      // Case B: Removing one character from the word
      for (size_t i = 0; i < db_word.size(); i++)
      {
        string tmp = db_word;
        tmp = tmp.substr(0, i) + tmp.substr(i + 1, tmp.size());
        inDict(dictionary, db_word, tmp, 'B');
      }

      // Case C: Swapping adjacent chracters in the word
      for (int i = 0; i < (int)db_word.size() - 1; i++)
      {
        string tmp = db_word;
        swap(tmp[i], tmp[i + 1]);
        inDict(dictionary, db_word, tmp, 'C');
      }
    }
  }
}

// @argument_count: same as argc in main
// @argument_list: save as argv in main.
// Implements
int testSpellingWrapper(int argument_count, char **argument_list)
{
  const string document_filename(argument_list[1]);
  const string dictionary_filename(argument_list[2]);

  // Call functions implementing the assignment requirements.
  HashTable<string> dictionary = MakeDictionary(dictionary_filename);
  SpellChecker(dictionary, document_filename);
  return 0;
}

// Sample main for program spell_check.
// WE WILL NOT USE YOUR MAIN IN TESTING. DO NOT CODE FUNCTIONALITY INTO THE
// MAIN. WE WILL DIRECTLY CALL testSpellingWrapper. ALL FUNCTIONALITY SHOULD BE
// THERE. This main is only here for your own testing purposes.
int main(int argc, char **argv)
{
  if (argc != 3)
  {
    cout << "Usage: " << argv[0] << " <document-file> <dictionary-file>"
         << endl;
    return 0;
  }

  testSpellingWrapper(argc, argv);

  return 0;
}
