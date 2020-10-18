/*
PROBLEM:
  Starting with 1 and spiralling anticlockwise in the following way, a square spiral with side
  length 7 is formed.

              37 36 35 34 33 32 31
              38 17 16 15 14 13 30
              39 18  5  4  3 12 29
              40 19  6  1  2 11 28
              41 20  7  8  9 10 27
              42 21 22 23 24 25 26
              43 44 45 46 47 48 49

  It is interesting to note that the odd squares lie along the bottom right diagonal, but what
  is more interesting is that 8 out of the 13 numbers lying along both diagonals are prime; that
  is, a ratio of 8/13 ≈ 62%.

  If one complete new layer is wrapped around the spiral above, a square spiral with side length
  9 will be formed. If this process is continued, what is the side length of the square spiral for
  which the ratio of primes along both diagonals first falls below 10%?


SOLUTION:
  This is actually quite straightforward: We only need to consider the four corners of the grid
  after adding a new layer each time. Note that the bottom right corner is always a square. We
  only need to consider the other three corners. They are give by:

        upper right: m ^ 2 - 3*(m - 1)
        upper left: m ^ 2 - 2*(m - 1) 
        lower left: m ^ 2 - (m - 1)
        lower right: m ^ 2

  where m = 2n + 1 and n is the level starting from zero. 

  ANSWER: Level 26241 the ration is 0.0999981
**/

#include <iostream>


bool is_prime(unsigned long int n)
{
  if (n == 2) return true;
  else if (n == 3) return true;
  else if (n == 5) return true;
  else if (n % 2 == 0) return false;
  else if (n % 3 == 0) return false;
  else if (n % 5 == 0) return false;

  unsigned long int k = 6;
  while (k * k <= n) {
    if (n % (k + 1) == 0) return false;
    if (n % (k + 5) == 0) return false;
    k += 6;
  }

  return true;
}


int main()
{
  unsigned int m;
  double  prime_count, total_count;

  m = 3;   
  prime_count = 3.0;
  total_count = 5;
  unsigned long int lowe_right, lower_left, upper_left, upper_right;
  while (prime_count / total_count >= 0.1) {
    m += 2;
    total_count += 4;
    //
    lowe_right = m * m;
    lower_left = lowe_right - (m - 1);
    upper_left = lower_left - (m - 1);
    upper_right = upper_left - (m - 1);
    // std::cout << "\t" << upper_right << ", " << upper_left << ", "
    //           << lower_left << ", " << lowe_right << std::endl;
    //
    if (is_prime(lower_left)) prime_count++;
    if (is_prime(upper_left)) prime_count++;
    if (is_prime(upper_right)) prime_count++;
    //
    // std::cout << "\t[" << m << "]: " << prime_count / total_count 
    //           << std::endl << std::endl;
  } 

  std::cout << "Level " << m << ": " << prime_count / total_count << std::endl;

  return 0;
}
