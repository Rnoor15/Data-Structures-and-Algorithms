#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "AvlTree.h"
#include "BinarySearchTree.h"
#include "SequenceMap.h"

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// Here is all the helper functions for both test routines

// Loads the tree reading input from file
// We first must skip first 10 lines since they are useless
// Then we read the enzyme acronym, and then read each rec string
// For each string, we create a SequenceMap, and with the enzyme,
// we insert it to the tree. Repeat for every line.
template<typename TreeType>
void LoadTree(const string &db_filename, TreeType &a_tree) {
  ifstream my_file;
  my_file.open(db_filename);
  string db_line;
  for(int i = 0; i < 10; i++) {
    getline(my_file, db_line);
  }
  string enzyme;
  while(getline(my_file, db_line)) {
    if(db_line.empty()) break;
    int line_counter = 0;
    while(db_line[line_counter] != '/') {
      enzyme = enzyme + db_line[line_counter];
      line_counter++;
    }
    line_counter++;
    string sequence;
    while(line_counter < db_line.length()) {
      if(db_line[line_counter] == '/') {
        SequenceMap new_sequence_map{sequence, enzyme};
        a_tree.insert(new_sequence_map);
        sequence = "";
        line_counter++;
        if(db_line[line_counter] == '/') break;
      }
      sequence = sequence + db_line[line_counter];
      line_counter++;
    }
    enzyme = "";
  }
}


// Part 2b number 4
// We read sequences in a file, and check to see if they exist.
// We also track the number of recursive calls being made
// If find status is true after the call to find(),
// we increment successful_queries.
// Finally compute the average recursive calls
template <typename TreeType>
void SearchSequences(const string &seq_filename, TreeType &a_tree) {
  ifstream sequence_file;
  sequence_file.open(seq_filename);
  string seq_line;
  int successful_queries = 0;
  int total_queries = 0;
  int recursion_counter = 0;
  bool find_status = true;
  while(getline(sequence_file, seq_line)) {
    SequenceMap s{seq_line, ""};
    a_tree.find(s, recursion_counter, find_status);
    if(find_status) successful_queries++;
    find_status = true;
    total_queries++;
  }
  cout << "4a: " <<  successful_queries << endl;
  float average_recurses = recursion_counter / float(total_queries);
  cout << "4b: " << average_recurses << endl;
}

// Part 2b number 5
// We delete a sequenceMap for every other sequence
// Track recursive call counter, and make sure if item is removed
// If it is removed we need to increment successful_removes
// Finally calculate average recursive calls
template <typename TreeType>
void RemoveSequences(const string &seq_filename, TreeType &a_tree) {
  ifstream sequence_file;
  sequence_file.open(seq_filename);
  string seq_line;
  int recursion_counter = 0;
  int removes_counter = 0;
  int successful_removes = 0;
  int line_counter = 0;
  bool remove_status = true;
  while(getline(sequence_file, seq_line)) {
    if(line_counter % 2 == 0) {
      SequenceMap s{seq_line, ""};
      a_tree.remove(s, recursion_counter, remove_status);
      if(remove_status) successful_removes++;
      removes_counter++;
      remove_status = true;
    }
    line_counter++;
  }
  float average_recurses = recursion_counter / (float)removes_counter;
  cout << "5a: " << successful_removes << endl;
  cout << "5b: " << average_recurses << endl;
}



#endif
