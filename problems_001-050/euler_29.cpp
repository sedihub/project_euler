/*
PROBLEM:
  Consider all integer combinations of a^b for 2 ≤ a ≤ 5 and 2 ≤ b ≤ 5:

      2^2 = 4,  2^3 = 8,   2^4 = 16,  2^5 = 32
      3^2 = 9,  3^3 = 27,  3^4 = 81,  3^5 = 243
      4^2 = 16, 4^3 = 64,  4^4 = 256, 4^5 = 1024
      5^2 = 25, 5^3 = 125, 5^4 = 625, 5^5 = 3125

  If they are then placed in numerical order, with any repeats removed, we get the following 
  sequence of 15 distinct terms:

      4, 8, 9, 16, 25, 27, 32, 64, 81, 125, 243, 256, 625, 1024, 3125

  How many distinct terms are in the sequence generated by a^b for 2 ≤ a ≤ 100 and 2 ≤ b ≤ 100?


SOLUTION:
  Here is the idea: Given `a` and `b`, factorize `a` and form a map with prime factors of `a`
  as keys and values of b times the corresponding exponent.

  Finally, note that the use of primality test is just to speed things up. Technically, when
  decomposing a number into its prime factors, since after visiting each prime factor, we have

      gcd(n/q^e, q) = 1

  we don't have to worry about other powers of q. This is of course not the case if we instead
  of prime decomposition were interested in numbers that are coprime.
  

  ANSWER: 9183
**/


#include <iostream>
#include <map>
#include <set>
#include <iterator>


typedef std::map<unsigned int, unsigned int> uint_map_type;


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
    if(n == 1)
      return false;
    if (primes.find(n) != primes.end())
      return true;
    for (it = primes.begin(); it != primes.end(); ++it){
      if (n % (*it) == 0) {
        return false;
      }
      if ((*it) * (*it) > n) {
        primes.insert(n);
        return true;
      }
    }
    //
    // If this number is beyond the range of current primes, get the rest:
    rit = primes.rbegin();
    std::advance(rit, 1);
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

protected:
  std::set<T> primes;
  typename std::set<T>::iterator it;
  typename std::set<T>::reverse_iterator rit;
};


uint_map_type factorize(
  unsigned int n, 
  PrimalityTest<unsigned int> *is_prime_ptr, 
  bool verbose=false)
{
  uint_map_type factorized_n;
  unsigned int q = 2;
  if (verbose) std::cout << "\t" << n << " = ";
  while (n > 1) {
    while (! is_prime_ptr->is_prime(q)) {
      q++;  // Just to speed up things; in principle can do without. See the note above.
    }
    //
    if (n % q == 0){
      if (verbose) std::cout << q << "^";
      factorized_n[q] = 1;
      n /= q;
      while (n % q == 0) {
        factorized_n[q]++;
        n /= q;
      }
      if (verbose) { 
        std::cout << factorized_n[q];
        if (n > 1) std::cout << " * ";
      }
    }
    q++;
  }
  if (verbose) std::cout << std::endl;

  return factorized_n;
}


int main()
{
  uint_map_type factroized_n;
  PrimalityTest<unsigned int> pt;

  uint_map_type temp;
  std::set<uint_map_type> unique_pairs;
  for (unsigned int a = 2; a <= 100; a++) {
    factroized_n = factorize(a, &pt);
    for (unsigned int b = 2; b <= 100; b++) { // create various powers of b and add them to the set
      temp = factroized_n;
      for (uint_map_type::iterator it = temp.begin(); it != temp.end(); it++){
        it->second *= b;
      }
      unique_pairs.insert(temp);
    }
  }

  std::cout << "Number of unique terms: " << unique_pairs.size() << std::endl;

  return 0;
}
