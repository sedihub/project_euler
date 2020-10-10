/*
PROBLEM:
  By replacing the 1st digit of the 2-digit number *3, it turns out that six of the nine possible
  values: 13, 23, 43, 53, 73, and 83, are all prime.

  By replacing the 3rd and 4th digits of 56**3 with the same digit, this 5-digit number is the 
  first example having seven primes among the ten generated numbers, yielding the family: 56003, 
  56113, 56333, 56443, 56663, 56773, and 56993. Consequently 56003, being the first member of 
  this family, is the smallest prime with this property.

  Find the smallest prime which, by replacing part of the number (not necessarily adjacent digits)
  with the same digit, is part of an eight prime value family.


SOLUTION:
  Here is the idea, find primes in the ascending order. The candidate must include at least one 
  pair of repeating digits.

  ANSWER: 121313
**/

#include "iostream"
#include "vector"
#include "iterator"
#include "algorithm"
#include "set"


bool is_prime(unsigned long int n)
{
  if (n == 2 ) return true;
  else if (n == 3) return true;
  else if (n == 5) return true;
  else if (n % 2  == 0) return false;
  else if (n % 3  == 0) return false;
  else {
    unsigned long int k = 6;
    while (k * k <= n) {
      if (n % (k + 1) == 0) return false;
      if (n % (k + 5) == 0) return false;
      k += 6;
    }
    return true;
  }
}


template<typename T> void print_vector(const std::vector<T> &vec, bool reverse=false)
{
  std::cout << "\t";
  if (reverse) {
    typename std::vector<T>::const_reverse_iterator rit;
    for (rit = vec.rbegin(); rit != vec.rend(); rit++){
      std::cout << *rit << " ";
    }
  }
  else {
    typename std::vector<T>::const_iterator it;
    for (it = vec.begin(); it != vec.end(); it++) {
      std::cout << *it << " ";
    }
  }
  std::cout << std::endl;
}


void ulint_to_char_vec(unsigned long int n, std::vector<char> &vec)
{
  vec.clear();
  while (n > 0) {
    vec.push_back(n % 10 + '0');
    n /= 10;
  }
  std::reverse(vec.begin(),vec.end());
}


unsigned long int char_vec_to_ulint(const std::vector<char> &vec)
{
  unsigned long int n = 0;
  unsigned long int p = 1;
  std::vector<char>::const_reverse_iterator rit;
  for (rit = vec.rbegin(); rit != vec.rend(); rit++){
    n += p*(*rit-'0');
    p *= 10;
  }

  return n;
}


bool contains_at_least_one_repeat_digit( const std::vector<char> &vec )
{
  for( std::vector<char>::const_iterator it = vec.begin() ; it != vec.end()-1 ; it++ )
  {
    if( find(it+1,vec.end(),*it) != vec.end() ){ return true; }
  }
  return false;
}


bool is_the_smallest_eight_prime_family( const std::vector<char> &vec )
/** Based on divisibility by 3, it can be shown that one or three (or six, etc.) digits need to be
   replaced...
   - For a family of seven primes, 2 digits suffices. Also, in that case I found 2207. Presumably
     the question means primes of the same length...
   - For family of eith primes, I first got 1 1 1 1 0 9. 

   - SOMETHING IS WRONG WITH THIS PROBLEM. I GOT THESE:

            111109
            111857
            121313  <---- The Answer...
            141619
            222109
            222323
            222857
            242629
              .
              .
              .

   - I see, the one that starts with zero, strictly speaking cannot belong to the family. To force
     this, I added "&& temp_vec[0]!=0" on line 133.
  */
{
  unsigned int count;
  std::vector<char> temp_vec;
  std::vector<char>::const_iterator it0;
  std::vector<char>::const_iterator it1;
  std::vector<char>::const_iterator it2;
  for (it0 = vec.begin(); it0 != vec.end()-3; it0++)
  {
    // Ignore the last digit as once replaced with an even digit, the result will not be a prime:
    for( it1 = it0+1 ; it1 != vec.end()-2 ; it1++) { 
      if (*it1 != *it0) continue; 
      // Ignore the last digit as once replaced with an even digit, the result will not be a prime:
      for (it2 = it1 + 1; it2 != vec.end()-1; it2++) { 
        if( *it2 == *it1 ) { 
          temp_vec = vec;
          count = 0;
          for(char c = '0'; c <= '9'; c++) {
            temp_vec[std::distance(vec.begin(), it0)] = c;
            temp_vec[std::distance(vec.begin(), it1)] = c;
            temp_vec[std::distance(vec.begin(), it2)] = c;
            //print_vector<char>( temp_vec );
            //std::cout << "\t" << char_vec_to_ulint(temp_vec) << "\t" << is_prime(char_vec_to_ulint(temp_vec)) << std::endl;
            if (is_prime(char_vec_to_ulint(temp_vec)) && temp_vec[0]!='0') count++;
          }
          if (count == 8) {
            std::cout << "\t" << char_vec_to_ulint(vec) << std::endl;
            return true;
          }
        }
      }
    }
  } 
  return false;
}


int main()
{ 
  std::vector<char> vec;
  std::vector<char>::iterator it;

  unsigned long int n = 102;  // = 6 * 17  
  while (true) {
    if (is_prime(n + 1)) {
      ulint_to_char_vec(n + 1, vec);
      if (contains_at_least_one_repeat_digit(vec)) {
        if (is_the_smallest_eight_prime_family(vec)) { 
          print_vector<char>(vec); 
          break;
        }
      }
    }
    if (is_prime(n + 5)) {
      ulint_to_char_vec(n + 5, vec);
      if (contains_at_least_one_repeat_digit(vec)) {
        if (is_the_smallest_eight_prime_family(vec)) { 
          print_vector<char>(vec); 
          break;
        }
      }
    }
    n += 6;
  }

  return 0;
}
