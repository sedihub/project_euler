/*
PROBLEM:
  Starting in the top left corner of a 2×2 grid, and only being able to move to the right
  and down, there are exactly 6 routes to the bottom right corner.
  
  How many such routes are there through a 20×20 grid?


SOLUTION:
  This is a simple combinatorial problem: We have to take n steps to the right and n steps 
  down on an n-by-n grid. Thus, the number of wats is 2n choose n. For n = 2, 4 choose 2
  which is 6.

  The tricky part is computing the factorial, which we don't have to!

  ANSWER:  137846528820
**/

#include <iostream>
#include <vector>


void simplify(unsigned int &n, unsigned int &m)
{
  if (n == 1 || m == 1)
    return;
  //
  if (n % m == 0) {
    n /= m;
    m = 1;
  }
  else if  (m % n == 0) {
    m /= n;
    n = 1;
  }
  else if (n > m) {
    for (unsigned int i = 2 ; i < m; ++i) {
      while (m % i == 0 and n % i == 0) {
        m /= i;
        n /= i;
        if(m == 1) return;
      }
    }
  }
  else if (m > n) {
    for (unsigned int i = 2 ; i < n; ++i) {
      while (n % i == 0 and m % i == 0) {
        n /= i;
        m /= i;
        if(n == 1) return;
      }
    }
  }
  
  return;
}


int main()
{
  const unsigned int n = 20;

  // Compute m choose k = m!/(k!(m-k)!)
  std::vector<unsigned int> numerator;
  for (unsigned int i = 2*n; i > n; --i)
    numerator.push_back(i);

  std::vector<unsigned int> denominator;
  for (unsigned int i = 1; i <= n; ++i)
    denominator.push_back(i);

  std::vector<unsigned int>::iterator it;
  std::vector<unsigned int>::iterator it2;
  for (it = denominator.begin(); it != denominator.end(); ++it) {
    for (it2 = numerator.begin(); it2 != numerator.end(); ++it2) {
      std::cout << *it << ", " << *it2 << " ---> ";
      simplify(*it, *it2);
      std::cout << *it << ", " << *it2 << std::endl;
    }
  }

  unsigned long long int numerator_prod = 1;
  for (it = numerator.begin(); it != numerator.end(); ++it)
    numerator_prod *= (unsigned long long int)*it;

  unsigned long long int denominator_prod = 1;
  for (it = denominator.begin(); it != denominator.end(); ++it)
    denominator_prod *= (unsigned long long int)*it;

  std::cout << 2*n << " choose " << n << ": " << std::endl;
  std::cout << numerator_prod << " / " << denominator_prod << " = "
            << numerator_prod/denominator_prod << std::endl;

  return 0;
}
