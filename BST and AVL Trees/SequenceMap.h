#ifndef SEQUENCE_MAP_H
#define SEQUENCE_MAP_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// SequenceMap class
// Contains a recognition sequence and vector of enzyme acronyms
// Default big five
// This class is just the object for this project, which deals
// with dna sequences and their correlating enzymes

class SequenceMap {
public:

  // Default big five
  SequenceMap() = default;
  SequenceMap(const SequenceMap &rhs) = default;
  SequenceMap& operator=(const SequenceMap &rhs) = default;
  SequenceMap(SequenceMap &&rhs) = default;
  SequenceMap& operator=(SequenceMap &&rhs) = default;
  ~SequenceMap() = default;

  // 2 parameter constructor, using a recongnition string and
  // setting the enzyme acronym vector to one element
  SequenceMap(const string &a_rec_seq, const string &an_enz_acro) :
    recognition_sequence_{a_rec_seq}, enzyme_acronyms_{an_enz_acro} {}

  // < Operator overload, which compares 2 SequenceMaps by their
  // recognition sequence string
  bool operator<(const SequenceMap &rhs) const {
    return recognition_sequence_ < rhs.recognition_sequence_;
  }

  // Overloaded << operator, which prints the associated enzymes
  // Printed last element of vector without following space
  friend ostream &operator<<(ostream &out, const SequenceMap &s) {
    for(int i = 0; i < s.enzyme_acronyms_.size() - 1; i++) {
      out << s.enzyme_acronyms_[i] << " ";
    }
    out << s.enzyme_acronyms_[s.enzyme_acronyms_.size() - 1];
    return out;
  }

  // Pushback the elements of second vector to the 1st vector
  void Merge(const SequenceMap &other_sequence) {
    for(int i = 0; i < other_sequence.enzyme_acronyms_.size(); i++) {
      enzyme_acronyms_.push_back(other_sequence.enzyme_acronyms_[i]);
    }
  }
  
private:
  string recognition_sequence_;
  vector<string> enzyme_acronyms_;
};

#endif
