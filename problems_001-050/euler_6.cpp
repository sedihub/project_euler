/*
PROBLEM:
  Find the difference between the sum of the squares of the 
  first one hundred natural numbers and the square of the 
  sum.


SOLUTION:
  Using Newton's expansion for the square of the sum,

    (x_0 + x_1 + x_2 + ... + x_{n-1})^2 = 
    \sum_{i=0}^{n-1} x_i^2 + 
    2 \sum_{i,j and i < j} x_i * x_j

  Thus the difference is the sum of the products. 

  ANSWER: 25,164,150
**/

#include <iostream>  

int main()
{
  unsigned long long int sum = 0;

  for (int i = 1; i <= 100; ++i) {
    for (int j = i+1; j <= 100; ++j) {
      sum += i * j;
    }
  }

  std::cout << 2 * sum << std::endl;

  return 0;
} 
