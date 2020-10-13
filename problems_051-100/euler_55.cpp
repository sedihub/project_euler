/*
PROBLEM:
  If we take 47, reverse and add, 47 + 74 = 121, which is palindromic.

  Not all numbers produce palindromes so quickly. For example,

          349 + 943 = 1292,
          1292 + 2921 = 4213
          4213 + 3124 = 7337

  That is, 349 took three iterations to arrive at a palindrome.

  Although no one has proved it yet, it is thought that some numbers, like 196, never produce
  a palindrome. A number that never forms a palindrome through the reverse and add process is
  called a Lychrel number. Due to the theoretical nature of these numbers, and for the purpose
  of this problem, we shall assume that a number is Lychrel until proven otherwise. In addition
  you are given that for every number below ten-thousand, it will either (i) become a palindrome
  in less than fifty iterations, or, (ii) no one, with all the computing power that exists, has
  managed so far to map it to a palindrome. In fact, 10677 is the first number to be shown to 
  require over fifty iterations before producing a palindrome: 4668731596684224866951378664 
  (53 iterations, 28-digits).

  Surprisingly, there are palindromic numbers that are themselves Lychrel numbers; the first 
  example is 4994.

  How many Lychrel numbers are there below ten-thousand?


SOLUTION:
  Brute-force solution using a custom large-int class! 

  ANSWER: 249
**/

#include <iostream>
#include <limits>
#include <vector>
#include <iterator>
#include <algorithm>


class LargeUInt
{
public:
  LargeUInt()
  {
    vec.clear();
  }

  LargeUInt( unsigned long int n )
  {
    vec.clear();
    if (n == 0) vec.push_back('0');
    while (n > 0)
    {
      vec.push_back(n % 10 + '0');
      n /= 10;
    }

    std::reverse(vec.begin(), vec.end());
  }


  friend std::ostream &operator<<(std::ostream &output, const LargeUInt &lUInt) 
  { 
    std::vector<char>::const_iterator it;
    for (it = (lUInt.vec).begin(); it != (lUInt.vec).end(); it++) {
      output << *it;
    }
    return output;            
  }

  void reverse_digits()
  {
    std::reverse(vec.begin(),vec.end());
    std::vector<char>::iterator it = vec.begin();
    while (*it == '0') {
      vec.erase(it);
      it = vec.begin();
    }
  }

  unsigned int sum_digits()
  {
    unsigned int sum = 0;
    std::vector<char>::iterator it;
    for (it = vec.begin(); it != vec.end(); it++) {
      sum += *it;
    }
    return sum;
  }

  unsigned int num_digits()
  {
    std::vector<char>::iterator it = vec.begin();
    while( *it == '0' )
    {
      vec.erase(it);
      it = vec.begin();
    }
    return vec.size();
  }

  // LargeUInt operator*(const LargeUInt &n)
  // {}


  // LargeUInt operator*(const unsigned long int &n)
  // {
  //   LargeUInt temp = LargeUInt(n);
  //   return ( (*this) * temp );
  // }

  LargeUInt operator+(const LargeUInt &n)
  {
    LargeUInt temp = LargeUInt();
    (temp.vec).clear();

    unsigned int carryOver = 0;
    std::vector<char>::const_reverse_iterator lhs = vec.rbegin();
    std::vector<char>::const_reverse_iterator rhs = (n.vec).rbegin();
    while (lhs!=vec.rend() && rhs!=(n.vec).rend()) {
      carryOver += (unsigned int)(*lhs-'0')+(unsigned int)(*rhs-'0');
      (temp.vec).push_back(carryOver%10+'0');
      carryOver /= 10;
      lhs++;
      rhs++;
    }
    while (lhs!=vec.rend()) {
      carryOver += (unsigned int)(*lhs-'0');
      (temp.vec).push_back(carryOver%10+'0');
      carryOver /= 10;
      lhs++;
    }
    while (rhs!=(n.vec).rend()) {
      carryOver += (unsigned int)(*rhs-'0');
      (temp.vec).push_back(carryOver%10+'0');
      carryOver /= 10;
      rhs++;
    }
    while (carryOver > 0) {
      (temp.vec).push_back(carryOver%10+'0');
      carryOver /= 10;
    }
    temp.reverse_digits();

    return temp;
  }


  LargeUInt operator+( const unsigned long int &n )
  {
    LargeUInt temp = LargeUInt(n);
    return (temp + *this);
  }

  bool is_palindrom()
  {
    std::vector<char>::iterator itL = vec.begin();
    std::vector<char>::iterator itR = vec.end()-1;
    while (itL < itR) {
      if (*itL != *itR) return false;
      itL++;
      itR--;
    }
    return true;
  }

private:
  std::vector<char> vec;
};


int main()
{
  LargeUInt n, rn;
  unsigned int lychrels_count = 0;
  unsigned int count;
  for (unsigned long int i = 1; i <= 10000; i++) {
    n = LargeUInt(i);
    count = 0;
    while (count <= 50) {
      count++;
      rn = n;
      rn.reverse_digits();
      n = n + rn;
      if (n.is_palindrom()) {
        std::cout << "[" << count << "]:\t" << n << std::endl; 
        break; 
      }
    }
    if (count > 50) lychrels_count++;
  }
  std::cout << "Number of Lychrels: " << lychrels_count << std::endl;

  return 0;
}
