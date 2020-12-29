/*
PROBLEM:
  Euler 72
  Consider the fraction, n/d, where n and d are positive integers. If n<d 
  and HCF(n,d)=1, it is called a reduced proper fraction.

  If we list the set of reduced proper fractions for d ≤ 8 in ascending 
  order of size, we get:

      1/8, 1/7, 1/6, 1/5, 1/4, 2/7, 1/3, 3/8, 2/5, 3/7, 1/2, 4/7, 
      3/5, 5/8, 2/3, 5/7, 3/4, 4/5, 5/6, 6/7, 7/8

  It can be seen that there are 21 elements in this set.

  How many elements would be contained in the set of reduced proper fractions 
  for d ≤ 1,000,000?


SOLUTION:
  We need the number of $m/n$ fractions such that $gcd(m, n) = 1$ and $m < n$ and 
  $n \leq 10^6$.

  This is the same as $n/m$ fractions such that $gcd(n, m) = 1$ and $n > m$. 
  Thus, for a given $n$ we are there are $phi(n)$ $m$'s.

  The answer, therefore, is:

        $\sum_{n = 1}^{10^6} \phi(n)$

  We need to compute this sum in an efficient way.


  ANSWER: 303963552391
  (Took 5 seconds...)
**/

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>


typedef unsigned long int ULInt;
typedef std::vector<ULInt> ULIntVec;
typedef std::map<ULInt, ULInt> ULIntMap;


namespace Solution_1{
  ULIntVec list_of_primes(ULInt max_n)
  {
    ULIntVec primes = {2, 3, 5};
    ULIntVec::iterator it;
    for (ULInt n = 6; n < max_n; n += 6) {
      it = primes.begin();
      while (it != primes.end() && (*it) * (*it) <= (n + 1)) {
        if ((n + 1) % (*it) == 0) {
          goto CONT1;
        }
        it++;
      }
      primes.push_back(n + 1);
      CONT1:;
      //
      it = primes.begin();
      while (it != primes.end() && (*it) * (*it) <= (n + 5)) {
        if ((n + 5) % (*it) == 0) {
          goto CONT2;
        }
        it++;
      }
      primes.push_back(n + 5);
      CONT2:;
    }
    while (primes.back() > max_n) {
      primes.pop_back();
    }

    return primes;
  }

  ULIntMap deomposion(ULInt n, const ULIntVec &primes)
  {
    ULIntMap decom;
    ULIntVec::const_iterator it;
    for (it = primes.begin(); it != primes.end() && n > 1; it++) {
      if (n % (*it) == 0) {
        decom[*it] = 1;
        n /= (*it);
      }
      while (n % (*it) == 0) {
        decom[*it] += 1;
        n /= (*it);
      }
    }

    return decom;
  }

  // void merge_decmpositions(ULIntMap &decomp1, const ULIntMap &decomp2){
  //   ULIntMap::const_iterator mit;
  //   for (mit = decomp2.begin(); mit != decomp2.end(); mit++) {
  //     if (decomp1.find(mit->first) != decomp1.end()) {
  //       decomp1[mit->first] += mit->second;
  //     }
  //     else {
  //       decomp1[mit->first] = mit->second;
  //     }
  //   }
  // }

  void print_decomp(const ULIntMap &decomp)
  {
    ULIntMap::const_iterator mit;
    for (mit = decomp.begin(); mit != decomp.end(); mit++) {
      std::cout << mit->first << "^" << mit->second << " ";
    }
  }

  ULInt phi(ULInt n, const ULIntMap &decomp) {
    ULIntMap::const_iterator mit;
    for (mit = decomp.begin(); mit != decomp.end(); mit++) {
      n /= mit->first;
      n *= (mit->first - 1); 
    }
    return n;
  }

  ULInt sum_phi(ULInt n_max) {
    // First, compile the list of primes:
    ULIntVec primes = list_of_primes(n_max);
    std::cout << "\tNum primes: " << primes.size() 
              << "\n\tLast Prime: " << primes.back() << std::endl;

    ULInt sum = 0;
    ULInt phi_n;
    ULIntMap decomp;
    for (ULInt n = 2; n <= n_max; n++) {
      decomp = deomposion(n, primes);
      phi_n = phi(n, decomp);
      sum += phi_n;
    }
    return sum;
  }
};


namespace Solution_2{
  ULInt sum_phi(ULInt n_max)
  {
    ULIntMap phi_map;
    for (ULInt n = 2; n <= n_max; n++) {
      phi_map[n] = n;
    }

    ULInt sum = 0;
    for (ULInt n = 2; n <= n_max; n++) {
      if (phi_map[n] == n) {
        for (ULInt i = n; i <= n_max; i += n) {
          phi_map[i] /= n;
          phi_map[i] *= (n - 1);
        }
      }
      sum += phi_map[n];
    }
    return sum;
  }
};


int main()
{
  const ULInt MAX_N = 1000000;

  // // Solution 1 (very slow...)
  // std::cout << Solution_1::sum_phi(MAX_N) << std::endl;

  // Solution 2
  std::cout << Solution_2::sum_phi(MAX_N) << std::endl;

  return 0;
}
