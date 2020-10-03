/*
PROBLEM:
  The number, 197, is called a circular prime because all rotations of the digits: 197, 971, and
  719, are themselves prime.

  There are thirteen such primes below 100: 2, 3, 5, 7, 11, 13, 17, 31, 37, 71, 73, 79, and 97.

  How many circular primes are there below one million?


SOLUTION:
  Find all primes. Then search for the ones that are circular primes. This way we will have 
  78,498 primes below 10^6 to search through.
  
  Alternatively, we can construct them: A circular prime under 10^6 will have at most 6 digits.
  The digits cannot contain a even digit or five (except 2 and 5 themselves), leaving the set 
  {1, 3, 7, 9}. Also, the sum of the digits cannot be a multiple of 3. An estimated size of the 
  number of sequences (without the constraint of sum of digits not being divisible by 3) is:

        2 + 4^2 + 4^3 + 4^4 + 4^5 + 4^6 = 5458

  We can see that generating candidates is shrinks the search space significantly. Now, I just
  need to generate the candidates properly.

  
  ANSWER: 55
  The solution takes 1.50s. Almost all of this time is spent on finding the primes. So, it seems
  that limiting the search space was not that critical after all.
**/


#include <iostream>
#include <set>
#include <vector>
#include <iterator>


typedef unsigned int uint;


template <typename T>
class PrimalityTest
{
public:
  PrimalityTest(){
    primes.insert(2);
    primes.insert(3);
    primes.insert(5);
  }

  bool is_prime(T n)
  {
    if (n == 1 || n == 0)
      return false;

    for (it = primes.begin(); it != primes.end(); ++it){
      if (n == *it) {
        return true;
      }
      else if (n % (*it) == 0) {
        return false;
      }
      //
      if ((*it) > n / (*it)) {
        for (T m = *(primes.rbegin()); m < n; m++) {
          this->is_prime(m);
        }
        primes.insert(n);
        return true;
      }
    }
    
    // If this number is beyond the range of current primes, get the rest:
    rit = primes.rbegin();
    T m = (*rit);
    while (m <= n) {
      m++;
      this->is_prime(m);
      if (n % m == 0) {
        return false;
      }
    }

    primes.insert(n);
    return true;
  }

  void print_primes(){
    for (it = primes.begin(); it != primes.end(); ++it) {
      std::cout << "\t" << *it << std::endl;
    }
  }

  std::set<T> get_primes() const
  {
    return primes;
  }

protected:
  std::set<T> primes;
  typename std::set<T>::iterator it;
  typename std::set<T>::reverse_iterator rit;
};


namespace solution {
  uint char_to_uint(char &c)
  {
    return (uint)(c - '0');
  }


  char uint_to_char(uint &n)
  {
    return (char)n + '0';
  }


  void char_vec_to_decimal(
    const std::vector<char> &vec, 
    uint &num, 
    uint &num_digits,
    uint &sum_digits)
  {
    char c;
    sum_digits = 0;
    num_digits = 0;
    num = 0;
    std::vector<char>::const_iterator cit;
    for (cit = vec.begin(); cit != vec.end(); cit++) {
      c = *cit;
      if(c == ' ')  continue;
      num = 10 * num + char_to_uint(c);
      sum_digits += char_to_uint(c);
      num_digits++;
    } 
  }

  // Permutations... 
  std::vector< std::vector<char> > generate_candidate_circular_primes(
    std::vector< std::vector<char> > &previous,
    const std::vector<char> &allowed_elements,
    uint remaining_lenght)
  {
    if(remaining_lenght == 0) return previous;

    std::vector<char>::const_iterator elem_cit; 
    std::vector< std::vector<char> >::iterator it;
    
    std::vector< std::vector<char> > current;
    uint idx = 0;
    for (it = previous.begin(); it != previous.end(); it++) {
      if (it->back() == ' ') {
        current.push_back(std::vector<char>());
        current[idx] = *it;
        current[idx].push_back(' ');
        idx++;
      }
      for (elem_cit = allowed_elements.begin(); elem_cit != allowed_elements.end(); elem_cit++) {
        current.push_back(std::vector<char>());
        current[idx] = *it;
        current[idx].push_back(*elem_cit);
        idx++;
      }
    }

    return generate_candidate_circular_primes(
      current, 
      allowed_elements,
      (remaining_lenght - 1)
    );
  }


  uint pow(const uint &a, uint n)
  {
    if(n == 0) return 0;
    else if(n == 1) return a;

    uint result = 1;
    while (n > 0) {
      result *= a;
      n--;
    }

    return result;
  }


  bool is_circular_prime(
    uint num, 
    const uint &num_digits, 
    const uint &sum_digits, 
    PrimalityTest<uint> *pt_ptr)
  {
    // Check if n is divisible by 3
    if (sum_digits % 3 == 0 && num != 3) 
      return false; 

    // Compute the most significant decimal:
    uint msd = pow(10, (num_digits - 1));

    // Permute and check primality:
    for (uint i = 0; i < num_digits; i++) {
      if(!pt_ptr->is_prime(num))
        return false;
      num = msd * (num % 10) + (num / 10);
    }

    return true;
  }
}


int main()
{
  const uint upper_limit = 1000000;
  uint circular_prime_count = 0;
  PrimalityTest<uint> pt;  // To determine if a permutation is prime.


  // Compile a list of candidates:
  std::vector<char> allowd_elements = {'1', '3', '7', '9'};
  std::vector< std::vector<char> > candidates = {
    {' '}, {'1'}, {'3'}, {'7'}, {'9'}
  };
  candidates = solution::generate_candidate_circular_primes(
    candidates, allowd_elements, 5);

  // Check candidates:
  circular_prime_count += 2;  // For 2 and 5
  std::cout << "\t\"2\"" << std::endl;
  std::cout << "\t\"5\"" << std::endl;
  uint num, num_digits, sum_digits;
  std::vector< std::vector<char> >::iterator it;
  std::vector<char>::iterator it2;
  for (it = candidates.begin(); it != candidates.end(); it++) {
    solution::char_vec_to_decimal(*it, num, num_digits, sum_digits);
    if (solution::is_circular_prime(num, num_digits, sum_digits, &pt)) {
      std::cout << "\t";
      for (it2 = it->begin(); it2 != it->end(); it2++) 
        std::cout << *it2;
      std::cout << std::endl;
      circular_prime_count++;
    }
  }

  std::cout << "Number of circular primes below " << upper_limit 
        << ": " << circular_prime_count << std::endl;
  std::cout << pt.get_primes().size() << std::endl;

  return 0;
}
