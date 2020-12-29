/*
PROBLEM:
  Euler 73
  How many fractions lie between 1/3 and 1/2 in the sorted set of reduced 
  proper fractions for d ≤ 12,000?




SOLUTION:
  SOLUTION 1:
  The idea is to generate candidates: $\frac{k - m}{2k + n}$ where $k$ is
  in the range $\{1, 2, \cdots, N_{Max} / 2\}$. Also, $m$ and $n$ has to 
  satisfy $3m + n < k$.

  The bottle neck in this solution is identifying irreducible pairs in the
  proposed candidates.


  SOLUTION 2:
  I originally solved this problem using `Solution_1::numeber_of_fractions()`.
  Later on, I learned about the Farey's sequence. For more details on this,
  see: https://en.wikipedia.org/wiki/Farey_sequence
  This is considerably faster.

  The maini idea is to use the "median property":

       $ \frac{a}{b} < \frac{p}{q} < \frac{c}{d} $ 

  are the consecutive terms in the nth Farey sequence, then,

       $ \frac{p}{q} = \frac{a + c}{b + d} $

  Now, for a given n (in this case 12000), we want the Farey rations between
  1/3 and 1/2. For this, we start with the first two terms and generate the rest
  until we reach 1/2. The first term is $\frac{1}{3}$. The next one is: 

       $ \frac{4000}{3 * 4000 - 1} $

  (This is the smallest irreducible fraction greater than 1/3 with a denominator
  smaller than 12000.)

  We use the median property next:

       $ \frac{a}{b} < \frac{c}{d} < \frac{x}{y} $

  Therefore,

       $ \frac{c}{d} = \frac{a + x}{b + y} $

  Since, $gcd(c, d) = 1$, $c * k = a + x$ and $d * k = y + b$. To find x and y, 
  we utilize one more property of the Farey sequences: The property if neighbors.
  If $\frac{p_1}{q_1}$ and $\frac{p_2}{q_2}$ are neighbors, in the sense that in
  the nth Farey sequence there is no term in between them, then: 

      $ q_1 p_2 - q_2 p1 = 1 $

  Imposing the constraint that $\frac{c}{d}$ and $\frac{x}{y}$ are neighbors, we
  have:

      $ x * d - y * c  = (c * k - a) * d - (d * k - b) * c = 1 $

  which is automatically satisfied if the first two are neighbors. To ensure they
  are neighbors in the nth Farey sequence, we demand that $k$ to be as large as 
  possible, i.e., $d * k - b \leq n$. Thus, $k = \floor(\frac{n + b}{d})$   


  ANSWER: 7295372
 **/

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>


typedef unsigned long int ULInt;

namespace Solution_1{
  ULInt euclid_gcd(ULInt a, ULInt b)
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
    return a;
  }


  inline bool relatively_prime(ULInt a, ULInt b)
  {
    if (a % 2 == 0 && b % 2 == 0) {
      return false;
    }
    return (euclid_gcd(a, b) == 1);
  }

  ULInt numeber_of_fractions(const ULInt n_max, const bool print_fractions=false)
  {
      ULInt count = 0;
    ULInt base_numerator, base_denominator;
    ULInt numerator, denominator;
    for (ULInt k = 1; k < n_max / 2; k++) {
      base_numerator = k;
      base_denominator = 2 * k;

      // base_numerator - m / base_denominator case:
      for (ULInt m = 1; 3 * m < k; m++) {
        numerator = base_numerator - m;
        denominator = base_denominator;
        numerator = base_numerator - m;
        if (relatively_prime(numerator, denominator)) {
          if (print_fractions) { 
            std::cout << "\t" << numerator << "/" << denominator << std::endl;
          }
          count += 1;
        }
      }

      // base_numerator - m / base_denominator + 1 case:
      for (ULInt m = 0; 3 * m + 1 < k; m++) {
        numerator = base_numerator - m;
        denominator = base_denominator + 1;
        numerator = base_numerator - m;
        if (relatively_prime(numerator, denominator)) {
          if (print_fractions) { 
            std::cout << "\t" << numerator << "/" << denominator << std::endl;
          }
          count += 1;
        }
      }
    }

    if (n_max % 2 == 0) {
      ULInt k = n_max / 2;
      base_numerator = k;
      denominator = n_max;
      for (ULInt m = 1; 3 * m < k; m++) {
        numerator = base_numerator - m;
        if (relatively_prime(numerator, denominator)) {
          if (print_fractions) { 
            std::cout << "\t" << numerator << "/" << denominator << std::endl;
          }
          count += 1;
        }
      }
    }

    return count;
  }
};


namespace Solution_2{
  ULInt numeber_of_fractions(ULInt n_max,
    ULInt lower_numerator=0, ULInt lower_denominator=1,
    ULInt upper_numerator=1, ULInt upper_denominator=1)
  /* Using Farey sequence (see: https://en.wikipedia.org/wiki/Farey_sequence). 
   **/
  {
    ULInt a, b, c, d;
    a = lower_numerator;
    b = lower_denominator;
    c = upper_numerator;
    d = upper_denominator;
    
    ULInt count = 0;
    ULInt k, temp_a, temp_b;
    while (!(c == 1 && d == 2)) {
      k = (n_max + b) / d;
      temp_a = a;
      temp_b = b;
      a = c;
      b = d;
      c = k * c - temp_a;
      d = k * d - temp_b;
      // std::cout << "\t" << a << "/" << b << std::endl;
      count += 1;
    }

    return count;
  }
};


int main()
{
  const ULInt MAX_N = 12000;

  // // Solution 1:
  // std::cout << "Number of irreduciable fractions: " 
  //           << Solution_1::numeber_of_fractions(MAX_N) << std::endl;

  // Solution 2:
  std::cout << "Number of irreduciable fractions: " 
            << Solution_2::numeber_of_fractions(MAX_N, 1, 3, MAX_N / 3, MAX_N - 1) << std::endl;

	return 0;
}
