/*
PROBLEM:
  Euler 85
  By counting carefully it can be seen that a rectangular grid measuring 3 by 2 contains 
  eighteen rectangles:

            [Example image](https://projecteuler.net/project/images/p085.png)

  Although there exists no rectangular grid that contains exactly two million rectangles,
  find the area of the grid with the nearest solution.


SOLUTION:
  This is a combinatorics problem: One can show that the number of rectangles contained in
  an m-by-n grid is given by:

        $ \frac{m (m + 1)}{2} \frac{n (n + 1)}{2} $   

  which is obtained by multiplying the number of segments within each dimension of the 
  grid. Note that for m segments there are (m + 1) points.

  Now, all we need is to find a pair (m, n) for which the above expression is as close to
  2x10^6 as possible. 

  To find the closest grid dimensions pair with the number of rectangles closest to the 
  target value, we start from the target, choose a reasonable range of values for m and n,
  and search for a match.


  ANSWER: 2772 (m = 77, n = 36 ---> 1999998)
**/

#include <iostream>


typedef unsigned long int ULInt;


inline ULInt num_rects(ULInt m, ULInt n)
{
  return (m * (m + 1) / 2) * (n * (n + 1) / 2);
}


int main()
{
  const ULInt TARGET = 2000000;

  ULInt temp, m_prod, n_prod;
  for (ULInt d = 0; d < TARGET; d++) {
    // Search smaller values:
    for (ULInt m = 10; m < 100; m++) {
      temp = TARGET - d;
      m_prod = (m * (m + 1)) / 2;
      if (temp % m_prod != 0) { continue; }
      temp /= m_prod;
      for (ULInt n = 10; n <= m; n++) {
        n_prod = (n * (n + 1)) / 2;
        if (temp == n_prod) {
          std::cout << m * n << " (" << m << ", " << n 
                    << " ---> " << num_rects(m, n) << ")" << std::endl;
          goto TERMINATE_SEARCH;
        }
      }
    }
    //
    // Search larger values:
    for (ULInt m = 10; m < 100; m++) {
      temp = TARGET + d;
      m_prod = (m * (m + 1)) / 2;
      if (temp % m_prod != 0) { continue; }
      temp /= m_prod;
      for (ULInt n = 10; n <= m; n++) {
        n_prod = (n * (n + 1)) / 2;
        if (temp == n_prod) {
          std::cout << m * n << " (" << m << ", " << n 
                    << " ---> " << num_rects(m, n) << ")" << std::endl;
          goto TERMINATE_SEARCH;
        }
      }
    }
  }
  TERMINATE_SEARCH:;


  return 0;
}
