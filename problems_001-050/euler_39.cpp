/*
PROBLEM:
  If p is the perimeter of a right angle triangle with integral length sides, {a,b,c}, there are
  exactly three solutions for p = 120.

        {20,48,52}, {24,45,51}, {30,40,50}

  For which value of p <= 1000, is the number of solutions maximized?


SOLUTION: 
  Let's see if we can utilize the Pythagorean triple properties: We want the perimeter,

        p = a + b + c 
          = a + b + \sqrt(a^2 + b^2)

  where a, b, and c are all integers. Pythagorean triples are generated by:

        a = k(m^2 - n^2)
        b = 2 k m n
        c = k(m^2 + n^2)

  Thus, p = k (m^2 + 2mn) = k * m * (m + 2n), where k, m and n are all relatively prime and n < m. 
  
  For the number of solutions to be maximized, p has to have have at least three prime factors. It
  is easier to search in the space of {k, m, n}. Since p <= 1000, m cannot be larger than 32. 

  Finally, we need to consider the uniqueness of triangle given the {k, m, n} triple. This will be
  guaranteed as long as GCD(m, n) = 1;

  ANSWER: 840 which has 6 solutions.
**/


#include <iostream>
#include <map>

typedef unsigned int uint;

/*
std::map<uint, uint> prime_decomposition(uint n)
{
  std::map<uint, uint> decomposition;
  if (n == 1 || n == 0) {
    return decomposition;
  }

  uint k = 2;
  while (n > 1) {
    if (n % k == 0) {
      decomposition[k] = 0;
      while (n % k == 0 && n != 0) {
        decomposition[k]++;
        n /= k;
      }
    }
    k++;
  }

  return decomposition;
}


void print_dcomposition(const std::map<uint, uint> & decomp, uint &n)
{
  std::map<uint, uint>::const_iterator it ;
  std::cout << "\t" << n << " = ";
  for (it = decomp.begin(); it != decomp.end(); it++) {
    std::cout << "(" << it->first << "^" << it->second << ")";
  }
  std::cout << std::endl;
}
*/


inline uint perimeter(uint k, uint m, uint n)
{
  return k * m * (m + 2 * n);
}


bool are_relatively_prime(uint m, uint n)
{
  if (m > n) {
    if(m % n == 0) 
      return false;
    for (uint k = 2; k < n; k++) {
      if (n % k == 0 && m % k == 0) 
        return false;
    }
    return true;
  }
  else if (n < m) {
    if(n % m == 0) 
      return false;
    for (uint k = 2; k < m; k++) {
      if (m % k == 0 && n % k == 0) 
        return false;
    }
    return true;
  }
  else
    return false;
}

 
int main()
{
  std::map<uint, uint> perimeter_solutions_counts;

  // Find the number of solutions corresponding to each perimeter value:
  uint k, p;
  for (uint m = 2; m < 32; m++) {
    for (uint n = 1; n < m; n++) {
      if (!are_relatively_prime(m, n))
        continue;
      k = 1;
      p = perimeter(k, m, n);
      while (p <= 1000) {
        if (perimeter_solutions_counts.find(p) == perimeter_solutions_counts.end()) {
          perimeter_solutions_counts[p] = 1;
        }
        else {
          perimeter_solutions_counts[p]++;
        }
        std::cout << "\t" << p << ":\tk = " << k << ", m = " << m << ", n = " << n << std::endl; 
        k++;
        p = perimeter(k, m, n);
      }
    }
  } 
    

  // Find the perimeter with the maximum number of solutions:
  uint max_p = 0;
  uint max_num_solutions = 0;
  std::map<uint, uint>::iterator it = perimeter_solutions_counts.begin();
  while (it != perimeter_solutions_counts.end()) {
    if (it->second > max_num_solutions) {
      max_p = it->first;
      max_num_solutions = it->second;
    }
    it++;
  }
  std::cout << max_p << " has " << max_num_solutions << " solutions!" << std::endl;

  return 0;
}
