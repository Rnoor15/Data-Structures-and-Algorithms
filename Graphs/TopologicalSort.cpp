#include "Graph.h"
#include "HelpFunctions.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// Part 3, we load graph, computeIndegrees, and then TopologicalSort
void TopologicalSort(Graph& test_graph, const string& file1) {
  LoadGraph(test_graph, file1);
  test_graph.computeIndegrees();
  test_graph.SortGraph();
}

int
main(int argc, char **argv) {

  const string num1_filename(argv[1]);

  Graph g;
  TopologicalSort(g, num1_filename);
  return 0;
}
