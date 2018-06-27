#include "Graph.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// Load a graph from the given text file
// Make sure to use stringstream to read ints in pairs for each line
void LoadGraph(Graph &test_graph, const string& file1) {
  ifstream file_reader;
  file_reader.open(file1);
  int start_vertex, adjacent_vertex;
  double weight;
  string line;
  getline(file_reader, line);
  while(getline(file_reader,line)) {
    stringstream ss(line);
    ss >> start_vertex;
    Vertex v;
    v.vertex_num = start_vertex;
    while(ss >> adjacent_vertex >> weight) {
      pair<int, double> p;
      p = make_pair(adjacent_vertex, weight);
      v.adjaceny_list.push_back(p);
    }
    test_graph.AddVertex(v);
  }
  file_reader.close();
}

//Test for part 1
//Read each pair from line, and check for adjacency
void TestVertexAdjancency(Graph& test_graph, const string& file) {
  ifstream file_reader;
  file_reader.open(file);
  string line;
  int start_vertex, adjacent_vertex;
  while(getline(file_reader, line)) {
    stringstream ss(line);
    ss >> start_vertex >> adjacent_vertex;
    cout << start_vertex << " " << adjacent_vertex << ": ";
    test_graph.CheckAdjacency(start_vertex, adjacent_vertex);
  }
  file_reader.close();
}
