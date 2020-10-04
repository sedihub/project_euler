/*
PROBLEM:
  We shall say that an n-digit number is pandigital if it makes use of all 
  the digits 1 to n exactly once. For example, 2143 is a 4-digit pandigital 
  and is also prime.

  What is the largest n-digit pandigital prime that exists?


SOLUTION: 
  Okay, the brute-force solution is not going to be efficient: Find all pandigital
  integers below 987654322 then check primality and finally return the largest.

  A more efficient solution can be constructed by generating all possible pandigital
  numbers. Since we are looking for primes, we can carry out a few simple checks to
  weed out the obvious cases.

  Finally, note that 9-digit and 8-digit pandigital numbers are all divisible by 3.
  7-, 5-, and 1-digit pandigital numbers are the only ones that are not divisible by
  3. 

  Note that I generate the candidates in the lexicographical order. Thus I will traverse
  the vector of vectors in the reverse order.

  ANSWER: 7652413
**/

#include <iostream>
#include <algorithm>
#include <vector>


typedef unsigned short int us;


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


void generate_pandigitals(
  us length,
  std::vector< std::vector<us> > &pandigitals, 
  us step_number=0)
/* Recursively generates pandigitals of all length (max is obviously 9).
**/
{
  if(step_number == length) {
    return;
  }
  else if (step_number == 0){
    pandigitals.clear();
    for (us n = 1; n <= length; n++){
      pandigitals.push_back(
        std::vector<us>{n}
      );
    }
    generate_pandigitals(length, pandigitals, ++step_number);
  }
  else {
    unsigned int current_step_idx = 0;
    std::vector< std::vector<us> > current_step = {};
    std::vector< std::vector<us> >::iterator it;
    for (it = pandigitals.begin(); it != pandigitals.end(); it++) {
      for (us n = 1; n <= length; n++) {
        if(std::find(it->begin(), it->end(), n) != it->end())
          continue;
        current_step.push_back(std::vector<us>());
        current_step[current_step_idx] = *it;
        current_step[current_step_idx].push_back(n);
        current_step_idx++;
      }
    }
    pandigitals = current_step;
    generate_pandigitals(length, pandigitals, ++step_number);
  }
}


void print_vector(const std::vector<us> *ptr)
{
  std::vector<us>::const_iterator it; 
  std::cout << "\t";
  for (it = ptr->begin(); it != ptr->end(); it++)
    std::cout << *it;
  std::cout << std::endl; 
}


void print_candidates(
  std::vector< std::vector<us> > &pandigitals)
{
  std::vector< std::vector<us> >::iterator it;
  for (it = pandigitals.begin(); it != pandigitals.end(); it++) {
    print_vector(&*it);
  }
  std::cout << "Size: " << pandigitals.size() << std::endl;
}


unsigned int vector_to_number(const std::vector<us> &vec)
{
  unsigned int num = 0;
  std::vector<us>::const_iterator it;
  for (it = vec.begin(); it != vec.end(); it++) {
    num *= 10;
    num += *it;
  }
  return num;
}


unsigned int find_largest_prime(
  std::vector< std::vector<us> > &pandigitals)
{
  unsigned int numerical_rep;
  std::vector< std::vector<us> >::reverse_iterator rit;
  for (rit = pandigitals.rbegin(); rit != pandigitals.rend(); rit++) {
    if (rit->back() % 2 == 0 || rit->back() == 5)
      continue;
    // print_vector(&*rit);
    numerical_rep = vector_to_number(*rit);
    // std::cout << numerical_rep << std::endl;
    if (is_prime<unsigned int>(numerical_rep))
      return numerical_rep;
  }

  return 0;
}


int main()
{
  std::vector< std::vector<us> > pandigitals;

  // Check 7-digit pandigitals:
  generate_pandigitals(7, pandigitals);
  // print_candidates(pandigitals);
  std::cout << find_largest_prime(pandigitals) << std::endl;

  return 0;
}
