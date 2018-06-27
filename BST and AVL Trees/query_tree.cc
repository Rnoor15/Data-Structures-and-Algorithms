// <Your name>
// Main file for Part2(a) of Homework 2.

#include "AvlTree.h"
#include "BinarySearchTree.h"
#include "SequenceMap.h"
#include "functions.h"

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

namespace {

// We load the tree, and then get 3 strings from the User
// We then search for those three strings
template <typename TreeType>
void QueryTree(const string &db_filename, TreeType &a_tree) {
  LoadTree(db_filename, a_tree);
  string seq1 ,seq2, seq3;
  getline(cin, seq1);
  getline(cin, seq2);
  getline(cin, seq3);
  SequenceMap s1{seq1, ""};
  SequenceMap s2{seq2, ""};
  SequenceMap s3{seq3, ""};
  a_tree.find(s1);
  a_tree.find(s2);
  a_tree.find(s3);
}

}  // namespace

int
main(int argc, char **argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <databasefilename> <tree-type>" << endl;
    return 0;
  }
  const string db_filename(argv[1]);
  const string param_tree(argv[2]);
  cout << "Input filename is " << db_filename << endl;
  cout << "Type of tree is " << param_tree << endl;
  if (param_tree == "BST") {
    // Note that you will replace BinarySearchTree<int> with BinarySearchTree<SequenceMap>
    BinarySearchTree<SequenceMap> a_tree;
    QueryTree(db_filename, a_tree);
  } else if (param_tree == "AVL") {
    // Note that you will replace AvlTree<int> with AvlTree<SequenceMap>
    AvlTree<SequenceMap> a_tree;
    QueryTree(db_filename, a_tree);
  } else {
    cout << "Uknown tree type " << param_tree << " (User should provide BST, or AVL)" << endl;
  }
  return 0;
}
