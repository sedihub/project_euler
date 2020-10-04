/*
PROBLEM:
  It was proposed by Christian Goldbach that every odd composite number can be written as the sum
  of a prime and twice a square.

         9 =  7 + 2×1^2
        15 =  7 + 2×2^2
        21 =  3 + 2×3^2
        25 =  7 + 2×3^2
        27 = 19 + 2×2^2
        33 = 31 + 2×1^2

  It turns out that the conjecture was false.

  What is the smallest odd composite that cannot be written as the sum of a prime and twice a square?


SOLUTION:
  With a few helper classes we can quickly find the answer.

  ANSWER: 5777
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


bool is_square(ulint n)
{
  double d = sqrt( (double)n );
  return d == floor(d);
}


int main()
{  
  std::set<ulint> primes;
  ulint n = 1;
  ulint odd_num;
  bool satisfies_golbach_conjecture = true;
  while (satisfies_golbach_conjecture) {
    odd_num = 2 * n + 1;
    if (is_prime(odd_num)) {
      primes.insert(odd_num);
      n++;
    }
    else {
      for (std::set<ulint>::iterator it = primes.begin(); it != primes.end(); it++) {
        if (is_square((odd_num - *it) / 2)) {
          n++;
          goto proceed;
        }
      }
      satisfies_golbach_conjecture = false;
    }
    proceed:;
  }

  std::cout << "Smallest odd composite that violates Goldbach's conjecture: " << odd_num << std::endl;
  return 0;
}
