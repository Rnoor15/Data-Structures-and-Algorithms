#include "Graph.h"
#include "HelpFunctions.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// Load graph and then print all shortest paths Part 2
void FindPaths(Graph& test_graph, const string& file1, const int v) {
  LoadGraph(test_graph, file1);
  test_graph.AllPaths(v);
}

int
main(int argc, char **argv) {

  const string num1_filename(argv[1]);
  const int vertex_number = stoi(argv[2]);

  Graph g;
  FindPaths(g, num1_filename, vertex_number);
  return 0;
}
