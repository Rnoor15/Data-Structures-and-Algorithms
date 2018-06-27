#ifndef BINOMIAL_QUEUE_H
#define BINOMIAL_QUEUE_H

#include <iostream>
#include <vector>
#include <iterator>
#include "dsexceptions.h"
#include <unordered_map>

using namespace std;

// Binomial queue class
//
// CONSTRUCTION: with no parameters
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// deleteMin( )           --> Return and remove smallest item
// Comparable findMin( )  --> Return smallest item
// bool isEmpty( )        --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void merge( rhs )      --> Absorb rhs into this heap
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class BinomialQueue
{
  public:
    BinomialQueue( ) : theTrees( DEFAULT_TREES )
    {
        for( auto & root : theTrees )
            root = nullptr;
        currentSize = 0;
    }

    BinomialQueue( const Comparable & item ) : theTrees( 1 ), currentSize{ 1 }
      { theTrees[ 0 ] = new BinomialNode{ item, nullptr, nullptr, nullptr }; }

    BinomialQueue( const BinomialQueue & rhs )
      : theTrees( rhs.theTrees.size( ) ),currentSize{ rhs.currentSize }
    {
        for( int i = 0; i < rhs.theTrees.size( ); ++i )
            theTrees[ i ] = clone( rhs.theTrees[ i ] );
    }

    BinomialQueue( BinomialQueue && rhs )
      : theTrees{ std::move( rhs.theTrees ) }, currentSize{ rhs.currentSize }
    {
    }

    ~BinomialQueue( )
      { makeEmpty( ); }


    /**
     * Deep copy.
     */
    BinomialQueue & operator=( const BinomialQueue & rhs )
    {
        BinomialQueue copy = rhs;
        std::swap( *this, copy );
        return *this;
    }

    /**
     * Move.
     */
    BinomialQueue & operator=( BinomialQueue && rhs )
    {
        std::swap( currentSize, rhs.currentSize );
        std::swap( theTrees, rhs.theTrees );

        return *this;
    }

    /**
     * Return true if empty; false otherwise.
     */
    bool isEmpty( ) const
      { return currentSize == 0; }

    /**
     * Returns minimum item.
     * Throws UnderflowException if empty.
     */
    const Comparable & findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };

        return theTrees[ findMinIndex( ) ]->element;
    }

    // Use iterators to check if item exists in BinomialQueue
    bool find(const Comparable & x) const
    {
      if(isEmpty())
          throw UnderflowException{ };

      if(hash_table.find(x) == hash_table.end()) {
        return false;
      }
      return true;
    }



    /**
     * Insert item x into the priority queue; allows duplicates.
     */
    void insert( const Comparable & x )
    {
        BinomialQueue oneItem{ x };

        //set the key x in hash table to the pointer in the BinomialQueue
        hash_table[x] = oneItem.getNodePointer();
        merge( oneItem );

    }

    /**
     * Insert item x into the priority queue; allows duplicates.
     */
    void insert( Comparable && x )
    {
        BinomialQueue oneItem{ std::move( x ) };
        hash_table[x] = oneItem.getNodePointer();
        merge( oneItem );
    }

    /**
     * Remove the smallest item from the priority queue.
     * Throws UnderflowException if empty.
     */
    void deleteMin( )
    {
        Comparable x;
        deleteMin( x );
        hash_table[x] = nullptr;
        hash_table.erase(x);
    }

    /**
     * Remove the minimum item and place it in minItem.
     * Throws UnderflowException if empty.
     */
    void deleteMin( Comparable & minItem )
    {
        if( isEmpty( ) )
            throw UnderflowException{ };

        int minIndex = findMinIndex( );
        minItem = theTrees[ minIndex ]->element;

        BinomialNode *oldRoot = theTrees[ minIndex ];
        BinomialNode *deletedTree = oldRoot->leftChild;
        delete oldRoot;

        // Construct H''
        BinomialQueue deletedQueue;
        deletedQueue.theTrees.resize( minIndex );
        deletedQueue.currentSize = ( 1 << minIndex ) - 1;
        for( int j = minIndex - 1; j >= 0; --j )
        {
            deletedQueue.theTrees[ j ] = deletedTree;
            deletedTree = deletedTree->nextSibling;
            deletedQueue.theTrees[ j ]->nextSibling = nullptr;
        }

        // Construct H'
        theTrees[ minIndex ] = nullptr;
        currentSize -= deletedQueue.currentSize + 1;

        merge( deletedQueue );
    }

    // Delete any key in BinomialQueue
    // We first need to get the min value and change the key to less than value
    // Percolate up so node with that key is at the root
    // We can then use deleteMin to delete that node
    // Make sure to update the hash table values
    void deleteItem(Comparable &x) {

      BinomialNode* t1 = hash_table[x];
      Comparable min = findMin() - 1;
      PercolateUp(t1, t1->parent);
      t1->element = min;
      Comparable to_delete;
      deleteMin(to_delete);
      hash_table[x] = nullptr;
      hash_table.erase(x);
    }


    /**
     * Make the priority queue logically empty.
     */
    void makeEmpty( )
    {
        currentSize = 0;
        for( auto & root : theTrees )
            makeEmpty( root );
    }

    /**
     * Merge rhs into the priority queue.
     * rhs becomes empty. rhs must be different from this.
     * Exercise 6.35 needed to make this operation more efficient.
     */
    void merge( BinomialQueue & rhs )
    {
        if( this == &rhs )    // Avoid aliasing problems
            return;

        currentSize += rhs.currentSize;

        if( currentSize > capacity( ) )
        {
            int oldNumTrees = theTrees.size( );
            int newNumTrees = max( theTrees.size( ), rhs.theTrees.size( ) ) + 1;
            theTrees.resize( newNumTrees );
            for( int i = oldNumTrees; i < newNumTrees; ++i )
                theTrees[ i ] = nullptr;
        }

        BinomialNode *carry = nullptr;
        for( int i = 0, j = 1; j <= currentSize; ++i, j *= 2 )
        {
            BinomialNode *t1 = theTrees[ i ];
            BinomialNode *t2 = i < rhs.theTrees.size( ) ? rhs.theTrees[ i ] : nullptr;

            int whichCase = t1 == nullptr ? 0 : 1;
            whichCase += t2 == nullptr ? 0 : 2;
            whichCase += carry == nullptr ? 0 : 4;

            switch( whichCase )
            {
              case 0: /* No trees */
              case 1: /* Only this */
                break;
              case 2: /* Only rhs */
                theTrees[ i ] = t2;
                rhs.theTrees[ i ] = nullptr;
                break;
              case 4: /* Only carry */
                theTrees[ i ] = carry;
                carry = nullptr;
                break;
              case 3: /* this and rhs */
                carry = combineTrees( t1, t2 );
                theTrees[ i ] = rhs.theTrees[ i ] = nullptr;
                break;
              case 5: /* this and carry */
                carry = combineTrees( t1, carry );
                theTrees[ i ] = nullptr;
                break;
              case 6: /* rhs and carry */
                carry = combineTrees( t2, carry );
                rhs.theTrees[ i ] = nullptr;
                break;
              case 7: /* All three */
                theTrees[ i ] = carry;
                carry = combineTrees( t1, t2 );
                rhs.theTrees[ i ] = nullptr;
                break;
            }
        }

        for( auto & root : rhs.theTrees )
            root = nullptr;
        rhs.currentSize = 0;
    }

  // Include parent pointers
  private:
    struct BinomialNode
    {
        Comparable    element;
        BinomialNode *leftChild;
        BinomialNode *nextSibling;
        BinomialNode *parent;

        BinomialNode( const Comparable & e, BinomialNode *lt, BinomialNode *rt, BinomialNode *pt )
          : element{ e }, leftChild{ lt }, nextSibling{ rt }, parent{ pt }  { }

        BinomialNode( Comparable && e, BinomialNode *lt, BinomialNode *rt, BinomialNode *pt  )
          : element{ std::move( e ) }, leftChild{ lt }, nextSibling{ rt }, parent{ pt } { }
    };

    const static int DEFAULT_TREES = 1;

    vector<BinomialNode *> theTrees;  // An array of tree roots
    int currentSize;                  // Number of items in the priority queue
    unordered_map <Comparable, BinomialNode*> hash_table;

    /**
     * Find index of tree containing the smallest item in the priority queue.
     * The priority queue must not be empty.
     * Return the index of tree containing the smallest item.
     */
    int findMinIndex( ) const
    {
        int i;
        int minIndex;

        for( i = 0; theTrees[ i ] == nullptr; ++i )
            ;

        for( minIndex = i; i < theTrees.size( ); ++i )
            if( theTrees[ i ] != nullptr &&
                theTrees[ i ]->element < theTrees[ minIndex ]->element )
                minIndex = i;

        return minIndex;
    }

    // Find the index of a node
    int findIndex(const Comparable &x) const
    {
        int index;
        for(int i = 0; i < theTrees.size(); i++) {
            if(theTrees[i] != nullptr and theTrees[i]->element == x) {
              index = i;
            }
        }
        return index;
    }

    //Return the root of the first index in array
    BinomialNode* getNodePointer() const
    {
        return theTrees[0];
    }

    /**
     * Return the capacity.
     */
    int capacity( ) const
      { return ( 1 << theTrees.size( ) ) - 1; }

    /**
     * Return the result of merging equal-sized t1 and t2.
     */
    BinomialNode * combineTrees( BinomialNode *t1, BinomialNode *t2 )
    {
        if( t2->element < t1->element )
            return combineTrees( t2, t1 );
        t2->nextSibling = t1->leftChild;
        t1->leftChild = t2;

        //Update parent of larger node to the smaller node
        t2->parent = t1;
        return t1;
    }

    // While the parent pointer is not null, we move key to root
    // Swap the key with its parent until it is at the top
    // Update t1 and t2 as well
    void PercolateUp(BinomialNode* &t1, BinomialNode* &t2) {
        while(t2 != nullptr) {
          swap(hash_table[t1->element], hash_table[t2->element]);
          swap(t1->element, t2->element);
          t1 = t2;
          t2 = t2->parent;
        }
    }

    /**
     * Make a binomial tree logically empty, and free memory.
     */
    void makeEmpty( BinomialNode * & t )
    {
        if( t != nullptr )
        {
            makeEmpty( t->leftChild );
            makeEmpty( t->nextSibling );
            delete t;
            t = nullptr;
        }
    }

    /**
     * Internal method to clone subtree.
     */
    BinomialNode * clone( BinomialNode * t ) const
    {
        if( t == nullptr )
            return nullptr;
        else
            return new BinomialNode{ t->element, clone( t->leftChild ), clone( t->nextSibling ), clone(t->parent) };
    }
};

#endif
