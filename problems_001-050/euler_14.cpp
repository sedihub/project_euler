/*
PROBLEM:
  The following iterative sequence is defined for the set of positive integers:

      n --> n/2    (n is even)
      n --> 3n + 1   (n is odd)

  Using the rule above and starting with 13, we generate the following sequence:
      
      13 → 40 → 20 → 10 → 5 → 16 → 8 → 4 → 2 → 1

  It can be seen that this sequence (starting at 13 and finishing at 1) contains 
  10 terms. Although it has not been proved yet (Collatz Problem), it is thought 
  that all starting numbers finish at 1.

  Which starting number, under one million, produces the longest chain?


SOLUTION:
  The obvious solution is to use brute force. (We could make the brute force solution
  a bit more efficient by storing the numbers we have already visited.) 
  Follow-up: The plain brute force solution seems to be faster...

  Before diving into coding the solution, let's consider reversing the sequence:

    1 → 2 → 4 → 8 → 16 → 32 → 64 → 128 → 256 ...
             ↓
             5 → 10 → 20 →  40 →  80 ...
                ↓      ↓
                3 → 6 →   
  
  Computing this tree will be more expensive as it will likely grow O(2 ^ depth).

  Anyway, the answer is 837799 with the cycle length of 524.

  ANSWER: 837799
**/

#include <iostream>
#include <map>


/*
template <typename T>
class ComputeSequenceLength
{
public:

  T sequence_length(T n){
    T n_val = n;
    unsigned long long int counter = 0;
    while (n != 1){
      if(visited.find(n) != visited.end()){
        counter += visited[n];
        break;
      }
      //
      if(n % 2 == 0)
        n = n / 2;
      else
        n = 3 * n + 1;
      //
      counter++;
    }
    visited[n_val] = counter;

    return counter;
  }

private:
  std::map<T, T> visited;
};
*/

unsigned long long int sequence_length(unsigned long long int n)
{
  unsigned long long int counter = 0;
  while (n != 1) {
    if(n % 2 == 0)
      n = n / 2;
    else
      n = 3 * n + 1;
    //
    counter++;
  }

  return counter;
}


int main()
{
  typedef unsigned long long int ulli;
  const ulli upper_limit = 1000000;
  
  ulli n = 0;
  ulli longest_cycle = 0;
  ulli cycle_length;

  for (ulli i = 1; i < upper_limit; ++i) {
    cycle_length = sequence_length(i);
    if (cycle_length > longest_cycle) {
      longest_cycle = cycle_length;
      n = i;
    }
    std::cout << i << " ---> " << cycle_length << std::endl; 
  }

  std::cout << "\t" << n << " has the longest cycle (" << longest_cycle\
            << ") of all numbers  under " << upper_limit << std::endl;

  return 0;
}