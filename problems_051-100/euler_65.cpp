/*
PROBLEM:
  The square root of 2 can be written as an infinite continued fraction.

      $$
        \sqrt{2} = 1 + \frac{1}{2 + \frac{1}{2 + \frac{1}{\cdots}}}
      $$
  The infinite continued fraction can be written, $\sqrt{2} = [1; (2)]$, where $(2)$ 
  indicates that 2 repeats ad infinitum. In a similar way, $\sqrt{23} = [4;(1, 3, 1, 8)]$.

  It turns out that the sequence of partial values of continued fractions for square roots 
  provide the best rational approximations. Let us consider the convergents for $\sqrt{2}$:

      $$
        1, \frac{3}{2}, \frac{7}{5}, \frac{17}{12}, \frac{41}{29}, \frac{99}{70}, \cdots
      $$

  What is most surprising is that the important mathematical constant, $e$:

      $$
        e = [2; 1, 2, 1, 1, 4, 1, 1, 6, \cdots, 1, 2k, 1, \cdots]
      $$

  The first ten terms in the sequence of convergents for e are:

      $$
        2, 3, \frac{8}{3}, \frac{11}{4}, \frac{19}{7}, \frac{87}{32}, \frac{106}{39}
        \frac{193}{71}, \frac{1264}{465}, \frac{1457}{536}, \cdots
      $$
  
  The sum of digits in the numerator of the 10th convergent is 17.

  Find the sum of digits in the numerator of the 100th convergent of the continued fraction 
  for $e$.


SOLUTION:
  We want to leverage the periodicity of the continued-fraction representation of $e$.
  We are going to focus on a more convenient parameter, $x$, defined as:

      $$
        e = 2 + \frac{1}{\frac{1}{x}}
      $$

  where, $x$ has the following continued-fraction representation:

      $$
        x = \frac{1}{1 + \frac{1}{2 + \frac{1}{1 + \frac{1}{1 + \frac{1}{4 + \cdots}}}}}
          = [0;1, 2, 1, 1, 4, 1, 1, 6, 1, \cdots]
      $$
  
  Given a rational approximation of $x$, $x_n$, we can readily construct a rational approximation
  for $e$:

      $$
        e_{n} = 2 + \frac{1}{x_{n}}
      $$

  Thus, the 100th rational approximation of $e$ corresponds to $x_{100}$, with $x_{1} = 0$.

  x_{3k+1} can be considered as follows:

      $$
        x_{3k+1} = [0; 1,2,1, 1,4,1, \cdots, 1,3k,1]
      $$

  Now, we can consider each triple (1,2k,1) as a function that operates on a an irreducible input
  $\frac{n}{d}$ as follows:

      $$
        (1, 2k, 1)(\frac{n}{d}) = \frac{(2k+1)d + (2k)n}{(2k+2)d + (2k+1)n}
      $$ 

  The issue is that this construction requires building from right to left.

  As a side note, one can show that if gcd(n, d) = 1, then the output is also an irreducible 
  fraction (?).

  Finally, we need a arbitrary-precision integer representation. 

  ANSWER: 272
          e_{100} = 6963524437876961749120273824619538346438023188214475670667 / 
                    2561737478789858711161539537921323010415623148113041714756
          Sum of numerator digits: 272

**/


#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>


class LargeUInt
{
public:
  LargeUInt()
  {
    vec.clear();
  }

  LargeUInt(unsigned int n)
  {
    vec.clear();
    if (n == 0) vec.push_back('0');
    while (n > 0) {
      vec.push_back(n % 10 + '0');
      n /= 10;
    }

    std::reverse(vec.begin(), vec.end());
  }


  friend std::ostream &operator<<(std::ostream &output, const LargeUInt &lUInt);

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
      sum += char_to_uint(*it);
    }
    return sum;
  }

  unsigned int num_digits()
  {
    std::vector<char>::iterator it = vec.begin();
    while (*it == '0') {
      vec.erase(it);
      it = vec.begin();
    }
    return vec.size();
  }

  LargeUInt operator+(const LargeUInt &n)
  {
    LargeUInt temp = LargeUInt();
    temp.vec.clear();

    unsigned short int carry_over = 0;
    std::vector<char>::const_reverse_iterator lhs = vec.rbegin();
    std::vector<char>::const_reverse_iterator rhs = n.vec.rbegin();
    while (lhs!=vec.rend() && rhs!=(n.vec).rend()) {
      carry_over += char_to_uint(*lhs) + char_to_uint(*rhs);
      (temp.vec).push_back(uint_to_char(carry_over % 10));
      carry_over /= 10;
      lhs++;
      rhs++;
    }
    while (lhs!=vec.rend()) {
      carry_over += char_to_uint(*lhs);
      (temp.vec).push_back(uint_to_char(carry_over % 10));
      carry_over /= 10;
      lhs++;
    }
    while (rhs!=(n.vec).rend()) {
      carry_over += char_to_uint(*rhs);
      (temp.vec).push_back(uint_to_char(carry_over % 10));
      carry_over /= 10;
      rhs++;
    }
    while (carry_over > 0) {
      (temp.vec).push_back(uint_to_char(carry_over % 10));
      carry_over /= 10;
    }
    temp.reverse_digits();

    return temp;
  }

  LargeUInt operator+(const unsigned int &n)
  {
    LargeUInt temp = LargeUInt(n);
    return (temp + *this);
  }

  LargeUInt operator*(const LargeUInt &n)
  {
    if (this->vec == std::vector<char>{'0'} || n.vec == std::vector<char>{'0'}) {
      return LargeUInt(0);
    }

    // A vector used to carry out the multiplication:
    unsigned int length = this->vec.size() + n.vec.size();
    std::vector<unsigned int> temp_vec;
    for (unsigned int i = 0; i <= length; i++) {
      temp_vec.push_back(0);
    }

    // First, the multiply digits:
    unsigned int idx;
    unsigned short int carry_over = 0;
    std::vector<char>::const_reverse_iterator lhs, rhs;
    for (lhs = this->vec.rbegin(); lhs != this->vec.rend(); lhs++) {
      for (rhs = n.vec.rbegin(); rhs != n.vec.rend(); rhs++) {
        idx = std::distance<std::vector<char>::const_reverse_iterator>(this->vec.rbegin(), lhs) +\
              std::distance<std::vector<char>::const_reverse_iterator>(n.vec.rbegin(), rhs);
        carry_over += char_to_uint(*rhs) * char_to_uint(*lhs);
        temp_vec[idx] += carry_over % 10;
        carry_over /= 10;
      }    
      while (carry_over > 0) {
        idx++;
        temp_vec[idx] += carry_over % 10;
        carry_over /= 10;
      }
    }

    // Next, make sure that we have digits -- note that the digits are arranged in reverse:
    carry_over = 0;
    std::vector<unsigned int>::iterator it;
    for (it = temp_vec.begin(); it != temp_vec.end(); it++) {
      carry_over += *it;
      *it = carry_over % 10;
      carry_over /= 10;
    }

    // Remove unneeded zeros at the end:
    while (temp_vec.back() == 0) {
      temp_vec.pop_back();
    }

    // Reverse the vector of digits:
    std::reverse(temp_vec.begin(), temp_vec.end());

    // Assign to a new LargeUInt instance:
    LargeUInt result = LargeUInt();
    for (it = temp_vec.begin(); it != temp_vec.end(); it++) {
      result.vec.push_back(uint_to_char(*it));
    }

    return result;
  } 

  LargeUInt operator*(const unsigned int &n)
  {
    LargeUInt temp = LargeUInt(n);
    return (*this) * temp;
  }

  LargeUInt operator^(const unsigned int &n)
  {
    if (n == 0) {
      return LargeUInt(1);
    }
    else if (n == 1) {
      return *this;
    }
    else {
      unsigned int count = 0; 
      LargeUInt p(1);
      while (count != n) {
        p = p * *this;
        count += 1;
      }
      return p;
    }
  }

protected:
  inline unsigned short int char_to_uint(char c)
  {
    return (unsigned short int)(c - '0');
  }

  inline char uint_to_char(unsigned short int n)
  {
    return (char)n + '0';
  }

private:
  std::vector<char> vec;
};


std::ostream &operator<<(std::ostream &output, const LargeUInt &lUInt) 
{ 
  std::vector<char>::const_iterator it;
  for (it = (lUInt.vec).begin(); it != (lUInt.vec).end(); it++) {
    output << *it;
  }
  return output;            
}


int main()
{
  const unsigned int k_max = 33;

  // x_{3k+1} approximation:
  LargeUInt temp;
  LargeUInt n(0);
  LargeUInt d(1);
  for (unsigned int k = k_max; k > 0; k--) {
    temp = d + n;
    n = (d * (2 * k + 1)) + (n * (2 * k));
    d = n + temp;
  }
  
  // e_{3k+1} approximation:
  n = n + d * 2; 
  std::cout << "e_{" << (3 * k_max + 1) << "} = " << n << " / " << d << std::endl;


  // Sum of digits:
  std::cout << "Sum of numerator digits: " << n.sum_digits() << std::endl;

  return 0;
}
