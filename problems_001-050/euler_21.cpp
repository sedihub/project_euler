/*
PROBLEM:
  Let d(n) be defined as the sum of proper divisors of n (numbers less than n which divide
  evenly into n). If d(a) = b and d(b) = a, where a ≠ b, then a and b are an amicable pair
  and each of a and b are called amicable numbers.

  For example, the proper divisors of 220 are 1, 2, 4, 5, 10, 11, 20, 22, 44, 55 and 110; 
  therefore d(220) = 284. The proper divisors of 284 are 1, 2, 4, 71 and 142; so d(284) = 
  220.

  Evaluate the sum of all the amicable numbers under 10000.


SOLUTION:
  Brute force solution. Not the most efficient or the most elegant one, but works, which
  I'm going to follow. The more elegant solution will likely have a longer run time...

  The answer is: 31626

  One way to make the current solution more efficient is to retail the number of proper 
  divisors of the ones we have visited so far.

  The elegant solution is based on the decomposition into prime factors: Say, `n` has the 
  prime decomposition:
    
    n = (p_0 ^ e_0) * (p_1 ^ e_1) * ... (p_k ^ e_k)
    d(n) = (1 + p_0 + p_0^2 + ... p_0^e_0) * ... (1 + p_k + p_k^2 + ... + p_k^e_k) - n 

  `n` is amicable if: d(d(n)) = n.

  ANSWER: 31626
**/

#include <iostream>
#include <vector>
#include <map>


std::vector<unsigned int> proper_divisors(unsigned int n) 
/*Things can be made more efficient in this function.
**/
{
  std::vector<unsigned int> vec;
  for (unsigned int i = 1; i < n; i++) {
    if (n % i == 0)
      vec.push_back(i);
  }
  return vec;
}


unsigned int sum_proper_divisors(unsigned int n)
{
  unsigned int sum = 0;
  std::vector<unsigned int> vec = proper_divisors(n);
  std::vector<unsigned int>::iterator it;
  for (it = vec.begin(); it != vec.end(); it++) {
    sum += *it;
  }
  
  return sum;
}


int main()
{
  const unsigned int inclusive_limit = 10000;

  std::map<unsigned int,unsigned int> amicablePairs;
  unsigned int temp;
  for (unsigned int i = 4; i <= inclusive_limit; i++){
	   temp = sum_proper_divisors(i);
	   if (sum_proper_divisors(temp) == i) {
	     amicablePairs[i] = temp;
	   }
  } 

  unsigned int sum = 0;
  std::map<unsigned int,unsigned int>::iterator mit;
  for (mit = amicablePairs.begin(); mit != amicablePairs.end(); mit++) {
    if (mit->first != mit->second) {
      sum += mit->first; 
    }
    std::cout << "\t(" << mit->first << ", " << mit->second << ")" << std::endl;
  }
  std::cout << "Sum: " << sum << std::endl; 
  
  return 0;
}
