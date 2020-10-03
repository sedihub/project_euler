/* 
PROBLEM:
  Find the sum of all the multiples of 3 or 5 below 1000.


Solution:
  Find those of 3, find those of 5, remove double counts.
  We can find all tge multiplies of n less than M using:
    {n * x such that x is in the range (1, N / n)}
  
  Since the gcd(3, 5) == 1, the double counts must be
  multiples of 15. Therefore, the desired sum is:

  3 * (N / 3) + 5 * (N / 5) - 15 * (N / 15) 

  ANSWER: 233168
**/

#include <iostream>
#include <sstream>


int str_to_int(char *str)
{
  std::istringstream ss(str);
  int x;
  if (!(ss >> x)) {
    std::cerr << "Invalid number: " << str << '\n';
    return -1;
  } 
  else {
    return x;
  }
}


int main(int argc, char **argv)
{
  int upper_limit = 1000;
  int n1 = 3;
  int n2 = 5;
 
  if (argc != 1 and argc != 2 and argc != 4) {
    std::cout << "ERROR: None, one or three integers are expected!" << std::endl;
    return 1;
  }
  else if (argc == 2) {
    upper_limit = str_to_int(argv[1]);
    std::cout << "\tN  <--- " << upper_limit << std::endl;
  }
  else if (argc == 4){
    n1 = str_to_int(argv[1]);
    n2 = str_to_int(argv[2]);
    upper_limit = str_to_int(argv[3]);
    std::cout << "\tn1 <--- " << n1 << std::endl;
    std::cout << "\tn2 <--- " << n2 << std::endl;
    std::cout << "\tN  <--- " << upper_limit << std::endl;
  }

  int n12 = n1 * n2;
  int sum = 0;
  int largest_multiplicant = 0;
  
  // For n1:
  largest_multiplicant = (upper_limit - 1) / n1;
  sum += n1 * largest_multiplicant * (largest_multiplicant + 1) / 2;
  
  // For n2:
  largest_multiplicant = (upper_limit - 1) / n2;
  sum += n2 * largest_multiplicant * (largest_multiplicant + 1) / 2;
  
  // The overlap:
  largest_multiplicant = (upper_limit - 1) / n12;
  sum -= n12 * largest_multiplicant * (largest_multiplicant + 1) / 2;

  std::cout << sum << std::endl;

  return 0;
}
