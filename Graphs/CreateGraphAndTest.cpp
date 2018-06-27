#include "Graph.h"
#include "HelpFunctions.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;


// Load the graph and then check adjaceny, Part 1
void CreateGraphAndTest(Graph & test_graph, const string& file1, const string& file2) {
  LoadGraph(test_graph, file1);
  TestVertexAdjancency(test_graph, file2);
}

int
main(int argc, char **argv) {

  const string num1_filename(argv[1]);
  const string num2_filename(argv[2]);

  Graph g;
  CreateGraphAndTest(g, num1_filename, num2_filename);
  return 0;
}
