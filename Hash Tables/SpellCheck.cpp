#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include "QuadraticProbing.h"

using namespace std;

// We first use a temp string to modify
// Using ascii values, we insert every possible lower case character
// into every possible position in the string
// Check if any possible modified string exists in the hash table
template <typename HashTableType>
void CaseA(const HashTableType & hash_table, const string & word) {
  char c;
  string tmp = word;
  for(int i = 0; i <= word.length(); i++) {
    for(int z = 97; z <= 122; z++) {
      tmp = tmp.insert(i, 1, z);
      if(hash_table.Contains(tmp)) {
        cout << word << " -> " << tmp << " (Case A)" << endl;
      }
      tmp = word; // reset tmp back to word
    }
  }
}

// Same as Case A, except here we remove a single character from any position
template <typename HashTableType>
void CaseB(const HashTableType & hash_table, const string & word) {
  string tmp = word;
  for(int i = 0; i < word.length(); i++) {
    tmp = tmp.erase(i, 1);
    if(hash_table.Contains(tmp)) {
      cout << word << " -> " << tmp << " (Case B)" << endl;
    }
    tmp = word; // reset tmp back to word
  }
}

// Same as Case A except we swap any adjacent characters in the string
template <typename HashTableType>
void CaseC(const HashTableType & hash_table, const string & word) {
  string tmp = word;
  for(int i = 0; i < word.length() - 1; i++) {
    swap(tmp[i], tmp[i+1]);
    if(hash_table.Contains(tmp)) {
      cout << word << " -> " << tmp << " (Case C)" << endl;
    }
    tmp = word; // reset tmp back to word
  }
}

// SpellCheck function
template <typename HashTableType>
void SpellCheck(HashTableType & hash_table, const string & document, const string & dictionary) {
  ifstream dictionary_reader;
  dictionary_reader.open(dictionary);
  string word;

  //Insert every word from dictionary to hash table
  while(getline(dictionary_reader, word)) {
    hash_table.Insert(word);
  }
  ifstream document_reader;
  document_reader.open(document);
  string line;
  word = "";

  // Read from the document file
  while(getline(document_reader, line)) {

    // Parses each line
    for(int i = 0; i < line.length(); i++) {

      // If letter is capitol, we need to make it lower case
      if(line[i] >= 65 and line[i] <= 90) {
        line[i] += 32;
        word += line[i];
      }

      // If they are letters or numbers we continue
      else if(line[i] >= 97 and line[i] <= 122 or line[i] >= 48 and line[i] <= 57) {
        word += line[i];
      }

      // A space means a word is finished, and also a - means there are two words
      // seperated by a dash
      else if(line[i] == ' ' or line[i] == '-') {

        // If the word is not empty and it doesnt exist already in the table,
        // We try all 3 cases to find potential correct cases
        if(!word.empty() and !hash_table.Contains(word)) {
          CaseA(hash_table, word);
          CaseB(hash_table, word);
          CaseC(hash_table, word);
        }
        //Must make sure to reset word
        word = "";
      }
    }
  }
  // Test for the last word of each file
  if(!word.empty() and !hash_table.Contains(word)) {
    CaseA(hash_table, word);
    CaseB(hash_table, word);
    CaseC(hash_table, word);
  }
  dictionary_reader.close();
  document_reader.close();
}

// Main where we test SpellCheck
int main(int argc, char **argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <documentfilename> <dictionaryfilename>" << endl;
    return 0;
  }

  const string document_filename(argv[1]);
  const string dictionary_filename(argv[2]);

  HashTable<string> quadratic_probing_table;
  SpellCheck(quadratic_probing_table, document_filename, dictionary_filename);
  return 0;
}
