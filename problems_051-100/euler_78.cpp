/*
PROBLEM:
  Euler 78
  Let p(n) represent the number of different ways in which n coins can be separated 
  into piles. For example, five coins can be separated into piles in exactly seven 
  different ways, so p(5)=7.

  Find the least value of n for which p(n) is divisible by one million.

SOLUTION:
  This is similar to problem 076. The difference is that we should be able to increase
  the solution set. In this regard, it is similar to problem 077. One main difference is
  that a pile of exactly n-numbers is acceptable. For this we include the number itself
  as one of the values to be used in finding the number of solutions. i.e., including 
  the upper limit in the outer loop of the external loops that compile the solutions.

  In the process of solving this problem, I realized that I need to deal with large 
  numbers. One way to get around this is to utilize the fact that we are looking for
  the first candidate with 6 zeros. For this reason and the fact that we are only using
  + operator, which commuted with the % operator, we can take the modulus of the output. 

  ANSWER: 55374 (took a long time -- ~29s...)
 **/

#include <iostream>


typedef unsigned long int ULInt;


int main()
{
  const ULInt upper_limit = 100000;

  // Create and zero initialize an array:
  ULInt* solutions = new ULInt[upper_limit + 1];
  for (ULInt idx = 0; idx < (upper_limit + 1); idx++) {
    solutions[idx] = 0;
  }
  solutions[0] = 1;  

  // Find solutions:
  for (ULInt vals = 1; vals <= upper_limit; vals++) {
    for (ULInt num = vals; num <= upper_limit; num++) {  
      solutions[num] += solutions[num - vals];
      solutions[num] = solutions[num] % 10000000;
    }
    if (solutions[vals] % 1000000 == 0) {
      std::cout << "\tAnswer: " << vals << std::endl; 
      break;
    }
  }
 
  delete[] solutions;
  return 0;
}
