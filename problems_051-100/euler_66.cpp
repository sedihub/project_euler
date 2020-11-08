/*
PROBLEM:
  Consider quadratic Diophantine equations of the form:

      $$
        x^2 - Dy^2 = 1 
      $$
  
  For example, when D=13, the minimal solution in x is 649^2 – 13×180^2 = 1.

  It can be assumed that there are no solutions in positive integers when D is square.

  By finding minimal solutions in x for D = {2, 3, 5, 6, 7}, we obtain the following:

      3^2 – 2×2^2 = 1
      2^2 – 3×1^2 = 1
     *9*^2 – 5×4^2 = 1   <---
      5^2 – 6×2^2 = 1
      8^2 – 7×3^2 = 1

  Hence, by considering minimal solutions in x for D <= 7, the largest x is obtained when D = 5.

  Find the value of D <= 1000 in minimal solutions of x for which the largest value of x 
  is obtained.


SOLUTION:
  We can rewrite the equation as:

      (x + 1)(x - 1) = Dy^2

  Seeking a brute-force solution from here on, but that did not work! That approach is highly
  inefficient. Retaining all the visited squares in a `std::map` did not help either...

  See [Pell's equation](https://mathworld.wolfram.com/PellEquation.html) descriptions on the
  MathWorld website.

  ANSWER: 661
  16421658242965910275055840472270471049^2 - 661 * 638728478116949861246791167518480580^2
**/


#include <iostream>
#include <map>
#include <vector>
#include <array>
#include <algorithm>
#include <iterator>


typedef unsigned int uint;


class LargeUInt
{
public:
  LargeUInt()
  {
    vec.clear();
  }

  LargeUInt(uint n)
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
  friend bool operator==(const LargeUInt &lhs, const LargeUInt &rhs);
  friend bool operator<(const LargeUInt &lhs, const LargeUInt &rhs);
  friend bool operator>(const LargeUInt &lhs, const LargeUInt &rhs);

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

  LargeUInt operator+(const uint &n)
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

  LargeUInt operator*(const uint &n)
  {
    LargeUInt temp = LargeUInt(n);
    return (*this) * temp;
  }

  LargeUInt operator^(const uint &n)
  {
    if (n == 0) {
      return LargeUInt(1);
    }
    else if (n == 1) {
      return *this;
    }
    else {
      uint count = 0; 
      LargeUInt p(1);
      while (count != n) {
        p = p * *this;
        count += 1;
      }
      return p;
    }
  }

protected:
  void reverse_digits()
  {
    std::reverse(vec.begin(),vec.end());
    std::vector<char>::iterator it = vec.begin();
    while (*it == '0') {
      vec.erase(it);
      it = vec.begin();
    }
  }

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


bool operator==(const LargeUInt &lhs, const LargeUInt &rhs) 
{
  return (lhs.vec == rhs.vec);
}


bool operator<(const LargeUInt &lhs, const LargeUInt &rhs) 
{
  if (lhs.vec.size() == rhs.vec.size()) {
    for (uint n = lhs.vec.size(); n > 0; n--) {
      if (lhs.vec[n-1] == rhs.vec[n-1]) continue;
      else {
        return (lhs.vec[n-1] < rhs.vec[n-1]);
      }
    }
  }
  else {
    return (lhs.vec.size() < rhs.vec.size());
  }
  return false;
}


bool operator>(const LargeUInt &lhs, const LargeUInt &rhs) 
{
  if (lhs.vec.size() == rhs.vec.size()) {
    for (uint n = lhs.vec.size(); n > 0; n--) {
      if (lhs.vec[n-1] == rhs.vec[n-1]) continue;
      else {
        return (lhs.vec[n-1] > rhs.vec[n-1]);
      }
    }
  }
  else {
    return (lhs.vec.size() > rhs.vec.size());
  }
  return false;
}


uint uint_sqrt(uint n)
{
  if (n == 0) {
    return 0;
  }
  else if (n < 4) {
    return 1;
  }
  uint cand_0, cand_1;
  cand_0 = uint_sqrt(n >> 2) << 1;
  cand_1 = cand_0 + 1;

  if (cand_1 * cand_1 > n) return cand_0;
  else return cand_1;
}


void continued_fraction_sqrt(uint n, uint &period, std::vector<uint> &a_vec)
{
  uint isqrt_n = uint_sqrt(n);

  // Define vectors for coefficients and the remainder pairs:
  std::vector< std::array<uint, 2> > num_den_vec;

  // Initialize:
  a_vec.push_back(isqrt_n);
  num_den_vec.push_back(std::array<uint, 2>{1, isqrt_n});
  if (isqrt_n * isqrt_n == n) {  // It's a perfect square.
    period = 0;
    return;
  }

  // Stop when period is found:
  std::vector< std::array<uint, 2> >::iterator it;
  uint a_n;
  std::array<uint, 2> r_n;
  //
  r_n[0] = (n  - num_den_vec.back()[1] * num_den_vec.back()[1]) / num_den_vec.back()[0];
  a_n = (isqrt_n + num_den_vec.back()[1]) / r_n[0];
  r_n[1] = isqrt_n - (isqrt_n + num_den_vec.back()[1]) % r_n[0];
  it = std::find(num_den_vec.begin(), num_den_vec.end(), r_n);
  // std::cout << a_n << ", " << r_n[0] << "/( sqrt{" << n << "} - " << r_n[1] << ")" << std::endl;
  while (it == num_den_vec.end()) {
    a_vec.push_back(a_n);
    num_den_vec.push_back(std::array<uint, 2>(r_n));
    r_n[0] = (n  - num_den_vec.back()[1] * num_den_vec.back()[1]) / num_den_vec.back()[0];
    a_n = (isqrt_n + num_den_vec.back()[1]) / r_n[0];
    r_n[1] = isqrt_n - (isqrt_n + num_den_vec.back()[1]) % r_n[0];
    it = std::find(num_den_vec.begin(), num_den_vec.end(), r_n); 
    // std::cout << a_n << ", " << r_n[0] << "/( sqrt{" << n << "} - " << r_n[1] << ")" << std::endl;
  }
  a_vec.push_back(a_n);

  period = (uint)std::distance(it, num_den_vec.end());
  return;
}


bool is_solution(LargeUInt x, LargeUInt y, uint d) {
  LargeUInt x2 = x^2;
  LargeUInt dy2p1 = LargeUInt(d) * (y^2) + LargeUInt(1);
  if (x2 == dy2p1) {
    // std::cout << x << "^2 = " << x2 << ",\t" << d << " * " 
    //           << y << "^2 + 1 = " << dy2p1 << std::endl;
    return true;
  }
  else {
    return false;
  }
}


int main()
{  
  const uint UPPER_LIMIT = 1000;
  const bool VERBOSE = !false;

  std::vector<uint> coefficients;
  std::vector<uint>::iterator it;
  uint period;
  uint max_d = 1;
  uint n, n_folded;
  LargeUInt x = LargeUInt(1);
  LargeUInt y;
  LargeUInt p_n, p_nm1, p_nm2;  // p_n, p_{n-1}, p_{n-2}
  LargeUInt q_n, q_nm1, q_nm2;  // q_n, q_{n-1}, q_{n-2}
  for (uint d = 1; d <= UPPER_LIMIT; d++) {
    coefficients.clear();
    continued_fraction_sqrt(d, period, coefficients);
    if (period == 0) continue;
    if (VERBOSE) {
      std::cout << std::endl << d << " = [";
      for (it = coefficients.begin(); it != coefficients.end(); it++) {
        std::cout << " " << *it;
      }
      std::cout << "]" << " (Period: " << period << ")" << std::endl;
    }
    //
    p_nm2 = LargeUInt(coefficients[0]);
    q_nm2 = LargeUInt(1);
    if (VERBOSE) std::cout << "\t[" << d << "]_" << 0 << " = " << p_nm2 <<  " / " << q_nm2 << std::endl;
    if (is_solution(p_nm2, q_nm2, d)) {
      if (p_nm2 > x) {
        x = p_nm2;
        y = q_nm2;
        max_d = d;
      }
      continue;
    }
    p_nm1 = LargeUInt(1 + coefficients[0] * coefficients[1]);
    q_nm1 = LargeUInt(coefficients[1]);
    if (VERBOSE) std::cout << "\t[" << d << "]_" << 1 << " = " << p_nm1 <<  " / " << q_nm1 << std::endl;
    if (is_solution(p_nm1, q_nm1, d)) {
      if (p_nm1 > x) {
        x = p_nm1;
        y = q_nm1;
        max_d = d;
      }
      continue;
    }
    n = 2;
    n_folded = 1 + (n - 1) % period;
    p_n = LargeUInt(coefficients[n_folded]) * p_nm1 + p_nm2;
    q_n = LargeUInt(coefficients[n_folded]) * q_nm1 + q_nm2;
    if (VERBOSE) std::cout << "\t[" << d << "]_" << n << " = " << p_n <<  " / " << q_n << std::endl;
    p_nm2 = p_nm1;
    p_nm1 = p_n;
    q_nm2 = q_nm1;
    q_nm1 = q_n;
    n++;
    while (!is_solution(p_n, q_n, d)) {
      n_folded = 1 + (n - 1) % period;
      p_n = LargeUInt(coefficients[n_folded]) * p_nm1 + p_nm2;
      q_n = LargeUInt(coefficients[n_folded]) * q_nm1 + q_nm2;
      if (VERBOSE) std::cout << "\t[" << d << "]_" << n << " = " << p_n <<  " / " << q_n << std::endl;
      p_nm2 = p_nm1;
      p_nm1 = p_n;
      q_nm2 = q_nm1;
      q_nm1 = q_n;
      n++;
    }
    if (p_n > x) {
        x = p_n;
        y = q_n;
        max_d = d;
    }
    continue;
  }

  std::cout << std::endl << "----------------------------------" << std::endl;
  std::cout << x << "^2 - " << max_d << " * " << y << "^2" << std::endl;

  return 0;
}
