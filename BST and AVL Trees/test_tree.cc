// Rifat Noor
// Main file for Part2(b) of Homework 2.

#include "AvlTree.h"
#include "BinarySearchTree.h"
#include "SequenceMap.h"
#include "functions.h"

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
using namespace std;

namespace {

// TestTree routine
// Load the tree, and do calculations on it
// We then search sequences.txt, and then remove every other sequence
// Print the new stats of the tree
template <typename TreeType>
void TestTree(const string &db_filename, const string &seq_filename, TreeType &a_tree) {

  // Load the tree
  LoadTree(db_filename, a_tree);
  cout << "2: " << a_tree.numberOfNodes() << endl;
  float average_depth = a_tree.totalDepth() / (float)a_tree.numberOfNodes();
  cout << "3a: " << average_depth << endl;
  float ratio = average_depth / log2(a_tree.numberOfNodes());
  cout << "3b: " << ratio << endl;
  SearchSequences(seq_filename, a_tree);
  RemoveSequences(seq_filename, a_tree);
  cout << "6a: " << a_tree.numberOfNodes() << endl;
  average_depth = a_tree.totalDepth() / (float)a_tree.numberOfNodes();
  cout << "6b: " << average_depth << endl;
  ratio = average_depth / log2(a_tree.numberOfNodes());
  cout << "6c: " << ratio << endl;
}

}  // namespace

int
main(int argc, char **argv) {
  if (argc != 4) {
    cout << "Usage: " << argv[0] << " <databasefilename> <queryfilename> <tree-type>" << endl;
    return 0;
  }
  const string db_filename(argv[1]);
  const string seq_filename(argv[2]);
  const string param_tree(argv[3]);
  cout << "Input file is " << db_filename << ", and sequences file is " << seq_filename << endl;
  cout << "Type of tree is " << param_tree << endl;
  if (param_tree == "BST") {
    // Note that you will replace BinarySearchTree<int> with BinarySearchTree<SequenceMap>
    BinarySearchTree<SequenceMap> a_tree;
    TestTree(db_filename, seq_filename, a_tree);
  } else if (param_tree == "AVL") {
    // Note that you will replace AvlTree<int> with AvlTree<SequenceMap>
    AvlTree<SequenceMap> a_tree;
    TestTree(db_filename, seq_filename, a_tree);
  } else {
    cout << "Uknown tree type " << param_tree << " (User should provide BST, or AVL)" << endl;
  }
  return 0;
}
