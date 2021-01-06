/* 
PROBLEM:
  Euler 86
  A spider, S, sits in one corner of a cuboid room, measuring 6 by 5 by 3, and a fly, F, 
  sits in the opposite corner. By traveling on the surfaces of the room the shortest 
  "straight line" distance from S to F is 10 and the path is shown on the diagram.

            [086 IMAGE](https://projecteuler.net/project/images/p086.png)

  However, there are up to three "shortest" path candidates for any given cuboid and the 
  shortest route doesn't always have integer length.

  It can be shown that there are exactly 2060 distinct cuboid, ignoring rotations, with 
  integer dimensions, up to a maximum size of M by M by M, for which the shortest route 
  has integer length when M = 100. This is the least value of M for which the number of 
  solutions first exceeds two thousand; the number of solutions when M = 99 is 1975.

  Find the least value of M such that the number of solutions first exceeds one million.


SOLUTION:
  The shortest length candidates for a cuboid of width $w$, depth $d$ and height $h$ are 
  given by:

        $ l_w = \sqrt{w^2 + (h + d)^2} $
        $ l_d = \sqrt{h^2 + (w + h)^2} $
        $ l_h = \sqrt{h^2 + (w + d)^2} $

  Assuming the $w \geq d \geq h$, it is clear that the shortest of these is $l_w$. Thus,
  we need to count Pythagorean triples (recall that we dismiss rotations using the assumed
  ordering of $w$, $d$ and $h$).

  We want to count the integer-length $l$'s for $h \leq d \leq w \leq M$, with all lengths
  being integer. Thus, we seek solutions of,

        $ l^2 = w^2 + s^2$
  
  where, $s \leq 2w$. Given a solution pair $(w, s)$, there will be $floor(s / 2)$ solutions.
  Here is why: $s$ is the sum of $h$ and $d$. Since $h \leq d$, $h$ can take values in the 
  range ${1, 2, ..., floor(s / 2)}$. 

  The simplicity of the above expression piqued my curiosity: I thought there should be a more
  straightforward derivation. Lo and behold, I found the following interesting and more elegant
  derivation on Mathematics Stack Exchange:
  [Minimum distance to reach opposite corner](
  https://math.stackexchange.com/questions/1189743/minimum-distance-to-reach-opposite-corner)

  It only remains to generate pairs of $w$ and $s$, which can be generated using Pythagorean
  triples' formula:

        $ l = k(a^2 + b^2),  w = k(a^2 - b^2), s = 2kab $

  where, $a > b$ and are co-prime and are not both odd. We can ignore k and find all primitive
  solutions. Then factor in k.

  The main strategy is to find the update the number of solutions for cuboids of dimensions 
  less then or equal $M - 1$ by including the number of solutions for the case where $w = M$
  and $h \leq d \leq M$. The number of solutions for $M = 1$ is zero.


  ANSWER: There are 1000457 solutions for M = 1818.
 **/

#include <iostream>
#include <vector>
#include <utility>
#include <iterator>
#include <iomanip>

typedef unsigned long int ULInt;
typedef std::pair<ULInt, ULInt> ULIntPair;

ULInt gcd(ULInt a, ULInt b)
{  
  if (a == 0) {
    return b;
  }
  else if (b == 0) {
    return a;
  }
  else if (a == b) {
    return a;
  }

  if (a > b) {
    return gcd(a - b, b);
  }
  else {
    return gcd(a, b - a);
  }
}


std::vector<ULIntPair> primitive_pythogorean_triples(ULInt max_n)
{
  std::vector<ULIntPair> primitive_triples;

  ULInt a, b;
  for (ULInt m = 1; m * m <= max_n; m++) {
    for (ULInt n = 1; n < m; n++) {
      if (m % 2 == n % 2 || gcd(m, n) != 1) { continue; }
      else {
        a = m * m - n * n;
        b = 2 * m * n;
        if (a > b) { 
          primitive_triples.push_back(ULIntPair(a, b)); 
        }
        else { 
          primitive_triples.push_back(ULIntPair(b, a));
        }
      }
    }
  }

  return primitive_triples;
}


inline ULInt num_cuboids(ULInt s, ULInt w) 
/* s is the sum of height and depth of the cuboid.
   w is the width and we assume that width >= height >= depth
**/
{
  if (s <= w) {
    return s / 2;
  }
  else {
    // For example, if s = 105 and w = 100, h cannot be {1, 2, 3, 4} for which d > 100!
    return s / 2 - (s - w) + 1; 
  }
}


int main()
{
  const ULInt SUM_MAX = 1000000;  // 2000;

  std::vector<ULIntPair> primitve_triples;
  primitve_triples = primitive_pythogorean_triples(5000); // An educated guess for max m!

  ULInt w, sum, num_solutions, k;
  std::vector<ULIntPair>::iterator it;
  sum = 0;
  num_solutions = 0; 
  w = 0;
  while (sum < SUM_MAX) {            
    w++;
    //
    num_solutions = 0;
    for (it = primitve_triples.begin(); it != primitve_triples.end(); it++) {
      // I don't have to worry about double counting as a != b for Pythagorean triples. 
      k = (w / it->first);
      if (w % it->first == 0  && k * it->second <= 2 * w) {
        num_solutions += num_cuboids(k * it->second, w);
      }
      //
      k = (w / it->second);
      if (w % it->second == 0  && k * it->first <= 2 * w) {
        num_solutions += num_cuboids(k * it->first, w);
      }
    }
    // std::cout << "\t" << std::setw(4) << w << ": " << std::setw(7) 
    //           << num_solutions << std::endl; 
    sum += num_solutions;
  }

  std::cout << "There are " << sum << " solutions for M = "
            << w << "." << std::endl;

  return 0;
}
