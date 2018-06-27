#include <iostream>
#include <fstream>
#include "PriorityQueue.h"

using namespace std;

// We insert into the queue, and then try to delete from the queue
template <typename Comparable>
void TestInsertAndDelete(PriorityQueue<Comparable> &q, const string &file1, const string & file2) {
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
      q.deleteItem(num);
      if(!q.find(num)) {
        cout << "Deletion Successful" << endl;
      }
      else {
        cout << "Serious Error with Deletion" << endl;
      }
      cout << "The new minimum is " << q.findMinimum() << endl;
    }
    file_reader.close();
}

int
main(int argc, char **argv) {

  const string num1_filename(argv[1]);
  const string num2_filename(argv[2]);

  PriorityQueue<int> queue;
  TestInsertAndDelete(queue, num1_filename, num2_filename);
  return 0;
}
