/*
PROBLEM:
  Pythagorean triple:
      a ^ 2  +  b ^ 2  =  c ^ 2  
  There exists exactly one Pythagorean triplet for which a + b + c = 1000.
  Find it!


SOLUTION:
  We could use brute force search. A more efficient solution can be constructed
  using Euclid's formula:

      a = m ^ 2 - n ^ 2
      b = 2 * m * n
      c = m ^ 2 + n ^ 2

  Given a Pythagorean triplet, {a, b, c} and k != 1, we can generate a new tripet:

      (k * a) ^ 2 + (k * b)^2  =  (k * c)^2

  Using this representation, we have:

      1000 = k * 2 * m * (m + n)
      ---> 500 = k * m * (m + n) = 2^2 * 5^3 

  Since n < m, the only possible combination is:
  	k = 1, m = 20, and n = 5

  ANSWER: 375 * 200 * 425 = 31875000
**/

#include <iostream>  

int main()
{
  int m, n, k;
  m = 20;
  n = 5;
  k = 1;
  //
  int a, b, c;
  a = m * m - n * n;
  b = 2 * m * n;
  c = m * m + n * n;
  std::cout << "\ta = " << a << std::endl;
  std::cout << "\tb = " << b << std::endl;
  std::cout << "\tc = " << c << std::endl;
  std::cout << "\ta + b + c = " << (a + b + c) << std::endl;
  std::cout << "\ta^2 + b^2 - c^2 = " << (a*a + b*b - c*c) << std::endl;
  std::cout << "a x b x c  = " << (a * b * c) << std::endl;

  return 0;
} 