/*
PROBLEM:
  The arithmetic sequence, 1487, 4817, 8147, in which each of the terms increases by 3330, is
  unusual in two ways: 

    (i)  each of the three terms are prime, and,
    (ii) each of the 4-digit numbers are permutations of one another.

  There are no arithmetic sequences made up of three 1-, 2-, or 3-digit primes, exhibiting this
  property, but there is one other 4-digit increasing sequence.

  What 12-digit number do you form by concatenating the three terms in this sequence?


SOLUTION:
  Here's the idea: I will break down the search for four-digit primes with this property into
  several steps:

   1. find all four-digit primes. The result will be ordered as we find them in order.
   2. group them by their digits using a `std::map`: keys are sorted vectors of digits and values
      are the primes composed of the digits in the map keys. Since 1 was sorted, this values in
      this map will be sorted.
   3. consider only groups with more than four four-digit primes.
   4. Check which ones satisfy the equidistance criterion. It's particularly easy for the cases 
      with four primes. For more than four,

  ANSWER: 2969-6299-9629
    1487, 4817, 8147
    1487  1847  4817  4871  7481  7841  8147  8741  
    2969, 6299, 9629
    2699  2969  6299  9629
**/


#include<iostream>
#include<vector>
#include<map>
#include<algorithm>



typedef unsigned int uint;


bool is_prime(uint n)
{
  if (n == 2) return true;
  else if (n % 2 == 0) return false;
  else if (n == 3) return true;
  else if (n % 3 == 0) return false;
  else if (n == 5) return true;
  else if (n % 5 == 0) return false;
  else if (n == 7) return true;
  else if (n == 11) return true;
  else if (n == 13) return true;
  else if (n == 17) return true;
  else if (n == 19) return true;

  uint k = 6;
  while (k * k <= n) {
    if (n % (k + 1) == 0) return false;
    if (n % (k + 5) == 0) return false;
    k += 6;
  }

  return true;
}


std::vector<uint> find_four_digit_primes()
{
  std::vector<uint> primes;

  for (uint n = 1002; n <= 9994; n += 6) { // 1002 = 6 * 167 
    if (is_prime(n + 1)) primes.push_back(n + 1);
    if (is_prime(n + 5)) primes.push_back(n + 5);
  }

  return primes;
}


std::map<std::vector<uint>, std::vector<uint> > group_by_digits(
  const std::vector<uint> &nums)
{
  std::map<std::vector<uint>, std::vector<uint> > groups;

  std::vector<uint>::const_iterator it;
  std::vector<uint> digits;
  uint temp;
  for (it = nums.begin(); it != nums.end(); it++) {
    digits.clear();
    temp = *it;
    while (temp > 0) {
      digits.push_back(temp % 10);
      temp /= 10;
    }
    std::sort(digits.begin(), digits.end());
    if (groups.find(digits) == groups.end()){
      groups[std::vector<uint>(digits)] = std::vector<uint>{*it};
    }
    else{
      groups[digits].push_back(*it);
    }
  }

  return groups;
}


bool contains_equidistance_subset_of_three(std::vector<uint> &vec, bool print=true)
{
  uint last_elem;
  for (uint i = 0; i < vec.size() - 2; i++) {  // the index of the first one:
    for (uint j = i+1; j < vec.size() - 1; j++) {
      last_elem = 2 * vec[j] - vec[i];
      if (std::find(vec.begin()+j, vec.end(), last_elem) != vec.end()) {
        if (print) 
          std::cout << vec[i] << ", " << vec[j] << ", " << last_elem << std::endl;
        return true;
      }
    }
  }
  return false;
}


int main()
{
  // Find four-digit primes:
  std::vector<uint> four_digit_primes = find_four_digit_primes();
  std::vector<uint>::iterator it;

  // Group them by digits:
  std::map<std::vector<uint>, std::vector<uint> > groups = group_by_digits(four_digit_primes);

  // Find the groups that satisfy the equidistance criteria:
  std::map<std::vector<uint>, std::vector<uint> >::iterator mit;
  for (mit = groups.begin(); mit != groups.end(); mit++) {
    if ((mit->second).size() < 3) {
      continue;
    }
    // Finds the suitable ones and prints them.
    if (contains_equidistance_subset_of_three(mit->second)) {
      for (it = (mit->second).begin(); it != (mit->second).end(); it++ )
        std::cout << *it << "\t";
      std::cout << std::endl;
    }
  }

  return 0;
}
