#include <iostream>
#include <fstream>
#include "PriorityQueue.h"

using namespace std;

// Insert into queue, and then we search for each key, checking if it exists.
template <typename Comparable>
void TestInsertAndSearch(PriorityQueue<Comparable> &q, const string &file1, const string & file2) {
    ifstream file_reader;
    file_reader.open(file1);
    int num;
    int count = 0;
    while(file_reader >> num) {
      q.insert(num);
      count++;
    }
    cout << "Successfully inserted " << count << " numbers into the queue. ";
    cout << "The minimum element is " << q.findMinimum() << endl;
    file_reader.close();
    file_reader.open(file2);
    while(file_reader >> num) {
      if(q.find(num)) {
        cout << num << ": Found" << endl;
      }
      else {
        cout << num << ": Not Found" << endl;
      }
    }
    file_reader.close();
}


int
main(int argc, char **argv) {

  const string num1_filename(argv[1]);
  const string num2_filename(argv[2]);

  PriorityQueue<int> queue;
  TestInsertAndSearch(queue, num1_filename, num2_filename);
  return 0;
}
