/*
PROBLEM:
  Euler 70
  Find the value of n, 1 < n < 10^7, for which φ(n) is a permutation of n and the 
  ratio n/φ(n) produces a minimum.

SOLUTION:
  Euler's totient function for 

        $n = p_{0}^{l_0} p_{1}^{l_1} \cdots  p_{m}^{l_m}$
  is given by:

        $\phi(n) = n * \frac{(p_0 - 1)(p_1 - 1)\cdots(p_m - 1)}{p_0 p_1 \cdots p_m}$ 

  We make the observation that the ratio $n / \phi(n)$, which is    

        $\frac{(p_0 - 1)(p_1 - 1)\cdots(p_m - 1)}{p_0 p_1 \cdots p_m}$, 
  is minimized when $l_0 = l_1 = \cdots = l_m = 1$ and when $p_{l}$'s are as large
  as possible.

  
  Now, to solve the n for which $n/\phi(n)$ is minimized and \phi(n) and n are
  permutations of one another, we need to search the n's on an ascending order of 
  $n/\phi(n)$.

  For this, we construct n from primes. We first search n values of the form:
        
        $ n = p_0 p_1$

  If we do not find a solution, we move on to three-prime products, etc. 

  ANSWER: 
  Two-prime solution: (2339, 3557)  n: 8319823   phi: 8313928 Ratio: 1.00071
  This solution took about 9 seconds...
**/

#include <iostream>
#include <vector>
#include <algorithm>


typedef unsigned long int ULInt;
typedef std::vector<ULInt> ULIntVec;

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


ULIntVec digits(ULInt n, bool sorted=true)
{
  ULIntVec digits;
  while (n > 0) {
    digits.push_back(n % 10);
    n /= 10;
  }

  if (sorted) {
    std::sort(digits.begin(), digits.end());
  }

  return digits;
}


bool are_permutations(ULInt a, ULInt b)
{
  ULIntVec a_digits = digits(a, true);
  ULIntVec b_digits = digits(b, true);
  return (a_digits == b_digits);
}


int main()
{
  const ULInt MAX_N = 10000000;

  // First, compile the list of primes:
  ULIntVec primes = list_of_primes(MAX_N);
  std::cout << "\tNum primes: " << primes.size() 
            << "\n\tLast Prime: " << primes.back() << std::endl;

  // Two-prime candidates:
  ULInt sqrt_idx = 0;
  while (sqrt_idx < primes.size()) {
    if (primes[sqrt_idx] * primes[sqrt_idx] >= MAX_N) {
      sqrt_idx--;
      break;
    }
    sqrt_idx++;
  }
  std::cout << "\tSqrt(" << MAX_N << ") > "
            << "p_{"     << sqrt_idx << "} = " << primes[sqrt_idx] << std::endl;
  //
  ULInt idx_h, idx_l;
  ULInt n, phi_n;
  idx_h = sqrt_idx + 1;
  idx_l = sqrt_idx - 1;
  ULInt p_0, p_1;
  float ratio, min_ratio;
  min_ratio = 1000.0;
  for (idx_h = (sqrt_idx + 1); idx_h < primes.size(); idx_h++) {
    for (idx_l = (sqrt_idx - 1); idx_l > 0; idx_l--) {
      n = primes[idx_l] * primes[idx_h];
      if (n > MAX_N) {
        continue;
      }
      else {
        phi_n = (primes[idx_l] - 1) * (primes[idx_h] - 1);
        ratio = (float)(n) / (float)(phi_n);
        if (ratio > min_ratio) {
          break;
        }
        if (are_permutations(n, phi_n)) {
            std::cout << "\t(" << primes[idx_l] << ", " << primes[idx_h] << ")\tn = " 
                      << n << ", phi = " << phi_n << "\tRatio: " << ratio << std::endl;
          if (ratio < min_ratio) {
            p_0 = primes[idx_l];
            p_1 = primes[idx_h];
            min_ratio = ratio;
          }
        }
      }
    }
  }
  std::cout << "Two-prime solution: (" << p_0 << ", " << p_1 << ")"
            << "\tn: " << p_0 * p_1 << "\t phi: " << (p_0 - 1) * (p_1 - 1)
            << "\tRatio: " << min_ratio << std::endl;

  return 0;
}
