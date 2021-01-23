/* 
PROBLEM:
  Euler 88
  A natural number, N, that can be written as the sum and product of a given set of at least two
  natural numbers, {a1, a2, ... , ak} is called a product-sum number: 

        N = a1 + a2 + ... + ak = a1 × a2 × ... × ak.

  For example, 6 = 1 + 2 + 3 = 1 × 2 × 3.

  For a given set of size, k, we shall call the smallest N with this property a minimal product-
  sum number. The minimal product-sum numbers for sets of size, k = 2, 3, 4, 5, and 6 are as 
  follows.

        k=2:  4 = 2 × 2 = 2 + 2
        k=3:  6 = 1 × 2 × 3 = 1 + 2 + 3
        k=4:  8 = 1 × 1 × 2 × 4 = 1 + 1 + 2 + 4
        k=5:  8 = 1 × 1 × 2 × 2 × 2 = 1 + 1 + 2 + 2 + 2
        k=6: 12 = 1 × 1 × 1 × 1 × 2 × 6 = 1 + 1 + 1 + 1 + 2 + 6

  Hence for 2≤k≤6, the sum of all the minimal product-sum numbers is 4+6+8+12 = 30; note that 8 
  is only counted once in the sum.

  In fact, as the complete set of minimal product-sum numbers for 2≤k≤12 is {4, 6, 8, 12, 15, 16},
  the sum is 61.

  What is the sum of all the minimal product-sum numbers for 2 ≤ k ≤ 12000?  


SOLUTION:
  Clearly brute-force solution is not going to get anywhere. So, instead of finding these, we try 
  to generate them. Since we are interested in the smallest of such product-sum natural numbers, we 
  start from 1 and for each non-prime number, N, consider all possible ways of decomposing it into 
  divisors larger than 1. The difference between the number and the sum of those divisors provides 
  a product sum. We keep the smallest ones in a map.

  To generate the divisors efficiently, I will use dynamic programming: For n, I first fine its 
  greatest divisor. If this greatest divisor is a prime number, there is only one way to write n in
  terms of its divisors. If n's greatest divisor is not a prime number, then we must have already 
  encountered it. The decompositions of n are then can be obtained from those of its greatest divisor.

  Once we have the decompositions, we can compute the length of the corresponding product-sums as 
  outlined above.


  ANSWER: 
 **/

#include <iostream>
#include <iomanip>
#include <vector>
#include <set>
#include <map>
#include <iterator>
#include <algorithm>


typedef unsigned long int ULInt;

typedef std::vector<ULInt> ULIntVec;
typedef std::vector<ULInt>::iterator ULIntVecIt;
typedef std::vector<ULInt>::const_iterator ULIntConstVecIt;

typedef std::set<ULInt> ULIntSet;
typedef std::set<ULInt>::iterator ULIntSetIt;
typedef std::set<ULInt>::const_iterator ULIntConstSetIt;
typedef std::set<ULInt>::reverse_iterator ULIntSetRit;

typedef std::map<ULInt, ULInt> ULIntMap;
typedef std::map<ULInt, ULInt>::iterator ULIntMapIt;
typedef std::map<ULInt, ULInt>::const_iterator ULIntConstMapIt;


ULIntSet set_of_primes(ULInt upper_limit)
/* Returns all the primes in the range (1, upper_limit)
 **/
{
  ULIntSet primes;
  primes.insert(2);
  primes.insert(3);
  primes.insert(5);

  ULIntSetIt it;
  ULInt n;
  bool is_prime;
  ULInt k = 6;
  while (*primes.rbegin() < upper_limit) {
    // n % 6 = 1 case:
    n = k + 1;
    is_prime = true;
    for (it = primes.begin(); it != primes.end() && (*it) * (*it) <= n; it++) {
      if (n % *it == 0) {
        is_prime = false;
        break;
      }
    }
    if (is_prime) {
      primes.insert(n);
    }
    //
    // n % 6 = 5 case:
    n = k + 5;
    is_prime = true;
    for (it = primes.begin(); it != primes.end() && (*it) * (*it) <= n; it++) {
      if (n % *it == 0) {
        is_prime = false;
        break;
      }
    }
    if (is_prime) {
      primes.insert(n);
    }
    //
    k += 6; 
  }

  while (*primes.rbegin() > upper_limit) {
    primes.erase(*primes.rbegin());
  }

  return primes;
}


ULIntMap decompose(ULInt n, const ULIntVec& primes)
{
  ULIntMap decomposition;
  for (ULIntConstVecIt it = primes.begin(); it != primes.end() && n >= *it; it++) {
    if (n % *it == 0) {
      decomposition[*it] = 1;
      n /= *it;
      while (n % *it == 0) {
        decomposition[*it] += 1;
        n /= *it;
      }
    }
  }

  return decomposition;
}


void print(const ULIntVec& vec, bool comma=false) {
  if (comma) {
    std::cout << "\t";
    ULIntConstVecIt it = vec.begin();
    std::cout << *it;
    it++;
    while (it != vec.end()) {
      std::cout << ", " << *it;
      it++;
    }
  }
  else {
    for (ULIntConstVecIt it = vec.begin(); it != vec.end(); it++) {
      std::cout << "\t" << *it << std::endl;
    }
  }
}


int main()
{
  const ULInt MAX_LENGTH = 12000; // 12; // 6;
  const ULInt MAX_N = 2 * MAX_LENGTH + 1;  // MAX_LENGTH 2s is a solution!
  const bool VERBOSE = !true; 

  ULIntSet primes = set_of_primes(MAX_N);

  ULIntMap product_sums;  // A map of product-sum length to smallest instance.
  std::map<ULInt, std::set<ULIntVec> > divisor_decomps;
  ULInt n = 4;
  ULInt gd, p;
  ULInt largest_continuous_length = 1;
  ULInt temp_length;
  while (largest_continuous_length < MAX_LENGTH && n < MAX_N) {
    if (primes.find(n) != primes.end()) {
      n++;
      continue; 
    }
    else {
      // Find the greatest divisor of n:
      for (ULIntSetIt it = primes.begin(); it != primes.end(); it++) {
        if (n % *it == 0) {
          gd = n / *it;  // Since *it is the smallest prime factor, this fraction is gd.
          p = *it; // Smallest prime divisor of n;
          break;
        }
      }
      
      if (VERBOSE) {
        std::cout << n << " = " << p << " * " << gd << std::endl;
      }

      // This will always have to be there!
      divisor_decomps[n].insert(ULIntVec({p, gd}));

      // Check if we have this in divisor_decomps:
      if (divisor_decomps.find(gd) != divisor_decomps.end()) {
        for (std::set<ULIntVec>::iterator sit = divisor_decomps[gd].begin(); 
        sit != divisor_decomps[gd].end(); sit++) {
          // Append to the previous decompositions:
          ULIntVec temp_vec(*sit);
          temp_vec.push_back(p);
          std::sort(temp_vec.begin(), temp_vec.end());
          divisor_decomps[n].insert(temp_vec);
          //
          // Multiply to each of the previous values:
          ULInt idx = 0;
          while (idx < sit->size()) {
            // Skip duplicates:
            while ((idx + 1) < sit->size() && (*sit)[idx] == (*sit)[idx + 1]) {
              idx++;
            }
            ULIntVec temp_vec(*sit);
            temp_vec[idx] *= p;
            std::sort(temp_vec.begin(), temp_vec.end());
            divisor_decomps[n].insert(temp_vec);
            idx++;
          }
        }

        // Finally, compute lengths based on the decompositions:
        for (std::set<ULIntVec>::iterator sit = divisor_decomps[n].begin(); 
        sit != divisor_decomps[n].end(); sit++) {
          temp_length = n;
          for (ULIntConstVecIt vit = sit->begin(); vit != sit->end(); vit++) {
            temp_length -= (*vit - 1);
          }
          if (product_sums.find(temp_length) != product_sums.end()) {
            // If we have encountered a product_sum of the same length, update with the smaller.
            product_sums[temp_length] = std::min(n, product_sums[temp_length]);
          }
          else {
            // If we have not encountered this length, store it.
            product_sums[temp_length] = n;
          }

          if (VERBOSE) {
            print(*sit, true);
            std::cout << "\n\t" << temp_length << std::endl;
          }
        }
        if (VERBOSE) {
          std::cout << std::endl;
        }
      } 
      else {
        // If we have not already visited it, then it must be a prime!
        if (primes.find(gd) == primes.end()) {
          std::cout << "ERROR: " << gd << " is neither a prime nor already visited!" 
                    << std::endl;
          throw;
        }

        temp_length = n - (p + gd) + 2;
        if (product_sums.find(temp_length) != product_sums.end()) {
          // If we have encountered a product_sum of the same length, update with the smaller.
          product_sums[temp_length] = std::min(n, product_sums[temp_length]);
        }
        else {
          // If we have not encountered this length, store it.
          product_sums[temp_length] = n;
        }
        
        if (VERBOSE) {
          print(*divisor_decomps[n].begin(), true);
            std::cout << "\n\t" << temp_length << std::endl << std::endl;
        }
      }
    }

    // Updated the largest length that we have all values before it: 
    while (product_sums.find(largest_continuous_length + 1) != product_sums.end()) {
      largest_continuous_length++;
      // std::cout << "\t\t\t*** " << largest_continuous_length << " *** " << std::endl;
    }
    n++;
  }

  // Print the sum of unique minimal product-sum numbers:
  ULInt sum = 0;
  ULIntSet already_visited;
  for (ULIntMapIt mit = product_sums.begin(); mit != product_sums.end(); mit++) {
    if (mit->first > MAX_LENGTH) {
      break;
    }

    if (already_visited.find(mit->second) == already_visited.end()) {
      already_visited.insert(mit->second);
      sum += mit->second;
    }
    if (VERBOSE) {
      std::cout << std::setw(10) << mit->first
                << std::setw(10) << mit->second << std::endl;
    }
  }
  std::cout << "Sum of smallest product-sum numbers below "
            << MAX_LENGTH << " is " 
            << sum << std::endl;
  
  return 0;
}
