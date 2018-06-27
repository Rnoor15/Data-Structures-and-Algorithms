#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <iostream>
#include "BinomialQueue.h"

using namespace std;

//Priority Queue class using an underlying Binomial queue
//Basic implementation such as insert, find, deleteMin, delete

template <typename Comparable>
class PriorityQueue {
public:
    void insert(const Comparable &x) {queue.insert(x);}
    bool find(const Comparable &x) {return queue.find(x);}
    const Comparable findMinimum() {return queue.findMin();}
    void deleteMin() {queue.deleteMin();}
    void deleteItem(Comparable &x) {queue.deleteItem(x);}
private:
    BinomialQueue<Comparable> queue;
};

#endif
