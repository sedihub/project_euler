/*
PROBLEM:
  Find the sum of the even-valued terms in the Fibonacci 
  sequence that starts from 1 and 2 (as opposed to 1 and 
  1, which is commonly the case) up to 4,000,000.


Solution:
  Fibonacci sequence:
    a_0 = 1 
    a_1 = 2
    a_{n+2} = a_{n+1} + a_{n}

  The first few elements of the sequence are:
    1, 2, 3, 5, 8, 13, 21, 34, 55, 89, ...

  We observ the following even-odd pattern:
    o, e, o, o, e,  o,  o,  e,  o,  o, ...

  Setting aside the first two terms in the sequence, the 
  sum of even-valued terms is the sum of odd-valued terms
  less than the largest positive even-values term. Thus:

    sum_even - 2 = sum_odd -1

  Let's see if we can simplify the problem by translating
  this into the sum of all terms in the sequence. The sum
  of all term in the sequence (up to and including a largest
  even-values term f_N) is:

    sum_fibo = sum_even + sum_odd = 2 * sum_even - 1

  Now, we only need to find the sum of all the terms in the
  Fibonacci sequence upto and including the largest even
  term smaller than N (4,000,000 in this problem).  

  ANSWER: 4613732
**/

#include <iostream>


int main()
{
  int upper_limit = 4000000;
  int n1 = 1;
  int n2 = 2;
  
  // Compute the sum terms in the Fibonacci sequence:
  int fibo_sum = 0;
  int temp = 0;
  while (n1 < upper_limit and n2 < upper_limit) {
    fibo_sum += (n1 + n2);

    temp = n1;
    n1 = n1 + n2;
    n2 = n1 + n2;
  }
  
  // Get the last two terms added:
  n1 = temp;
  n2 = (n2 - n1) / 2;
  if (n2 % 2 == 1 and n2 % 2 == 1) {
    fibo_sum -= (n1 + n2);
  }
  else if (n2 % 2 == 1 and n2 % 2 == 0) {
    fibo_sum -= n2;
  }

  // Print the result:
  std::cout << "\tThe sum of even-valued terms: "
            << (fibo_sum + 1) / 2 << std::endl;

  return 0;
}
