#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>
#include <algorithm>
#include <functional>


// Got rid of namespace and put these functions into this file
// Used in the 3 hash table implementations

bool IsPrime(size_t n) {
  if( n == 2 || n == 3 )
    return true;

  if( n == 1 || n % 2 == 0 )
    return false;

  for( int i = 3; i * i <= n; i += 2 )
    if( n % i == 0 )
      return false;

  return true;
}


// Internal method to return a prime number at least as large as n.
int NextPrime(size_t n) {
  if (n % 2 == 0)
    ++n;
  while (!IsPrime(n)) n += 2;
  return n;
}

#endif
