/*
PROBLEM:
  The decimal number, 585 = 1001001001 (binary), is palindromic in both bases.
  
  Find the sum of all numbers, less than one million, which are palindromic in base 10 and base 2.

  (Please note that the palindromic number, in either base, may not include leading zeros.)


SOLUTION:
  We obvious solution is to use brute force search. This takes some time. A better solution is
  to compile decimal palindromes to shrink the search space and then check if they are also
  palindromic in the binary representation. This way, the solution is dramatically faster.

  ANSWER: 872187
      1  00000000000000000000000000000001
      3  00000000000000000000000000000011
      5  00000000000000000000000000000101
      7  00000000000000000000000000000111
      9  00000000000000000000000000001001
      33  00000000000000000000000000100001
      99  00000000000000000000000001100011
      313  00000000000000000000000100111001
      585  00000000000000000000001001001001
      717  00000000000000000000001011001101
      7447  00000000000000000001110100010111
      9009  00000000000000000010001100110001
      15351  00000000000000000011101111110111
      32223  00000000000000000111110111011111
      39993  00000000000000001001110000111001
      53235  00000000000000001100111111110011
      53835  00000000000000001101001001001011
      73737  00000000000000010010000000001001
      585585  00000000000010001110111101110001
**/

#include <iostream>
#include <vector>
#include <iterator>
#include <bitset>
#include <iomanip> 


namespace solution1 {
  template <typename T>
  bool is_palindrome(const std::vector<T> &vec)
  {
    typename std::vector<T>::const_iterator it = vec.begin();
    typename std::vector<T>::const_reverse_iterator rit = vec.rbegin();
    while (&(*it) != &(*rit)) {
      if (*it != *rit) {
        return false;
      }
      it++;
      if (&(*it) == &(*rit)) {  // The case the the size of the vec is even. 
        break; 
      }
      rit++;
    }
    return true;
  }


  bool is_decimal_palindrome(unsigned int n)
  {
    std::vector<char> digits;
    while (n > 0) {
      digits.push_back((char)(n % 10) + '0');
      n /= 10;
    }
    return is_palindrome<char>(digits);
  }
}


namespace solution2 {
  unsigned int pow(unsigned int n, unsigned int p)
  {
    if (p == 0) return 1;
    else if (p == 1) return n;
    else 
      return n * pow(n, p - 1);
  }


  std::vector<unsigned int> generate_n_digit_palindromes(unsigned int n_digit)
  {
    std::vector<unsigned int> candidates;

    // First, the single digit case: 
    unsigned int candidate;
    if(n_digit == 1) {
      for (candidate = 1; candidate < 10; candidate++)
        candidates.push_back(candidate);
      return candidates;
    }

    // If n_digit > 1, then we construct them:
    unsigned int temp;
    unsigned int half_num_digits = n_digit / 2;
    unsigned int smallest_m_digit_int = pow(10, half_num_digits - 1);
    unsigned int largest_m_digit_int = pow(10, half_num_digits) - 1;
    if (n_digit % 2 == 0) {
      for (unsigned int n = smallest_m_digit_int; n <= largest_m_digit_int; n++) {
        candidate = 0;
        temp = n;
        while (temp > 0) {
          candidate = (temp % 10) + 10 * candidate;
          temp /= 10;
        }
        candidate += n * pow(10, half_num_digits);
        candidates.push_back(candidate);
        // std::cout << candidate << std::endl;
      }
    }
    else {
      for (unsigned int n = smallest_m_digit_int; n <= largest_m_digit_int; n++) {
        candidate = 0;
        temp = n;
        while (temp > 0) {
          candidate = (temp % 10) + 10 * candidate;
          temp /= 10;
        }
        candidate += n * pow(10, half_num_digits + 1);
        temp = candidate;
        for (unsigned int mid_dig = 0; mid_dig < 10; mid_dig++) {
          candidate = temp + mid_dig * pow(10, half_num_digits);
          candidates.push_back(candidate);
          // std::cout << candidate << std::endl;
        }
      }
    }

    return candidates;
  }
}


bool is_binary_palindrome(const unsigned int &n)
{
  std::bitset<32> n_bits(n);

  // idecies to traverse the set of bits:
  unsigned int s_idx = 0;
  unsigned int e_idx = 31;
  while (n_bits[e_idx] == 0)
    e_idx--;

  while (s_idx != e_idx && (s_idx - 1) != e_idx) {
    if (n_bits[s_idx] != n_bits[e_idx])
      return false;
    s_idx++;
    e_idx--;
  }
  return true;
}


int main()
{
  const unsigned int upper_limit = 1000000;
  unsigned int sum;

  // // Solution 1: Brute-force solution:
  // sum = 0;
  // for (unsigned int n = 1; n < upper_limit; n++){
  //   if (solution1::is_decimal_palindrome(n)) {
  //     if (is_binary_palindrome(n)) {
  //       std::cout << "\t" << n << "  " << std::bitset<32>(n) << std::endl;
  //       sum += n;
  //     }
  //   }
  // }

  // Solution 2:
  sum = 0;
  std::vector<unsigned int> candidates;
  std::vector<unsigned int>::iterator it;
  for (unsigned int candidate_num_digits = 1; candidate_num_digits < 7; candidate_num_digits++) {
    candidates = solution2::generate_n_digit_palindromes(candidate_num_digits);
    for (it = candidates.begin(); it != candidates.end(); it++) {
      if (is_binary_palindrome(*it)) {
        std::cout << "\t" << *it << "  " << std::bitset<32>(*it) << std::endl;
        sum += *it;
      }
    }
  }

  std::cout << "Sum of decimal and binary palindromic numbers below" 
        << upper_limit << " is: " << sum << std::endl;

  return 0;
}
