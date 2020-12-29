/*
PROBLEM:
  Euler 75
  Given that L is the length of the wire, for how many values of L ≤ 1,500,000 
  can exactly one integer sided right angle triangle be formed?


SOLUTION:
  Pythagorean triple (https://en.wikipedia.org/wiki/Pythagorean_triple),

      $ a^2 + b^2 = ^2 $

  are given by the formula:

      $ a = (m^2 - n^2), b = 2 m n, c = (m^2 + n^2)$

  Given the triple $(a, b, c)$, $(ka, kb, kc)$ is also a solution. Using the
  above formula,

      $ l = a + b + c = 2 k m (m + n) $

  where $m > n$, $gcd(m, n) = 1$ and they are not both even. Given $l$, we 
  want to find all possible solutions.


  Here is the main idea: We first compile the list of (m, m + n). This will
  give a primitive perimeter $l = 2 m (m + n)$. Then we try to find for 
  what values of $k < floor(\frac{N_{Max}}{l})$ we have unique solutions.

  Now, if $2 k m (m + n)$ corresponds to another distinct solution, then 
  either $k$ contains a product of a distinct pair of (m, m + n), or $k$
  together with $m$ or $m+n$ forms a pair.

  The last observation we make is that if for a $k$ and a primitive solution
  pair $(m, m + n)$ there exists multiple solutions, then there will be
  multiple solutions for any multiple of $k$ with the same primitive pair.


  ANSWER: 
    Number of primitive solutions: 105353
    Number of solutions less than 1500000: 161667
 **/

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <iterator>


typedef unsigned long int ULInt;
typedef std::vector<ULInt> ULIntVec;
typedef std::map<ULInt, ULInt> ULIntMap;


ULInt euclid(ULInt a, ULInt b)
{
   ULInt temp;
  if (a < b) {
    temp = a;
    a = b;
    b = temp;
  }
  while (b != 0) {
    temp = b;
    b = a % b;
    a = temp;
  }
  //
  return a;
}


inline bool relatively_prime(ULInt a, ULInt b)
{
  // if (a % 2 == 0 && b % 2 == 0) {
  //   return false;
  // }
  return (euclid(a, b) == 1);
}


int main()
{
  const ULInt UPPER_LIMIT = 1500000;

  // Compile the list of pairs of (m, m+n) associated with primitive triples: 
  ULIntVec primitives;
  ULInt l;
  for (ULInt m = 2; m * m < UPPER_LIMIT; m++) {
    for (ULInt n = 1; n < m; n ++) {
      if (m % 2 == n % 2) {
        continue;  // (m, n) pair will not yield a primitive triple.
      }
      if (relatively_prime(m, n)) {
        l = 2 * m * (m + n);
        if (l >= UPPER_LIMIT) { 
          break;
        }
        primitives.push_back(l);
      }
    }
  }
  std::cout << "Number of primitive solutions: " << primitives.size() << std::endl;

  // Find candidates:
  ULInt* candidate_array = new ULInt[UPPER_LIMIT];
  for (ULInt idx = 0; idx < UPPER_LIMIT; idx++) {
    candidate_array[idx] = 0;
  }
  for (ULIntVec::iterator it = primitives.begin(); it != primitives.end(); it++) {
    for (ULInt k = *it; k < UPPER_LIMIT; k += *it) {
      candidate_array[k] += 1;
    }
  }

  // Count solutions:
  ULInt count = 0;
  for (ULInt idx = 0; idx < UPPER_LIMIT; idx++) {
    if (candidate_array[idx] == 1) {
      count++;
    }
  }
  std::cout << "Number of solutions less than " << UPPER_LIMIT 
            << ": " << count << std::endl;


  delete[] candidate_array;
  return 0;
}
