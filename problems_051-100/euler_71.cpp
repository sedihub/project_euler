/*
PROBLEM:
  Euler 71
  By listing the set of reduced proper fractions for d ≤ 1,000,000 in ascending 
  order of size, find the numerator of the fraction immediately to the left of 3/7.


SOLUTION:
  3/7 ---> 3k/7k

  Numerator: 3k, (3k + 1), (3k + 2)
  Denominator: (7k + 1), (7k + 2), ..., (7k + 6)

  First, are there any combinations of these 12 candidates fro each k that is
  greater than 3/7?

  (3k + m)/(7k + n) < 3/7
  21k + 7m < 21k + 3n
  7m < 3n  ----> if m = 1, then n has to be at least 3
                 if m = 2, then n can only take the values 5 or 6
  
  Next, let's determine the (descending) ordering of the candidates:

    (3k + m1)/(7k + n1) < (3k + m2)/(7k + n2)
    ---> 21k^2 + 7k*m1 + 3k*n2 + m1*n2 < 21k^2 + 7k*m2 + 3k*n1 + m2*n1
         7k * (m1 - m2) + 3k * (n2 - n1) + (m1 * n2 - m2 * n1) < 0
         k * (7(m1 - m2) + 3(n2 - n1)) < m2 * n1 - m1 * n2    

  Thus, we explore the pairs in the following order:

    (2, 5) (1, 3) (0, 1)
    (2, 6) (1, 4) (0, 2)
           (1, 5) (0, 3)
           (1, 6) (0, 4)
                  (0, 5)
                  (0, 6)  

  ANSWER: 428570 / 999997 = 0.428571
**/

#include <iostream>
#include <vector>
#include <algorithm>


typedef unsigned long int ULInt;
typedef std::vector<ULInt> ULIntVec;


ULInt euclid(ULInt a, ULInt b)
{
   ULInt temp;
  if (a < b) {
    temp = a;
    a = b;
    b = temp;
  }
  // else if (a == b) {
  //   return a;
  // }
  //
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
  return (euclid(a, b) == 1);
}


int main()
{
  const ULInt MAX_N = 1000000;

  ULIntVec numer_vec = {2, 1, 0, 2, 1, 0, 1, 0, 1, 0, 0, 0};
  ULIntVec denom_vec = {5, 3, 1, 6, 4, 2, 5, 3, 6, 4, 5, 6};

  ULInt numerator, denominator;
  ULInt max_numerator, max_denominator;
  max_numerator = 2;
  max_denominator = 5;
  for (ULInt k = MAX_N / 7; k > 2; k--) {
    for (ULInt idx = 0; idx < numer_vec.size(); idx++) {
      numerator = k * 3 + numer_vec[idx];
      denominator = k * 7 + denom_vec[idx];
      if (relatively_prime(numerator, denominator) && denominator < MAX_N) {
        std::cout << numerator << " / " << denominator << " = "
                  << (float)numerator / (float)denominator << std::endl;
        goto FOUND_PAIR;
      }
    }
  }
  FOUND_PAIR:;

  return 0;
}
