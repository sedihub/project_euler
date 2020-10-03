/*
PROBLEM:
  A permutation is an ordered arrangement of objects. For example, 3124 is one possible 
  permutation of the digits 1, 2, 3 and 4. If all of the permutations are listed numerically 
  or alphabetically, we call it lexicographic order. The lexicographic permutations of 0, 1 
  and 2 are:

    012   021   102   120   201   210

  What is the millionth lexicographic permutation of the digits 0, 1, 2, 3, 4, 5, 6, 7, 8 
  and 9?

SOLUTION:
  For N elements, there will be N! permutations. An interesting aspect of lexicographically
  ordered permutations is that we can recursively obtain permutations from those of the 
  sublists:

    {a_1, a_2, ..., a_n} = 
    a_n{a_2, ..., a_1}, a_{n-1}{a_2, ...,a_1, a_n}, ..., a_1{a_2, a_3, ..., a_n}

  There are n terms in the r.h.s.. Thus the number of permutations of n elements is the same
  as n x perms(n-1) as expected. This also allows us to systematically access kth permutation:

  Here is how to find the kth permutation:
   - Find the largest n such that n! > k. If n! == k, then that's the reverse-ordered sequence.
   - Determine floor((n-1)! / k). This identifies which permutation of those above are the one
     to explore.
   - k = (n-1)! % k and n = (n-1). Repeat until k = 0. Each round we "pop" an element from left. 


  ANSWER: 2783915460
**/

#include <iostream>
#include <sstream>
//#include <iomanip>


typedef unsigned int uint;


uint factorial(uint n)
{
  uint n_factorial = 1;
  while (n > 1) {
    n_factorial *= n;
    n--;
  }
  return n_factorial;
}


int main(int argc, char **argv)
{
  uint k; 
  if (argc == 1) {
    k = 1000000;
  } 
  else if (argc == 2) {
    std::istringstream ss(argv[1]);
    if (!(ss >> k)) {
      std::cerr << "Invalid number: " << argv[1] << '\n';
    } else if (!ss.eof()) {
      std::cerr << "Trailing characters after number: " << argv[1] << '\n';
    }
  }
  else {
    std::cerr << "ERROR: Expects at most one argument!" << std::endl;
    return 1; 
  }
  char kth_perm[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

  // Decompose k into factorials: k = k_m * m! + k_{m-1} * (m-1)! + ...
  uint kth = k - 1;  // The initial sequence is the first permutation.
  uint n_fact;
  uint fact_decom[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  for (uint n = 0; n < 10; n++) {
    n_fact = factorial(10 - n);
    if(kth == 0) 
      break;
    else {
      fact_decom[n] = kth / n_fact;
      kth = kth % n_fact;
    }
  }

  // Print decomposition:
  kth = k - 1;
  std::cout << std::endl << kth << " = ";
  for (uint n = 0; n < 10; n++){
    std::cout << "(" << fact_decom[n] << " x " << (10 - n) << "!)";
    if (n < 9) std::cout << " + ";
  }
  std::cout << std::endl;

  // Given the decomposition, we compile the permutation:
  // Replace the current n_th element with the one idx ahead
  // After replacing, we should shift so that in the subsequence
  // the shortest lexicographical order is established.
  // So, we bubble the (n + idx) up to n+1 and then replace.
  char temp;
  uint idx;
  for (uint n = 0; n < 9; n++) {
    idx = n + fact_decom[n + 1]; 
    // Bubble up and replace in one shot 
    while (idx > n) {  
      temp = kth_perm[idx - 1];
      kth_perm[idx - 1] = kth_perm[idx];
      kth_perm[idx] = temp;
      idx--;
    }
  }

  // Print the sequence 
  std::cout << "The " << k << "th permutation is: ";
  for (uint idx = 0; idx < 10; idx++) {
    std::cout << kth_perm[idx];
  }
  std::cout << std::endl;

  return 0;
}
