/*
PROBLEM:
  There are exactly ten ways of selecting three from five, 12345:

        123, 124, 125, 134, 135, 145, 234, 235, 245, and 345

  In combinatorics, we use the notation, choose(5, 3) = 10. In general, 

        choose(n, r) = n!/((n-r)! r!)

  It is not until n = 23, that a value exceeds one-million: 

        choose(23, r=10) = 1144066

  How many, not necessarily distinct, values of choose(n, r) for 1 <= n <= 100, are greater than 
  one-million?


SOLUTION:
  Let's do this!

  ANSWER: 4075
**/

#include "iostream"
#include "vector"
#include "iterator"


template<typename T> void print_vector(const std::vector<T> &vec, bool reverse=false)
{
  std::cout << "\t";
  if (reverse) {
    typename std::vector<T>::const_reverse_iterator rit;
    for (rit = vec.rbegin(); rit != vec.rend(); rit++){
      std::cout << *rit << " ";
    }
  }
  else {
    typename std::vector<T>::const_iterator it;
    for (it = vec.begin(); it != vec.end(); it++) {
      std::cout << *it << " ";
    }
  }
  std::cout << std::endl;
}


void remove_common_factors(unsigned int &a, unsigned int &b)
{
  if (a == 1 || b == 1) return;

  if (a == b) {
    a = 1;
    b = 1;
    return;
  }
  else if (a < b) {
    if (b % a == 0) {
      b /= a;
      a = 1;
      return;
    }
  }

  if(a % b == 0) {
    a /= b;
    b = 1;
    return;
  }

  for (unsigned int n = 2; n < std::min(a,b); n++) {
    if (a % n == 0 && b % n == 0) {
      a /= n;
      b /= n;
    }
  }
}


unsigned long int choose(unsigned int n, unsigned int r)
{
  if (n - r > r) r = n - r;

  std::vector<unsigned int> numerator;
  std::vector<unsigned int> denominator;
  for (unsigned int i = n; i > r; i--) {
    numerator.push_back(i);
  }
  for (unsigned int i = n-r; i > 1; i--) {
    denominator.push_back(i);
  }

  std::vector<unsigned int>::iterator n_it;
  std::vector<unsigned int>::iterator d_it;
  for (n_it = numerator.begin(); n_it != numerator.end(); n_it++) {
    for (d_it = denominator.begin(); d_it != denominator.end(); d_it++) {
      remove_common_factors(*n_it, *d_it);
    }
  }


  unsigned long int result = 1;
  std::vector<unsigned int>::iterator it;
  for (it = numerator.begin(); it != numerator.end(); it++) {
    if (*it == 1) continue;
    result *= (unsigned long int)(*it);
  }

  return result;
}



int main()
{
  unsigned int count = 0;
  for (unsigned int n = 2; n <= 100; n++) {
    for (unsigned int r = 2; r < n; r++) {
      if (choose(n,r) > 1000000) count++; 
    }
  }

  std::cout << count << std::endl;

  return 0;
}
