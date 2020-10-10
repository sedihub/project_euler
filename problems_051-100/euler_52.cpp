/*
PROBLEM:
  It can be seen that the number, 125874, and its double, 251748, contain exactly the same digits,
  but in a different order.

  Find the smallest positive integer, x, such that 2x, 3x, 4x, 5x, and 6x, contain the same digits.


SOLUTION:

  ANSWER: 142857
**/

#include "iostream"
#include "vector"
#include "iterator"
#include "algorithm"
#include "set"


bool is_prime(unsigned long int n)
{
  if (n == 2 ) return true;
  else if (n == 3) return true;
  else if (n == 5) return true;
  else if (n % 2  == 0) return false;
  else if (n % 3  == 0) return false;
  else {
    unsigned long int k = 6;
    while (k * k <= n) {
      if (n % (k + 1) == 0) return false;
      if (n % (k + 5) == 0) return false;
      k += 6;
    }
    return true;
  }
}


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


void ulint_to_char_vec(unsigned long int n, std::vector<char> &vec)
{
  vec.clear();
  while (n > 0) {
    vec.push_back(n % 10 + '0');
    n /= 10;
  }
  std::reverse(vec.begin(),vec.end());
}


unsigned long int char_vec_to_ulint(const std::vector<char> &vec)
{
  unsigned long int n = 0;
  unsigned long int p = 1;
  std::vector<char>::const_reverse_iterator rit;
  for (rit = vec.rbegin(); rit != vec.rend(); rit++){
    n += p*(*rit-'0');
    p *= 10;
  }

  return n;
}


void ulint_to_sorted_char_vec(unsigned long int n, std::vector<char> &vec)
{
  ulint_to_char_vec(n , vec);
  std::sort(vec.begin(), vec.end());
}


int main()
{
  unsigned long int n = 1000;
  std::vector<char> vec1;
  std::vector<char> vec2;
  while (true) {
    ulint_to_sorted_char_vec(n, vec1);
    ulint_to_sorted_char_vec(2 * n, vec2);
    if (vec1 == vec2) {
      ulint_to_sorted_char_vec(3 * n, vec2);
      if (vec1 == vec2) {
        ulint_to_sorted_char_vec(4 * n, vec2);
        if (vec1 == vec2) {
          ulint_to_sorted_char_vec(5 * n, vec2);
          if (vec1 == vec2) {
            ulint_to_sorted_char_vec(6 * n, vec2);
            if (vec1 == vec2) {
              std::cout << n << std::endl;
              break;
            }
          }
        }
      }
    }
    n++;
  }

  return 0;
}
