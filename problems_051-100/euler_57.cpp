/*
PROBLEM:
  It is possible to show that the square root of two can be expressed as an infinite continued
  fraction.

        \sqrt{2} = 1 + \frac{1}{2 + \frac{1}{2 + \frac{1}{2 + \cdots}}}

  By expanding this for the first four iterations, we get:

        1 + \frac{1}{2} = 3/2 = 1.5
        1 + \frac{1}{2 + \frac{1}{2}} = 7/5 = 1.4
        1 + \frac{1}{2 + \frac{1}{2+\frac{1}{2}}} = 1/17
        1 + \frac{1}{2 + \frac{1}{2+\frac{1}{2+\frac{1}{2}}}} = 41/29
        \cdots

  The next three expansions are 99/70, 239/169, and 577/408, but the eighth expansion, 1393/985, 
  is the first example where the number of digits in the numerator exceeds the number of digits 
  in the denominator.

  In the first one-thousand expansions, how many fractions contain a numerator with more digits 
  than the denominator?


SOLUTION:
  We need to convert the finite approximation of $\sqrt{2}$ into a recursive relation:

        f_{n} = 1 + \frac{1}{2 + (f_{n-1} - 1)} = 1 + \frac{1}{1 + f_{n-1}}  

  with f_{0} = 1. Here are the first few terms:

        f_{1} = 1 + 1/2           = 3/2
        f_{2} = 1 + 1/( 2 + 1/2 ) = 7/5
        f_{3} = 1 + 1/( 2 + 2/5 ) = 1/17

  If we represent f_{n} as \frac{n_{n}}{d_{n}}, where $n_{n}$ and $d_{n}$ are integers, we find:
  
        \frac{n_{n}}{d_{n}} = 1 + \frac{d_{n}}{d_{n} + n_{n}} 
                            = \frac{n_{n} + 2d_{n}}{d_{n} + n_{n}}

  With, $n_{0} = 1$ and $d_{0} = 1$, we find:

        n_{1} = 3, d_{1} = 2
        n_{2} = 7, d_{2} = 5

  Now we can quickly find the 

  ANSWER: 153
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

  LargeUInt(unsigned long int n)
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

  LargeUInt operator+(const unsigned long int &n)
  {
    LargeUInt temp = LargeUInt(n);
    return (temp + *this);
  }

  LargeUInt operator*(const LargeUInt &n)
  {
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

    // Next, make sure that we have digits -- note that the digits are aranged in reverse:
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

  LargeUInt operator*(const unsigned long int &n)
  {
    LargeUInt temp = LargeUInt(n);
    return (*this) * temp;
  }

  LargeUInt operator^(const unsigned long int &n)
  {
    if (n == 0) {
      return LargeUInt(1);
    }
    else if (n == 1) {
      return *this;
    }
    else {
      unsigned long int count = 0; 
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
  const unsigned int upper_limit = 1000;

  
  unsigned int count = 0;
  LargeUInt numerator(1);
  LargeUInt denominator(1);
  LargeUInt temp;
  for (unsigned int n=1; n <= upper_limit; n++) {
    temp = denominator;
    denominator = denominator + numerator;
    numerator = temp + denominator;
    // std::cout << "\t[" << n << "] = " << numerator << "/" << denominator;
    if (numerator.num_digits() > denominator.num_digits()) {
      count++;
      // std::cout << " <--- " << std::endl;
    } 
    // else std::cout << std::endl;
  }

  std::cout << count << " terms in the first " << upper_limit 
            << " terms have more digits in the numerator" << std::endl;

  return 0;
}
