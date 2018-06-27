#include "QuadraticProbing.h"
#include "LinearProbing.h"
#include "DoubleHashing.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// We insert every word into Hash table
// We then do calculations for different statistics
// Given the query file, we search for each word and check number of collisions
template <typename HashTableType>
void
TestFunctionForHashTable(HashTableType &hash_table, const string &words_filename, const string &query_filename) {
  cout << "TestFunctionForHashTables..." << endl;
  cout << "Words filename: " << words_filename << endl;
  cout << "Query filename: " << query_filename << endl;
  hash_table.MakeEmpty();
  ifstream file_reader;
  file_reader.open(words_filename);
  string word;
  while(getline(file_reader, word)) {
    hash_table.Insert(word);
  }
  cout << "Collisions: " << hash_table.NumberOfCollisions() << endl;
  cout << "Number of items: " << hash_table.NumberOfElements() << endl;
  cout << "Size of hash table: " << hash_table.TableSize() << endl;
  cout << "Load factor: " << hash_table.LoadFactor() << endl;
  cout << "Avg. number of collisions: " << hash_table.AverageNumberCollisions() << endl;

  ifstream query_reader;
  query_reader.open(query_filename);
  while(getline(query_reader, word)) {
    hash_table.ResetCollisions(); // Reset collisions so we can get each individual value
    if(hash_table.Contains(word)) {
      cout << word << ": Found ";
    }
    else {
      cout << word << ": Not Found ";
    }
    cout << hash_table.NumberOfCollisions() << " Probes Total." << endl;
  }
  file_reader.close();
  query_reader.close();
}

// Sample main for program CreateAndTestHash
int
main(int argc, char **argv) {
  if (argc != 4) {
    cout << "Usage: " << argv[0] << " <wordsfilename> <queryfilename> <flag>" << endl;
    return 0;
  }

  const string words_filename(argv[1]);
  const string query_filename(argv[2]);
  const string param_flag(argv[3]);

  if (param_flag == "linear") {
    HashTableLinear<string> linear_probing_table;
    TestFunctionForHashTable(linear_probing_table, words_filename, query_filename);
  } else if (param_flag == "quadratic") {
    HashTable<string> quadratic_probing_table;
    TestFunctionForHashTable(quadratic_probing_table, words_filename, query_filename);
  } else if (param_flag == "double") {
    HashTableDouble<string> double_probing_table;
    TestFunctionForHashTable(double_probing_table, words_filename, query_filename);
  } else {
    cout << "Uknown tree type " << param_flag << " (User should provide linear, quadratic, or double)" << endl;
  }
  return 0;
}
