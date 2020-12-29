/*
PROBLEM:
  Euler 74
  The number 145 is well known for the property that the sum of the factorial 
  of its digits is equal to 145:

      1! + 4! + 5! = 1 + 24 + 120 = 145

  Perhaps less well known is 169, in that it produces the longest chain of 
  numbers that link back to 169; it turns out that there are only three such 
  loops that exist:

      169 → 363601 → 1454 → 169
      871 → 45361 → 871
      872 → 45362 → 872

  It is not difficult to prove that EVERY starting number will eventually get 
  stuck in a loop. For example,

      69 → 363600 → 1454 → 169 → 363601 (→ 1454)
      78 → 45360 → 871 → 45361 (→ 871)
      540 → 145 (→ 145)

  Starting with 69 produces a chain of five non-repeating terms, but the longest 
  non-repeating chain with a starting number below one million is sixty terms.

  How many chains, with a starting number below one million, contain exactly 
  sixty non-repeating terms?


SOLUTION:
  The brute-force solution takes a while.

  I increased the efficiency in a second solution by generating sorted 
  permutations. At the end we need to sum up the permutations of course.
  I did that manually as there were only three solution. Coding that part
  is of course straightforward.

  Note that it is likely possible to devise an even more efficent slution 
  by improving searching the cycles.

  ANSWER: 402

      9740 --> 3 * 3 * 2   (because zero cannot be the leading digit)
      9741 -->      + 4!
    974322 -->  + 6! / 2   (there are two 2's, hence double counting)
 **/

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <iterator>


typedef unsigned long int ULInt;
typedef std::vector<ULInt> ULIntVec;
typedef std::map<ULInt, ULInt> ULIntMap;


ULInt factorial(ULInt n)
{
  if (n <= 1) {
    return 1;
  }
  else {
    return n * factorial(n - 1);
  }
}


ULInt sum_digit_factorials(ULInt n, const ULIntMap &digit_factorials)
{
  ULInt sum = 0;
  while (n > 0) {
    sum += digit_factorials.at(n % 10);
    n /= 10;
  }
  return sum;
}


std::vector<ULIntVec> ordered_permutations(
  std::vector<ULIntVec> previous, 
  ULInt &length)
{
  if (previous.back().size() == length) {
    return previous;
  }
  //
  std::vector<ULIntVec> next;
  std::vector<ULIntVec>::iterator it;
  ULInt max_digit = 9 + 1 - length + previous.back().size();
  for (it = previous.begin(); it != previous.end(); it++) {
    for (ULInt n = it->back(); n <= max_digit; n++) {
      next.push_back(ULIntVec(*it));
      next.back().push_back(n);
    }
  }
  return ordered_permutations(next, length);
}


ULInt num_digits(ULInt n) {
  ULInt count = 0;
  while (n != 0) {
    count += 1;
    n /= 10;
  }
  return count;
}


ULInt vec_to_int(ULIntVec &vec) {
  ULInt n = 0;
  for (ULIntVec::reverse_iterator rit = vec.rbegin(); rit != vec.rend(); rit++) {
    n *= 10;
    n += *rit;
  }
  return n;
}


int main()
{
  const ULInt UPPER_LIMIT = 1000000;
  ULIntMap digit_factorials;

  for (ULInt n = 0; n <= 9; n++) {
    digit_factorials[n] = factorial(n);
  }

  // // Brute-force solution -- very slow (~23 sec.)
  // ULInt count = 0;
  // bool show_cycles = !false;
  // ULIntVec visited;
  // ULIntVec::iterator it;
  // ULInt temp, length;
  // for (ULInt n = 1; n < UPPER_LIMIT; n++) {
  //   length = 1;
  //   visited = ULIntVec({n});
  //   temp = sum_digit_factorials(n, digit_factorials);
  //   it = std::find(std::begin(visited), std::end(visited), temp);
  //   if (show_cycles) std::cout << "\t" << n << " ";
  //   while (it == std::end(visited)) {
  //     if (show_cycles) std::cout << temp << " ";
  //     visited.push_back(temp);
  //     temp = sum_digit_factorials(temp, digit_factorials);
  //     it = std::find(std::begin(visited), std::end(visited), temp);
  //   }
  //   if (show_cycles) std::cout << std::endl;
  //   length = (ULInt)visited.size();
  //   if (length == 60) {
  //     std::cout << "\t" << n << " --> " << length << std::endl;
  //     count += 1;
  //   }
  // }
  // std::cout << "Count = " << count << std::endl;


  // More efficient solution:
  std::vector<ULIntVec> candidates;
  for (ULInt length = 1; length <= num_digits(UPPER_LIMIT - 1); length++) {
    std::vector<ULIntVec> current_candidates;
    for (ULInt n = 0; n <= 9 - length + 1; n++) {
      current_candidates.push_back(ULIntVec({n}));
    }
    current_candidates = ordered_permutations(current_candidates, length);
    candidates.reserve(candidates.size() + current_candidates.size());
    candidates.insert(
      candidates.end(), 
      current_candidates.begin() + 1, // The first candidate is always 00...0 
      current_candidates.end());
  }
  //
  std::vector<ULIntVec>::iterator it;
  if (! true) {
    for (it = candidates.begin(); it != candidates.end(); it++) {
      std::cout << "\t[" << std::distance(candidates.begin(), it) << "]\t";
      for (ULInt n = 0; n < it->size(); n++) {
        std::cout << (*it)[n];
      }
      std::cout << " ---> " << vec_to_int(*it) << std::endl;
    }
  }
  std::cout << "Number of candidates: " << candidates.size() << std::endl;
  //
  // Next, we use the candidates:
  ULInt count = 0;
  ULIntVec visited;
  ULIntVec::iterator visited_it;
  ULInt temp, length;
  for (it = candidates.begin(); it != candidates.end(); it++) {
    ULInt n = vec_to_int(*it);
    length = 1;
    visited = ULIntVec({n});
    temp = sum_digit_factorials(n, digit_factorials);
    visited_it = std::find(std::begin(visited), std::end(visited), temp);
    while (visited_it == std::end(visited)) {
      visited.push_back(temp);
      temp = sum_digit_factorials(temp, digit_factorials);
      visited_it = std::find(std::begin(visited), std::end(visited), temp);
    }
    length = (ULInt)visited.size();
    if (length == 60) {
      std::cout << "\t" << n << " --> " << length << std::endl;
      count += 1;
    }
  }
  std::cout << "Count = " << count << std::endl;

	return 0;
}
