/*
PROBLEM:
  A googol (10^100) is a massive number: one followed by one-hundred zeros; 100^100 is almost
  unimaginably large: one followed by two-hundred zeros. Despite their size, the sum of the digits
  in each number is only 1.

  Considering natural numbers of the form, a^b, where a, b < 100, what is the maximum digital sum?


SOLUTION:
  Brute-force solution, that's not too brute-force ;)

  ANSWER: 972 for 99 ^ 95.
**/

#include <iostream>
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
  // // Test LargeUInt 
  // LargeUInt n(9168234);
  // LargeUInt m(13479845);
  // std::cout << n << " has " << n.num_digits() << " digits." << std::endl;
  // std::cout << "Sum of " << n << " digits is: " << n.sum_digits() << std::endl;
  // std::cout << n << " + " << m << " = " << (n + m)  << std::endl;
  // std::cout << n << " * " << m << " = " << (n * m)  << std::endl;
  // std::cout << m << " * " << n << " = " << (m * n)  << std::endl;
  // std::cout << n << " ^ " << 3 << " = "  << (n ^ 3)  << std::endl;

  unsigned int digits_sum, max_digits_sum;
  unsigned long int a_max, b_max;
  max_digits_sum = 0;
  for (unsigned long int a = 1; a < 100; a++) {
    if (a % 10 == 0) continue;
    LargeUInt n(a);
    LargeUInt p(a);
    for (unsigned long int b = 2; b < 100; b++) {
      p = p * a;
      digits_sum = p.sum_digits();
      if (digits_sum > max_digits_sum) {
        a_max = a;
        b_max = b;
        max_digits_sum = digits_sum;
      }
    }
  }

  std::cout << "Largest digit sum is " << max_digits_sum 
            << " for " << a_max << " ^ " << b_max << std::endl;

  return 0;
}
