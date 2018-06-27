#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <limits>
#include <queue>
#include <functional>

using namespace std;

/*
    First we need a struct for a vertex in our graph.
    Our vertex has a value, an indegree, and also the essential
    variables for Dijkstra's algorithm. We also have a adjaceny list,
    and a comparator which compares the vertex's.
*/
struct Vertex {
  int vertex_num;
  int indegree;
  mutable bool status = false;
  double distance = numeric_limits<double>::infinity();
  Vertex* prev;

  // We use a pair, int representing the vertex number,
  // And the double representing the weight of that edge
  list<pair<int, double>> adjaceny_list;
  struct Comparator{
    bool operator()(const Vertex& lhs, const Vertex& rhs) {
      return lhs.distance > rhs.distance;
    }
  };

  // Goes through the adjacency list checking if the target exists
  // If it does, we output the associated edge weight
  void is_Adjacent(const int target) {
    for(auto it = adjaceny_list.begin(); it != adjaceny_list.end(); it++) {
      if(it->first == target) {
        cout << "Connected, the weight of edge is " << it->second << endl;
        return;
      }
    }
    cout << "Not Connected" << endl;
  }

  // Print the values of the adjacency list
  void print() {
    for(auto it = adjaceny_list.begin(); it != adjaceny_list.end(); it++) {
      cout << it->first << " " << it->second << " ";
    }
  }
};


// Graph class using a vector of vertex's
class Graph {
public:

  // Add a vertex to our graph
  void AddVertex(const Vertex& v) {
    directed_graph.push_back(v);
  }

  // Returns the number of vertices in graph
  int GraphSize() {
    return directed_graph.size() - 1;
  }

  // Checks whether two vertices are adjacent to each other
  void CheckAdjacency(const int vertex, const int adj_vertex) {
    if(vertex >= directed_graph.size() or adj_vertex >= directed_graph.size()) {
      cout << "Vertex does not exist" << endl;
      return;
    }
    directed_graph[vertex].is_Adjacent(adj_vertex);
  }

  // Checks all the indegrees of vertices
  void AllDegrees() {
    for(int i = 1; i < directed_graph.size(); i++) {
      cout << directed_graph[i].indegree << endl;
    }
  }

  // Calculates the path from the start to all vertices
  void AllPaths(const int start) {

    // Call Dijkstra with the start vertex
    Dijkstra(start);

    //If our vertice has a false known status, it is not reachable from point
    for(int i = 1; i < directed_graph.size(); i++) {
      if(!directed_graph[i].status) {
        cout << i << ": " << "No path" << endl;
        continue;
      }

      // Vector holds the path of the vertices
      vector <int> paths;
      cout << i << ": ";

      //Total is the distance to that vertex
      double total = directed_graph[i].distance;

      //Curr starts at the current vertice
      Vertex* curr = &directed_graph[i];

      //We go backwards using the previous pointer
      while(curr != &directed_graph[start]) {
        paths.push_back(curr->vertex_num);
        curr = curr->prev;
      }
      paths.push_back(start);

      // Print the path
      for(int i = paths.size()-1; i > 0; i--) {
        cout << paths[i] << "->";
      }
      cout << paths[0];
      cout << " (Cost:" << total << ")" << endl;
    }
  }

  // Dijkstra using stl priority queue
  // Use a Comparator to make queue a min-heap
  // Push every vertice to heap, and update distance if it is less
  // We pop the smallest distance vertex
  void Dijkstra(const int vertex) {
    directed_graph[vertex].distance = 0;
    priority_queue<Vertex, vector<Vertex>, Vertex::Comparator> p;
    p.push(directed_graph[vertex]);
    int dist, index;
    for( ; ; ) {
      bool success = false;
      while(!p.empty() and !success) {
        if(!p.top().status) {
          index = p.top().vertex_num;
          dist = p.top().distance;
          directed_graph[index].status = true;
          p.pop();
          success = true;
        }
        else {
          p.pop();
        }
      }
      if(!success) break;

      for(auto it = directed_graph[index].adjaceny_list.begin();
          it != directed_graph[index].adjaceny_list.end(); it++) {
            if(dist + it->second < directed_graph[it->first].distance) {
              directed_graph[it->first].distance = dist + it->second;
              p.push(directed_graph[it->first]);
              directed_graph[it->first].prev = &directed_graph[index];
            }
          }
    }

  }

// Compute the indegree of every vertex
  void computeIndegrees() {
    for(int i = 0; i < directed_graph.size(); i++) {
      for(auto it = directed_graph[i].adjaceny_list.begin();
          it != directed_graph[i].adjaceny_list.end(); it++) {
            directed_graph[it->first].indegree++;
          }
    }
  }

// Topological Sort of Graph
// Use a queue to put all vertices of indegree 0
// Update the indegrees of adjacent vertices after dequeue
// Check for cycle as well
// Print out the vertices sorted
  void SortGraph() {
    queue<Vertex> q;
    int counter = 0;
    vector<int> ordered_vertices;
    for(int i = 1; i < directed_graph.size(); i++) {
      if(directed_graph[i].indegree == 0) {
        q.push(directed_graph[i]);
      }
    }
    while(!q.empty()) {
      int index = q.front().vertex_num;
      ordered_vertices.push_back(index);
      q.pop();
      counter++;
      for(auto it = directed_graph[index].adjaceny_list.begin();
          it != directed_graph[index].adjaceny_list.end(); it++) {
            directed_graph[it->first].indegree--;
            if(directed_graph[it->first].indegree == 0) {
              q.push(directed_graph[it->first]);
            }
          }
    }
    if(counter != GraphSize()) {
      cout << "Cycle Found" << endl;
      return;
    }
    for(int i = 0; i < ordered_vertices.size()-1; i++) {
      cout << ordered_vertices[i] << ",";
    }
    cout << ordered_vertices[ordered_vertices.size()-1] << "." << endl;
  }

  // Print the adj list in each vertice
  void printVec() {
    for(int i = 1; i < directed_graph.size(); i++) {
      cout << i << " ";
      directed_graph[i].print();
      cout << endl;
    }
  }
private:

  //We use 1 to start, since we want the 0 index empty
  vector<Vertex> directed_graph{1};
};

#endif
