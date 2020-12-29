/*
PROBLEM:
  Euler 69
  Find the value of n ≤ 1,000,000 for which n/φ(n) is a maximum.

SOLUTION:
  Observe the $\phi(n)$ can be obtained by decomposing $n$ into its prime factors:
        
        $\phi(n) = n (1 - \frac{1}{p_1}) \cdots (1 - \frac{1}{p_m})$ 

  We also note that to maximize the ratio, we want the least power, i.e., 1, for 
  each prime factor of $n$ as higher powers are "wasted" so to speak: The ratio remains
  the same while $n$ increases. We also note that prime n's result in ratios of the 
  form $\frac{p}{phi(p)} = \frac{p}{p - 1}$. The largest fraction is that of 2.
  

  Given these, the idea is to find the number with the largest number of prime factors
  that are as small as possible:

        $n = 2 x 3 x 5 x 7 ... <= 1,000,000$ 

  ANSWER: 510510 has the n/phi ration of 5.53939
**/

#include <iostream>
#include <map>


typedef unsigned long int ULInt;
typedef std::map<ULInt, ULInt> ULIntMap;

/*
// This solution was inefficient...
namespace Solution_1 {
  ULIntMap prime_decomposition(ULInt n)
  {
    ULInt i = 2;
    ULIntMap decomp;
    while (n > 1 && i <= n) {
      if (n % i == 0) {
        decomp[i] = 1;
        n /= i;
      }
      while (n % i == 0) {
        decomp[i] += 1;
        n /= i;
      }
      i++;
    }
    return decomp;
  }


  ULInt power(ULInt m, ULInt p)
  {
    if (p == 0) {
      return 1;
    }
    else {
      ULInt result = 1;
      while (p > 0) {
        result *= m;
        p--;
      }
      return result;
    }
  }


  ULInt euler_phi(ULInt n)
  {
    ULIntMap decom_n = prime_decomposition(n);
    ULInt phi = 1;
    for (ULIntMap::iterator mit = decom_n.begin(); mit != decom_n.end(); mit++) {
      phi *= power(mit->first, mit->second - 1) * (mit->first - 1);
    }
    return phi;
  }
};
*/


bool is_prime(ULInt n)
{
  if (n == 2) {return true;}
  else if (n == 3) {return true;}
  else if (n == 5) {return true;}
  else if (n % 2 == 0) {return false;}
  else if (n % 3 == 0) {return false;}

  ULInt k = 1;
  ULInt temp;
  while (36 * k * k + 12 * k + 1 < n) {
    temp = 6 * k + 1;
    if (n % temp == 0 || n % (temp+4) == 0) {
      return false;
    }
    k++;
  }

  return true;
}


int main()
{
  const ULInt MAX_N = 1000000;

  float ratio = 1.0;
  ULInt num = 1;
  ULInt n = 2;
  while (num * n <= MAX_N) {
    if (is_prime(n)) {
      num *= n;
      ratio *= (float)n / (float)(n - 1);
      // std::cout << "\t[" << n << "]\t" << num << " ---> " << ratio << std::endl; 
    }
    n++;
  }
  std::cout << "The number " << num << " has the n/phi ration of " << ratio << std::endl;

  return 0;
}
