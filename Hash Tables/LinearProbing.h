#ifndef LINEAR_PROBING_H
#define LINEAR_PROBING_H

#include <vector>
#include <algorithm>
#include <functional>
#include "Functions.h"


// Linear probing implementation.
template <typename HashedObj>
class HashTableLinear {
 public:
  enum EntryType {ACTIVE, EMPTY, DELETED};

  explicit HashTableLinear(size_t size = 101) : array_(NextPrime(size))
    { MakeEmpty(); }

  bool Contains(const HashedObj & x) const {
    return IsActive(FindPos(x));
  }

  void MakeEmpty() {
    current_size_ = 0;
    for (auto &entry : array_)
      entry.info_ = EMPTY;
  }

  int NumberOfCollisions() const {
    return number_of_collisions_;
  }

  int TableSize() const {
    return array_.size();
  }

  int NumberOfElements() const {
    return current_size_;
  }

  float LoadFactor() const {
    float load_factor_ = float(current_size_) / array_.size();
    return load_factor_;
  }

  float AverageNumberCollisions() const {
    float average_collisions_ = float(number_of_collisions_) / current_size_;
    return average_collisions_;
  }

  void ResetCollisions() {
    number_of_collisions_ = 0;
  }

  bool Insert(const HashedObj & x) {
    // Insert x as active
    size_t current_pos = FindPos(x);
    if (IsActive(current_pos))
      return false;

    array_[current_pos].element_ = x;
    array_[current_pos].info_ = ACTIVE;

    // Rehash; see Section 5.5
    if (++current_size_ > array_.size() / 2)
      Rehash();
    return true;
  }

  bool Insert(HashedObj && x) {
    // Insert x as active
    size_t current_pos = FindPos(x);
    if (IsActive(current_pos))
      return false;

    array_[current_pos] = std::move(x);
    array_[current_pos].info_ = ACTIVE;

    // Rehash; see Section 5.5
    if (++current_size_ > array_.size() / 2)
      Rehash();

    return true;
  }

  bool Remove(const HashedObj & x) {
    size_t current_pos = FindPos(x);
    if (!IsActive(current_pos))
      return false;

    array_[current_pos].info_ = DELETED;
    return true;
  }

 private:
  struct HashEntry {
    HashedObj element_;
    EntryType info_;

    HashEntry(const HashedObj& e = HashedObj{}, EntryType i = EMPTY)
    :element_{e}, info_{i} { }

    HashEntry(HashedObj && e, EntryType i = EMPTY)
    :element_{std::move(e)}, info_{ i } {}
  };


  std::vector<HashEntry> array_;
  size_t current_size_;
  mutable int number_of_collisions_ = 0;

  bool IsActive(size_t current_pos) const
  { return array_[current_pos].info_ == ACTIVE; }

  size_t FindPos(const HashedObj & x) const {
    size_t current_pos = InternalHash(x);

    while (array_[current_pos].info_ != EMPTY &&
	   array_[current_pos].element_ != x) {
      number_of_collisions_++; // Increment Collisions
      current_pos++;  // Compute ith probe.
      if (current_pos >= array_.size())
	current_pos -= array_.size();
    }
    return current_pos;
  }

  void Rehash() {
    std::vector<HashEntry> old_array = array_;

    // Create new double-sized, empty table.
    array_.resize(NextPrime(2 * old_array.size()));
    for (auto & entry : array_)
      entry.info_ = EMPTY;

    // Copy table over.
    current_size_ = 0;
    for (auto & entry :old_array)
      if (entry.info_ == ACTIVE)
	Insert(std::move(entry.element_));
  }

  size_t InternalHash(const HashedObj & x) const {
    static std::hash<HashedObj> hf;
    return hf(x) % array_.size( );
  }
};

#endif
