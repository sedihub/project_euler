/*
PROBLEM:
  All square roots are periodic when written as continued fractions and can be written in the 
  form:
      $$
        \sqrt{n} = a_{0} + \frac{1}{a_{1} + \frac{1}{a_{2} + \frac{1}{\cdots}}}
      $$
  
  For example, let us consider, \sqrt{23}:
      $$
        \sqrt{23} = 4 + (\sqrt{23} - 4)
                  = 4 + \frac{23 - 16}{\sqrt{23} + 4}
                  = 4 + \frac{7}{(7 + 1) + (\sqrt{23} - 4)}
                  = 4 + \frac{1}{1 + (\sqrt{23} - 3)}
                  = \cdots
      $$

  The process can be summarized as follows:

      a_0 = 4, \frac{1}{\sqrt{23} - 4}
      a_1 = 1, \frac{7}{\sqrt{23} - 3}
      a_2 = 3, \frac{2}{\sqrt{23} - 3}
      a_3 = 1, \frac{7}{\sqrt{23} - 4}  <----
      a_4 = 8, \frac{1}{\sqrt{23} - 4}      |
      a_4 = 1, \frac{7}{\sqrt{23} - 3}      |
      a_4 = 3, \frac{2}{\sqrt{23} - 3}      |
      a_7 = 1, \frac{7}{\sqrt{23} - 4}  <----

  It can be seen that the sequence is repeating. For conciseness, we use the notation:

      $$ \sqrt{23} = [4;(1318)] $$
    
  to indicate that the block (1,3,1,8) repeats indefinitely.

  Exactly four continued fractions, for $n \leq 13$, have an odd period.

  How many continued fractions for $n \leq 10,000$ have an odd period?


SOLUTION:
  First, we need an integer square-root function. 

  Some questions:

    - What does guarantee the periodicity of the sequence?
    - Why is that in the steps numbers are neatly divisible?

  We will keep track of a pair of numbers: numerator and the subtracted integer in the 
  denominator. When we reach a pair of the two are identical, we have found the period. 

  At each update step, we start with $\frac{n_i}{\sqrt{x} - d_i}$. We want to write it as
  $a_{i+1} + \frac{n_{i+1}}{\sqrt{x} - d_{i+1}}$. This is done using a little algebra:

      $$
        \frac{n_i}{\sqrt{x} - d_i} = \frac{n_i (\sqrt{x} + d_i)}{x - d_i^2}
                                   = \frac{n_i (d_i + d_0 + \sqrt{x} - d_0)}{x - d_i^2}
      $$ 
  Note that $d_0$ is the integer sqrt of $x$.

  ANSWER: 1322
**/

#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

typedef unsigned int uint;

// uint binary_length(uint n) 
// {
//   uint length = 1;
//   n >>= 1;
//   while (n > 0) {
//     length += 1;
//     n >>= 1;
//   }
//   return length;
// }


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


uint period(uint n)
{
  uint isqrt_n = uint_sqrt(n);

  // Define vectors for coefficients and the remainder pairs:
  std::vector<uint> a_vec;
  std::vector< std::array<uint, 2> > num_den_vec;

  // Initialize:
  a_vec.push_back(isqrt_n);
  num_den_vec.push_back(std::array<uint, 2>{1, isqrt_n});
  if (isqrt_n * isqrt_n == n) {  // It's a perfect square.
    return 0;
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
  //std::cout << a_n << ", " << r_n[0] << "/( sqrt{" << n << "} - " << r_n[1] << ")" << std::endl;
  while (it == num_den_vec.end()) {
    a_vec.push_back(a_n);
    num_den_vec.push_back(std::array<uint, 2>(r_n));
    r_n[0] = (n  - num_den_vec.back()[1] * num_den_vec.back()[1]) / num_den_vec.back()[0];
    a_n = (isqrt_n + num_den_vec.back()[1]) / r_n[0];
    r_n[1] = isqrt_n - (isqrt_n + num_den_vec.back()[1]) % r_n[0];
    it = std::find(num_den_vec.begin(), num_den_vec.end(), r_n); 
    //std::cout << a_n << ", " << r_n[0] << "/( sqrt{" << n << "} - " << r_n[1] << ")" << std::endl;
  }

  return (uint)std::distance(it, num_den_vec.end());
}


int main()
{
  /*
  // Check the examples:
  std::cout <<  2 << " --> " << period( 2) << std::endl;
  std::cout <<  3 << " --> " << period( 3) << std::endl;
  std::cout <<  5 << " --> " << period( 5) << std::endl;
  std::cout <<  6 << " --> " << period( 6) << std::endl;
  std::cout <<  7 << " --> " << period( 7) << std::endl;
  std::cout <<  8 << " --> " << period( 8) << std::endl;
  std::cout << 10 << " --> " << period(10) << std::endl;
  std::cout << 11 << " --> " << period(11) << std::endl;
  std::cout << 12 << " --> " << period(12) << std::endl;
  std::cout << 13 << " --> " << period(13) << std::endl;
  */

  const uint upper_limit = 10001;
  
  uint count = 0;
  for (uint n = 1; n < upper_limit; n++) {
    if (period(n) % 2 == 1) {
      count += 1;
    }
  }
  std::cout << count << " numbers have odd periods." <<  std::endl;

  return 0;
}
