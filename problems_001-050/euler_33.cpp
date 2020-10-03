/*
PROBLEM:
  The fraction 49/98 is a curious fraction, as an inexperienced mathematician in attempting to 
  simplify it may incorrectly believe that 49/98 = 4/8, which is correct, is obtained by 
  cancelling the 9s.

  We shall consider fractions like, 30/50 = 3/5, to be trivial examples.

  There are exactly four non-trivial examples of this type of fraction, less than one in value, 
  and containing two digits in the numerator and denominator.

  If the product of these four fractions is given in its lowest common terms, find the value of
  the denominator.


SOLUTION:
  

  ANSWER: 100
**/

#include <iostream>


unsigned int reduce_by_gcd(unsigned int &a , unsigned int &b)
{
  unsigned int gcd = 1;
  if (a % b == 0) {
    gcd = b;
    a /= b;
    b = 1;
    return gcd; 
  }
  if (b % a == 0) {
    gcd = a;
    b  /= a;
    a   = 1;
    return gcd;
  }

  unsigned int n = 2;
  unsigned int max;
  while (n < a && n < b) {
    while (a % n==0 && b % n==0) {
      a /= n;
      b /= n;
      gcd *= n;
    }
    n++;
  }
  return gcd;
}


int main()
{
  unsigned int prod_nums = 1;
  unsigned int prod_denums = 1;

  unsigned int a0, a1;
  unsigned int b0, b1;
  unsigned int num, den;
  for (unsigned int a = 10; a <= 99; a++) {
    for (unsigned int b = a+1; b <= 99; b++) {
      if (a % 10 == 0 && b % 10 ==0) continue;  // Trivial solution. 

      // Compute the digits:
      a0 = a % 10;
      a1 = a / 10;
      
      b0 = b % 10;
      b1 = b / 10;
      
      num = a;
      den = b;
      
      if (a0 == b0) {
        reduce_by_gcd(num, den);
        if (a1 > 1 && b1 > 1 ) reduce_by_gcd(a1, b1);
        if (num == a1 && den == b1) {
          std::cout << "\t" << a << " / " << b   << "  =  "
                << num << " / " << den << std::endl; 
          prod_nums *= num;
          prod_denums *= den;
        }
      }
      else if (a0 == b1) {
        reduce_by_gcd(num, den);
        if (a1 > 1 && b0 > 1) reduce_by_gcd(a1, b0); 
        if (num == a1 && den == b0){
          std::cout << "\t" << a << " / " << b   << "  =  "
                << num << " / " << den << std::endl; 
          prod_nums *= num;
          prod_denums *= den;
        }
      }
      else if (a1 == b0) {
        reduce_by_gcd(num , den);
        if (a0 > 1 && b1 > 1) reduce_by_gcd(a0, b1);
        if (num == a0 && den == b1) {
          std::cout << "\t" << a << " / " << b   << "  =  "
                << num << " / " << den << std::endl; 
          prod_nums *= num;
          prod_denums *= den;
        }
      }
      else if (a1 == b1) {
        reduce_by_gcd(num, den);
        if (a0 > 1 && b0 > 1) reduce_by_gcd(a0, b0);
        if (num == a0 && den == b0) {
          std::cout << "\t" << a << " / " << b   << "  =  "
                << num << " / " << den << std::endl; 
          prod_nums *= num;
          prod_denums *= den;
        }
      }
    }
  }

  std::cout << "The product: " << prod_nums << " / " << prod_denums << "  =  ";
  reduce_by_gcd(prod_nums, prod_denums);
  std::cout << prod_nums << " / " << prod_denums << std::endl;
  
  return 0;
}
