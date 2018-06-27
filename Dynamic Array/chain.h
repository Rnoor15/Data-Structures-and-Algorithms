// Rifat Noor
// Class Chain is simply a psuedo vector, which uses an uderlying
// dynamic array, and also using the big five and operator overloading.

#ifndef CSCI335_HOMEWORK1_CHAIN_
#define CSCI335_HOMEWORK1_CHAIN_

#include <iostream>
#include <cstddef>
#include <sstream>

namespace teaching_project {
// Chain revolves around using a pointer to dynamically create arrays.
// We use templates to let Chain hold different data types.
// Big Five implementation and operator <<, [], and + are overloaded.
template<typename Object>
class Chain {
 public:

  //Default constructor
  Chain() : size_{0}, array_{nullptr} {}

  // Copy-constructor.
  Chain(const Chain &rhs) {
    array_ = new Object[rhs.size_];
    for(int i = 0; i < rhs.size_; i++) {
      array_[i] = rhs.array_[i];
    }
    size_ = rhs.size_;
  }

  //Copy Assignment, using swap to switch object values
  Chain& operator=(const Chain &rhs) {
    Chain copy = rhs;
    std::swap(*this, copy);
    return *this;
  }

  // Move-constructor.
  Chain(Chain &&rhs) : array_{rhs.array_}, size_{rhs.size_} {
    rhs.array_ = nullptr;
    rhs.size_ = 0;
  }

  // Move-assignment.
  // Set current object to rhs values
  // Set rhs object to zero and null
  Chain& operator=(Chain &&rhs) {

    // Must deallocate memory existing to avoid leaks
    delete [] array_;
    array_ = rhs.array_;
    size_ = rhs.size_;
    rhs.array_ = nullptr;
    rhs.size_ = 0;
  }

  // Destructor deleting pointers
  ~Chain() { delete [] array_; }

  // One parameter constructor.
  Chain(const Object& item) {
    array_ = new Object[1];
    array_[0] = item;
    size_ = 1;
  }

  // Read a chain from standard input.
  void ReadChain() {
    // User input string, using getline
    std::string user_chain;
    std::getline(std::cin, user_chain);

    // Abort if the input does not start in [
    // or end in ]
    if(user_chain[0] != '[' and user_chain[user_chain.length() - 1] != ']') {
      std::abort();
    }

    // Stringstream which breaks the string up
    std::stringstream ss;

    // Counter to track which index in string
    int counter = 1;

    // Get the size and then we convert to int
    for(int i = 1; user_chain[i] != ':'; i++) {
      ss << user_chain[i];
      counter++;
    }

    // We know that after the :, there is a ' ', so we increment counter by 2
    // Now counter starts with the first object to be put in the array
    counter = counter + 2;
    ss >> size_;

    // Create the array dynamically using size
    array_ = new Object[size_];
    ss.clear();
    Object temp;

    //Index for array, increment each time we add to array
    int array_index = 0;
    for(int i = counter; user_chain[i] != ']'; i++) {

      // If we hit a space, then we need to add the object to array
      // Clear stream and increment index for array
      if(user_chain[i] == ' ') {
        ss >> temp;
        array_[array_index] = temp;
        ss.clear();
        array_index++;
      }
      ss << user_chain[i];
    }

    // This is for the last item in the input
    ss >> temp;
    array_[array_index] = temp;
  }

  // Return size
  size_t size() const { return size_; }

  // Const operator overloaded
  // Abort if out of range
  // Use a reference, so a copy is not returned
  const Object& operator[](size_t location) const {
    if(location >= size_) {
      std::abort();
    }
    Object &value = array_[location];
    return value;
  }

 // Non-const version of [] operator
 Object& operator[](size_t location) {
   if(location >= size_) {
     std::abort();
   }
   return array_[location];
 }

 // + operator, using 2 chains
 friend Chain operator+(const Chain &c1, const Chain &c2) {

   // Create a new chain with size of the 2 combined
   Chain <Object> combined_chain;
   combined_chain.size_ = c1.size_ + c2.size_;
   combined_chain.array_ = new Object[combined_chain.size_];

   // Copy elements over from 1st chain
   for(int i = 0; i < c1.size_; i++) {
     combined_chain.array_[i] = c1[i];
   }
   int counter = 0;

   // Copy elements over from second chain
   for(int i = c1.size_; i < combined_chain.size_; i++) {
     combined_chain.array_[i] = c2[counter];
     counter++;
   }
   return combined_chain;
 }

 // Overloaded + operator using one chain and item
 // Appends to end of chain
 friend Chain operator+(Chain &c1, const Object &item) {

   // Here we need to create a new array,
   // with size 1 greater
   // Copy all the elements over to new array, along with item.
   Object *temp = c1.array_;
   c1.array_ = new Object[c1.size_ + 1];
   for(int i = 0; i < c1.size_; i++) {
     c1.array_[i] = temp[i];
   }
   c1.size_++;
   c1.array_[c1.size_ - 1] = item;

   // Delete the temp pointer since old array not needed
   delete [] temp;
   return c1;
 }

 // Overloading the << operator.
 friend std::ostream &operator<<(std::ostream &out, const Chain &a_chain) {

   // If chain is empty
   if(a_chain.size_ == 0) {
     out << "[]";
     return out;
   }
   out << '[';
   for(int i = 0; i < a_chain.size_-1; i++) {
     out << a_chain[i] << ' ';
   }
   out << a_chain[a_chain.size_-1] <<  ']';
   return out;
 }

 private:
  size_t size_;
  Object *array_;
};

}  // namespace teaching_project
#endif // CSCI_335_HOMEWORK1_CHAIN_
