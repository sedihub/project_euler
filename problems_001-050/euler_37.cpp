/*
PROBLEM:
  The number 3797 has an interesting property. Being prime itself, it is possible to continuously
  remove digits from left to right, and remain prime at each stage: 3797, 797, 97, and 7. 
  Similarly we can work from right to left: 3797, 379, 37, and 3.

  Find the sum of the only eleven primes that are both truncatable from left to right and right
  to left.

  NOTE: 2, 3, 5, and 7 are not considered to be truncatable primes.


SOLUTION:
  We need to shrink the search space as much as possible. Being left-right and right-left prime
  truncatable are very stringent criteria that will allow us to significantly reduce the size
  of the search space.

  Since the number is prime-truncatable from both left to right and right to left, it must be
  only consisted of 1, 3, 7 and 9 digits. Further, it cannot have more than two 1 and 7 in its 
  digits or else it will be divisible by 3. To see this, say it has 4 sevens. As we truncate 
  we are bound to get to a truncation with only three sevens and the reset of the digits being
  3s and 9s. The sum of the digits will be divisible by 3. Specifically, allowed sequences can
  only have the following start and ends:

      3 1 ... 7 3
      3 7 ... 7 3
      3 1 ... 1 3
      3 7 ... 1 3
        7 ... 7 3
        7 ... 1 3
      3 1 ... 7
      3 7 ... 7
        7 3
        3 7
        3 1 7
        3 1 3
 
  Note that 1 and 7 cannot be any closer or else a subsequence will be divisible by 3. We can 
  use recursion to find out all valid combinations of 9 and 3 in the place of ellipsis above.
  Note that we are not using the expected number of solutions!

  Finally, note that there are two exception that need to be included: 23 and 53!


  ANSWER: 748317
      23, 37, 53, 73, 313, 317, 373, 797, 3137, 3797, 739397
**/

#include <iostream>
#include <vector>
#include <set>
#include <iterator>


typedef unsigned long long int ullint;


template <typename T>
bool is_prime(T n)
{
  if (n == 0) return false;
  else if (n == 1) return false;
  else if (n == 2) return true;
  else if (n == 3) return true;
  else if (n == 5) return true;
  else if (n % 2 == 0) return false;
  else if (n % 3 == 0) return false;
  else if (n % 5 == 0) return false;

  T k = 6;
  while (k * k <= n) {
    if (n % (k + 1) == 0) return false;
    if (n % (k + 5) == 0) return false;
    k += 6;
  }
  return true;
}


ullint char_to_int(char c)
{
  return (ullint)(c - '0');
}


bool is_bidirectional_truncatable_prime(const std::vector<char> &num_digits)
{
  // Check right-truncated in the reverse order
  ullint right_truncated = 0;
  std::vector<char>::const_iterator it = num_digits.begin();
  while (it != num_digits.end()) {
    right_truncated = 10 * right_truncated;
    right_truncated += char_to_int(*it);
    if (!is_prime<ullint>(right_truncated)) {
        // std::cout << "[RT] "  << right_truncated << " is not prime!" << std::endl;
        return false;
    }
    it++;
  }
  
  // Check left-truncated in the reverse order
  ullint left_truncated = 0;
  ullint decimal = 1;
  std::vector<char>::const_reverse_iterator rit = num_digits.rbegin();
  while (rit != num_digits.rend()) {
    left_truncated += decimal * char_to_int(*rit);
    decimal *= 10;
    if (!is_prime<ullint>(left_truncated)) {
      // std::cout << "[LT] " << left_truncated << " is not prime!" << std::endl;
      return false;
    }
    rit++;
  }

  return true;
}


ullint digits_vecor_to_ullint(const std::vector<char> &num_digits)
{
  ullint n = 0;
  std::vector<char>::const_iterator it = num_digits.begin();
  while (it != num_digits.end()) {
    n *= 10;
    n += char_to_int(*it);
    it++;
  }
  return n;
}


bool is_prime(const std::vector<char> &num_digits)
{
  ullint n = digits_vecor_to_ullint(num_digits);
  return is_prime(n);
}


std::vector<ullint> dicsover_truncatable_primes(
  std::vector<char> &head, 
  std::vector<char> &tail,
  bool verbose=false)
/* Given a head and tail subsequences, explores their combination as well as
   their combination with 3 and 9 insertions.
**/
{
  std::vector<ullint> candidates;
  std::vector<char> candidate;

  // Splice head and tail. Retain if it is a bidirectional truncatable prime:
  candidate = head;
  candidate.insert(candidate.end(), tail.begin(), tail.end());
  if (verbose) {  
    std::vector<char>::iterator it;
    for (it = head.begin(); it != head.end(); it++) {
      std::cout << *it;
    }
    std::cout << " + ";
    for (it = tail.begin(); it != tail.end(); it++) {
      std::cout << *it;
    }
    std::cout << " = ";
    for (it = candidate.begin(); it != candidate.end(); it++) {
      std::cout << *it;
    }
    std::cout << "\t" << is_bidirectional_truncatable_prime(candidate) << std::endl;
  }
  if (is_bidirectional_truncatable_prime(candidate)) {
    candidates.push_back(digits_vecor_to_ullint(candidate));
  }

  // Recursively check the remaining possibilities:
  std::vector<ullint> new_candidates;
  // 
  // Examine adding 3:
  candidate = head;
  candidate.push_back('3');
  if (is_prime(candidate)) {
    new_candidates = dicsover_truncatable_primes(candidate, tail, verbose);
    candidates.insert(candidates.end(), new_candidates.begin(), new_candidates.end());
  }
  // 
  // Examine adding 9:
  candidate = head;
  candidate.push_back('9');
  if (is_prime(candidate)) {
    new_candidates = dicsover_truncatable_primes(candidate, tail, verbose);
    candidates.insert(candidates.end(), new_candidates.begin(), new_candidates.end());
  }

  return candidates;
}


int main()
{
  std::set<ullint> truncatable_primes = {23, 53};

  std::vector< std::vector<char> > heads = {
    {'3', '1'}, {'3', '7'}, {'7'}, {'3'}};
  std::vector< std::vector<char> > tails = {
    {'7', '3'}, {'1', '3'}, {'7'}, {'3'}};

  std::vector<ullint> discovered;
  std::vector< std::vector<char> >::iterator head_it;
  std::vector< std::vector<char> >::iterator tail_it;
  for (head_it = heads.begin(); head_it != heads.end(); head_it++) {
    for (tail_it = tails.begin(); tail_it != tails.end(); tail_it++) {
      discovered = dicsover_truncatable_primes(*head_it, *tail_it, false);
      truncatable_primes.insert(discovered.begin(), discovered.end());
    }
  }

  ullint sum = 0;
  std::set<ullint>::iterator it;
  for (it = truncatable_primes.begin(); it != truncatable_primes.end(); it++) {
    std::cout << "\t" << *it << std::endl;
    sum += *it;
  }
  std::cout << "Sum of left-right and right-left truncatable primes is: "
      << sum << std::endl;

  return 0;
}
