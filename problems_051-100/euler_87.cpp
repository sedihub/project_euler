/* 
PROBLEM:
  Euler 87
  The smallest number expressible as the sum of a prime square, prime cube, and prime fourth
  power is 28. In fact, there are exactly four numbers below fifty that can be expressed in 
  such a way:

      28 = 2^2 + 2^3 + 2^4
      33 = 3^2 + 2^3 + 2^4
      49 = 5^2 + 2^3 + 2^4
      47 = 2^2 + 3^3 + 2^4

  How many numbers below fifty million can be expressed as the sum of a prime square, prime 
  cube, and prime fourth power?


SOLUTION:
  A brute-force search is hopeless. A better/more efficient approach is to construct the sets
  of quadratic, cubic and quartic primes.

  We first generate a list of primes. There cannot be a prime larger than sqrt(5x10^7). For 
  this, I utilize the integer square root function I used in problem 66 so that I can try
  different upper limits.

  Once we have the list of primes, we proceed to generating quadratics, cubics and quartics
  lists. 

  Now, all we have to do is to count the triples of these that add up to a number under 5x10^7
  assuming that such sums are unique. If this assumption does not hold, we can use std::set
  to count the unique combinations at the cost of using memory.

  To count the solutions, we can use three nested for loops over the three lists. Turned out 
  that the uniqueness assumption was false. I had to use a std::set to weed out duplicates.
  This resulted in a longer execution as insertion into std::set is O(log(n))...

  ANSWER: There are 1097343 numbers under 50000000 that can be written in this way.
 **/

#include <iostream>
#include <iomanip>
#include <vector>
#include <iterator>
#include <set>


typedef unsigned long int ULInt;
typedef std::vector<ULInt> ULIntVec;
typedef std::vector<ULInt>::iterator ULIntVecIt;


ULInt ULInt_sqrt(ULInt n)
{
  if (n == 0) {
    return 0;
  }
  else if (n < 4) {
    return 1;
  }
  ULInt cand_0, cand_1;
  cand_0 = ULInt_sqrt(n >> 2) << 1;
  cand_1 = cand_0 + 1;

  if (cand_1 * cand_1 > n) return cand_0;
  else return cand_1;
}


ULIntVec get_primes(ULInt upper_limit)
/* Returns all the primes in the range (1, upper_limit)
 **/
{
  ULIntVec primes = {2, 3, 5};

  ULIntVecIt it;
  ULInt n;
  bool is_prime;
  ULInt k = 6;
  while (primes.back() < upper_limit) {
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
      primes.push_back(n);
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
      primes.push_back(n);
    }
    //
    k += 6; 
  }

  // Instead of checking things every time we add a prime, we can do this:
  // Note that the primes are added in the ascending order -- no need to use
  // std::set, etc.
  while (primes.back() > upper_limit) {
    primes.pop_back();
  }

  return primes;
}


int main()
{
  const ULInt UPPRE_LIMIT = 50000000; // 50;

  // Generate primes:
  ULIntVec primes = get_primes(ULInt_sqrt(UPPRE_LIMIT) + 1);
  // std::cout << "Number of primes under " << ULInt_sqrt(UPPRE_LIMIT) + 1
  //           << " is " << primes.size() << std::endl;

  // Generate lists of quadratics, cubics and quartics:
  ULIntVec quadratics, cubics, quartics;
  ULInt temp;
  for (ULIntVecIt it = primes.begin(); it != primes.end(); it++) {
    temp = (*it) * (*it);  //  = p^2
    if (temp < UPPRE_LIMIT) {   
      quadratics.push_back(temp);
      temp *= *it;         //  = p^3
      if (temp < UPPRE_LIMIT) {
        cubics.push_back(temp);
        temp *= *it;       //  = p^4
        if (temp < UPPRE_LIMIT) {
          quartics.push_back(temp);
        }
      }
    }
  }
  std::cout << "Quadratics: " << std::setw(5) << quadratics.size() << std::endl;
  std::cout << "Cubics:     " << std::setw(5) << cubics.size() << std::endl;
  std::cout << "Quartics:   " << std::setw(5) << quartics.size() << std::endl;

  // Count solutions:
  std::set<ULInt> numbers;
  for (ULIntVecIt it_quart = quartics.begin(); it_quart != quartics.end(); it_quart++) {
    for (ULIntVecIt it_cub = cubics.begin(); it_cub != cubics.end(); it_cub++) {
      temp = *it_quart + *it_cub;
      if (temp >= UPPRE_LIMIT) { continue; }
      for (ULIntVecIt it_quad = quadratics.begin(); it_quad != quadratics.end(); it_quad++) {
        if (*it_quad + temp < UPPRE_LIMIT) { 
          numbers.insert(*it_quad + temp); 
        }
        else { continue; }
      }
    }
  }
  std::cout << "There are " << numbers.size() << " numbers under " << UPPRE_LIMIT
            << " that can be written in this way." << std::endl;

  return 0;
}
