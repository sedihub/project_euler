/*
PROBLEM:
  Euler 76
  How many different ways can one hundred be written as a sum of at least two 
  positive integers?

  Solution:
  Generating the sums using either recursion or a `while` loop was inefficient.

  "Solution 2" is based on the idea of stratifying the solutions into number of
  terms. There are a total of (n - 1) terms at most. Here is an example for 7
  to demonstrate the idea:

        2 terms --> ceil(7/2) to (7-1)
          6 + 1
          5 + 2
          4 + 3

        3 terms --> ceil(7/3) to (7-2)
          5 + 1 + 1
          4 + 2 + 1
          3 + 3 + 1
          3 + 2 + 2   <---  Simple counting won't suffice...

        4 terms --> ceil(7/4) to (7-3)
          4 + 1 + 1 + 1 
          3 + 2 + 1 + 1
          2 + 2 + 2 + 1

        5 terms --> ceil(7/5) to (7-4)
          3 + 1 + 1 + 1 + 1
          2 + 2 + 1 + 1 + 1

        6 terms --> ceil(7/6) to (7-5)
          2 + 1 + 1 + 1 + 1 + 1

        7 terms --> ceil(7/7) to (7-6)
          1 + 1 + 1 + 1 + 1 + 1 + 1 
        ---------------------------
        Number of sums: 14

  This solution is still slow. The bottleneck of this is `num_sums`. This can be 
  sped up by storing these values.

  I came across a solution that does this in a very efficient way. Here it is:
  (source: https://www.mathblog.dk/project-euler-76-one-hundred-sum-integers/)

  Solution 3:
  The idea is to start with the smallest available number: construct solutions using
  m = 1 for all the values between 1 and n. Then we use these to construct solutions 
  for sums that use 1 and 2. In fact, n here is the number of times that he value m is 
  used. For example, for the target sum of 5:

        4 + 1
        3 + 2
        3 + 1 + 1
        2 + 2 + 1
        2 + 1 + 1 + 1
        1 + 1 + 1 + 1 + 1 

  We can use 2 at most twice and 3 and 4 at most once.

  ANSWER: 190569291
 **/

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>


typedef unsigned long int ULInt;
typedef std::vector<ULInt> ULIntVec;

namespace Solution_1a {
  void print_ulintvec(const ULIntVec &vec) 
  {
    ULIntVec::const_iterator it;
    for (it = vec.begin(); it != vec.end(); it++) {
      std::cout << *it << " ";
    }
    std::cout << std::endl;
  }


  std::vector<ULIntVec> sums(const std::vector<ULIntVec> &previous, const ULInt &target_sum) 
  {
    if (previous.size() == 0) {
      return std::vector<ULIntVec>();
    }

    std::vector<ULIntVec> next;
    std::vector<ULIntVec> complete;
    std::vector<ULIntVec>::const_iterator it;
    ULInt sum;
    for (it = previous.begin(); it != previous.end(); it++) {
      for (ULInt n = 1; n <= it->back(); n++) {
        sum = n + (*it)[0];
        if (sum > target_sum) {
          break;
        }
        else if (sum == target_sum) {
          complete.push_back(ULIntVec(*it));
          complete.back().push_back(n);
          complete.back()[0] = sum;
        }
        else {
          next.push_back(ULIntVec(*it));
          next.back().push_back(n);
          next.back()[0] = sum;
        }
      }
    }
    std::vector<ULIntVec> remaining = sums(next, target_sum);
    complete.reserve(complete.size() + remaining.size());
    complete.insert(complete.end(), remaining.begin(), remaining.end());
    return complete;
  }


  ULInt number_of_solutions(const ULInt target_sum) 
  {
    std::vector<ULIntVec> seeds;
    for (ULInt n = 1; n < target_sum; n++) {
      seeds.push_back(ULIntVec({n, n}));
    }
    std::vector<ULIntVec> sum_combinations = sums(seeds, target_sum);

    // // Print the possible sums:
    // std::vector<ULIntVec>::iterator it;
    // for (it = sum_combinations.begin(); it != sum_combinations.end(); it++) {
    //   print_ulintvec(*it);
    // }

    return sum_combinations.size();
  }
};


namespace Solution_1b {
  // Same as solution 1 but with `while` loop instead of recursion.
  ULInt number_of_solutions(const ULInt target_sum) 
  {
    std::vector<ULIntVec> next;
    for (ULInt n = 1; n < target_sum; n++) {
      next.push_back(ULIntVec({n, n}));
    }

    ULInt sum;
    std::vector<ULIntVec> complete;
    std::vector<ULIntVec> temp;
    std::vector<ULIntVec>::iterator it;
    while (next.size() > 0) {
      temp.clear();
      for (it = next.begin(); it != next.end(); it++) {
        for (ULInt n = 1; n <= it->back(); n++) {
          sum = n + (*it)[0];
          if (sum > target_sum) {
            break;
          }
          else if (sum == target_sum) {
            complete.push_back(ULIntVec(*it));
            complete.back().push_back(n);
            complete.back()[0] = sum;
          }
          else {
            temp.push_back(ULIntVec(*it));
            temp.back().push_back(n);
            temp.back()[0] = sum;
          }
        }
      }
      next = temp;
    }
    return complete.size();
  }
}


namespace Solution_2 {
  inline ULInt ceil(ULInt m, ULInt n) 
  {
    if (m <= n) {
      return 1;
    }
    else if (m % n == 0) {
      return m / n;
    }
    else {
      return (m / n + 1);
    }
  }

  inline ULInt min(ULInt m, ULInt n)
  {
    if (m >= n) {
      return n;
    }
    else {
      return m;
    }
  }


  ULInt num_sums(ULInt target_sum, ULInt num_terms, ULInt max_val)
  {
    // std::cout << "(" << target_sum << ", " << num_terms << ", " << max_val << ")" << std::endl;
    ULInt max_leading_term = target_sum - (num_terms - 1);  // The (n + 1 + ... + 1) case 
    
    if (max_leading_term < 3 || num_terms == 1) {
      return 1;
    }

    ULInt count = 0;
    for (ULInt n = ceil(target_sum, num_terms); n <= min(max_leading_term, max_val); n++) {
      count += num_sums(target_sum - n, num_terms - 1, n);
    }
    return count;
  }


  ULInt number_of_solutions(const ULInt target_sum) 
  {
    ULInt count = 0;
    for (ULInt num_terms = 2; num_terms <= target_sum; num_terms++) {  
      for (ULInt n = ceil(target_sum, num_terms); n <= (target_sum - num_terms + 1); n++) {
        count += num_sums(target_sum - n, num_terms - 1, n);
      }
    }
    return count;
  }
};


namespace Solution_3 {
  ULInt number_of_solutions(const ULInt target_sum) 
  {
    // Create and zero initialize an array:
    ULInt* solutions = new ULInt[target_sum + 1];
    for (ULInt n = 0; n < (target_sum + 1); n++) {
      solutions[n] = 0;
    }

    // We define 1 sum of for target_sum = 0:
    solutions[0] = 1;  

    // Find solutions:
    for (ULInt vals = 1; vals < target_sum; vals++) {
      for (ULInt n = vals; n <= target_sum; n++) {  // n > val as 0 is the least remainder.
        solutions[n] += solutions[n - vals];
      }
    }

    ULInt count = solutions[target_sum];
    delete[] solutions;
    return count;
  }
};


int main() 
{
  const ULInt TARGET_SUM = 100;

  // // Solution 1:
  // std::cout << "Number of solution for \"" << TARGET_SUM << "\": "
  //           << Solution_1a::number_of_solutions(TARGET_SUM) << std::endl;
  // std::cout << "Number of solution for \"" << TARGET_SUM << "\": "
  //           << Solution_1b::number_of_solutions(TARGET_SUM) << std::endl;

  // // Solution 2:
  // std::cout << "Number of solution for \"" << TARGET_SUM << "\": "
  //           << Solution_2::number_of_solutions(TARGET_SUM) << std::endl;

  // Solution 3:
  std::cout << "Number of solution for \"" << TARGET_SUM << "\": "
            << Solution_3::number_of_solutions(TARGET_SUM) << std::endl;

  return 0;
}
