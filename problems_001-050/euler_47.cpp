/*
PROBLEM:
  The first two consecutive numbers to have two distinct prime factors are:

        14 = 2 × 7
        15 = 3 × 5

  The first three consecutive numbers to have three distinct prime factors are:

        644 = 2^2 × 7 × 23
        645 = 3 × 5 × 43
        646 = 2 × 17 × 19.

  Find the first four consecutive integers to have four distinct prime factors each. What is the
  first of these numbers?


SOLUTION:
  The brute-force search will be grossly inefficient. The inefficiency stems from the fact that


  ANSWER: 134043
**/

#include "iostream"
#include "set"
#include "iterator"
#include "math.h"


typedef unsigned long int ulint;


bool is_prime(ulint n)
{
  if (n == 2) return true;
  else if (n % 2 == 0) return false;
  else if (n == 3) return true;
  else if (n % 3 == 0) return false;
  else if (n == 5) return true;
  else if (n % 5 == 0) return false;
  else if (n == 7) return true;
  else if (n == 11) return true;
  else if (n == 13) return true;
  else if (n == 17) return true;
  else if (n == 19) return true;

  ulint k = 6;
  while (k * k <= n) {
    if (n % (k + 1) == 0) return false;
    if (n % (k + 5) == 0) return false;
    k += 6;
  }

  return true;
}

namespace solution1 {
  unsigned int number_of_distinct_prime_factors(ulint n , const std::set<ulint> &primes)
  {
    unsigned int count = 0;
    std::set<ulint>::const_iterator it;
    for(it = primes.begin() ; it != primes.end() ; it++ ) {
      if (n % *it == 0) {
        count++;
      }
    }

    return count;
  }

  unsigned int brute_force_search(unsigned int number_of_factors)
  {
    std::set<ulint> primes;
    primes.insert(2);
    primes.insert(3);
    primes.insert(5);

    ulint n = 6;
    while (true) {
      while (is_prime(n)) { 
        primes.insert(n);   
        n++;
      }  

      if (number_of_distinct_prime_factors(n + 3, primes) == number_of_factors) {
        if (number_of_distinct_prime_factors(n + 2, primes) == number_of_factors) {
          if (number_of_distinct_prime_factors(n + 1, primes) == number_of_factors) {
            if (number_of_distinct_prime_factors(n, primes) == number_of_factors)
              break;
            else {
              n += 1;
            }
          }
          else {
            if (is_prime(n + 1)) 
              primes.insert(n + 1);
            n += 2;
          }
        }
        else {
          if (is_prime(n + 1)) 
            primes.insert(n + 1);
          if (is_prime(n + 2)) 
            primes.insert(n + 2);
          n += 3;
        }
      }
      else {
        if (is_prime(n + 1)) 
          primes.insert(n + 1);
        if (is_prime(n + 2)) 
          primes.insert(n + 2);
        if (is_prime(n + 3)) 
          primes.insert(n + 3);
        n += 4;
      }
    }

    return n;
  }
}


namespace solution2 {

}


int main()
{ 
  std::cout << "The first number is: " << solution1::brute_force_search(4) << std::endl;

  return 0;
}
