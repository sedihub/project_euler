/*
PROBLEM:
  The 5-digit number, 16807=7^5, is also a fifth power. Similarly, the 9-digit number, 
  134217728=8^9, is a ninth power.

  How many n-digit positive integers exist which are also an nth power?


SOLUTION:
  For this, we can use `double` representation. First, let's reduce the search space.
   - We want $10^{n-1} \leq m^n \le 10^{n}$. Thus, $(n-1) \leq n\log_{10}(m) \le n$. Now, let's 
     consider various values for m and n:

        m = 1  -->  log(1) = 0            -->  n = 1
        m = 2  -->  log(2) ~ 0.30103      -->  n = 1
        m = 3  -->  log(3) ~ 0.47712125   -->  n = 1
        m = 4  -->  log(4) ~ 0.60205999   -->  n = 1, 2 
        m = 5  -->  log(5) ~ 0.69897000   -->  n = 1, 2, 3
        m = 6  -->  log(6) ~ 0.77815125   -->  n = 1, ... 4
        m = 7  -->  log(7) ~ 0.845098     -->  n = 1, ... 6
        m = 8  -->  log(8) ~ 0.90308999   -->  n = 1, ... 10
        m = 9  -->  log(9) ~ 0.95424251   -->  n = 1, ... 21

     This is, in fact, the solution. Let's verify this programmatically...

  ANSWER: 49 = (1 + 1 + 1+ 2 + 3 + 4 + 6 + 10 + 21)  
**/

#include <iostream>
#include <set>


unsigned int number_of_digits(double n)
{
  unsigned int count = 0;
  while (n >= 1) {
    count++;
    n /= 10.;
  }
  return count;   
}


double pow(double n, unsigned long int p)
{
  if (p == 0) return 1;
  if (p == 1) return n;
  
  unsigned long int temp = n;
  while (p > 1) {
    n *= temp;
    p--;
  }

  return n;
}


int main()
{
  std::set<double> set_of_solutions; 
  double x;
  unsigned int p;
  for (double n = 1.0; n < 10.0; n += 1.0) {
    p = 1;
    x = pow(n, p);
    while (x >= pow(10, p-1)) {
      if (number_of_digits(x) == p) { 
        std::cout << "\t" << n << "^" << p << " = " << x 
                  << " [" << number_of_digits(x) << " digits]" << std::endl; 
        set_of_solutions.insert(x); 
      }
      p++;
      x = pow(n, p);
    }
  }
   
  std::cout << "Number of solutions: " << set_of_solutions.size() << std::endl;
  
  return 0;
}