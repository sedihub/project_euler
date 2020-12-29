/*
PROBLEM:
  Euler 77
  What is the first value which can be written as the sum of primes in over five 
  thousand different ways?

SOLUTION:
  We use the same approach as in the previous problem. The only difference is that
  this time we need to continue finding primes until one is found.

  A tricky aspect of this problem is that no all combinations result in a solution.

  First, let's develop a prime finder utility that allows for finding more primes.

  Actually, since finding the solution is so fast, I worked around this by using a
  rough guess for the needed numbed of primes.

  ANSWER: 71, which can be written in 5007 ways.
 **/

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>


typedef unsigned long int ULInt;
typedef std::vector<ULInt> ULIntVec;


void print_ulintvec(const ULIntVec &vec) 
{
  ULIntVec::const_iterator it;
  for (it = vec.begin(); it != vec.end(); it++) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
}


void find_primes(ULInt num_primes, ULIntVec &primes)
{
  if (primes.size() < 3) {
    primes.push_back(2);
    primes.push_back(3);
    primes.push_back(5);
  }

  ULIntVec::iterator it;
  ULInt n = 6 * (primes.back() / 6);
  while (primes.size() < num_primes) {
    n += 6; // Since in the previous round we have explored (6k + 5).
    //
    it = primes.begin();
    while (it != primes.end() && (*it) * (*it) <= (n + 1)) {
      if ((n + 1) % (*it) == 0) {
        goto CONT1;
      }
      it++;
    }
    primes.push_back(n + 1);
    CONT1:;
    //
    it = primes.begin();
    while (it != primes.end() && (*it) * (*it) <= (n + 5)) {
      if ((n + 5) % (*it) == 0) {
        goto CONT2;
      }
      it++;
    }
    primes.push_back(n + 5);
    CONT2:;
  }

  return;
}


int main()
{
  const ULInt MIN_NUM_WAYS = 5001;

  ULIntVec primes;
  find_primes(50, primes);

  // Initialize the solution vector:
  ULIntVec solutions;
  for (ULInt idx = 0; idx <= 2 * primes.back(); idx++) {
    solutions.push_back(0);
  }
  solutions[0] = 1;

  // Compile solutions: 
  ULInt max_num_solutions = 1;
  ULInt number_with_max_sums = 0;
  ULInt initial_primes_idx = 0;
  for (ULInt p_idx = initial_primes_idx; p_idx < primes.size(); p_idx++) {
    for (ULInt n = primes[p_idx]; n < solutions.size(); n++) {
      solutions[n] += solutions[n - primes[p_idx]];
    }
  } 
  //
  for (ULInt num = 1; num < solutions.size(); num++) {
    if (solutions[num] > max_num_solutions) {
      max_num_solutions = solutions[num];
      number_with_max_sums = num;
    }
  }
  // // Check 10 as sanity check:
  // std::cout << "\t10 can be written in " << solutions[10] << " ways." << std::endl;

  // Find and print the answer:
  ULInt solution_number, solution_num_sums; 
  for (ULInt num = 1; num < solutions.size(); num++) {
    if (solutions[num] > MIN_NUM_WAYS) {
      solution_num_sums = solutions[num];
      solution_number = num;
      break;
    }
  } 
  std::cout << "\tAnswer: " << solution_number 
            << ", which can be written in " << solution_num_sums
            << " ways." << std::endl;

  return 0;
}
