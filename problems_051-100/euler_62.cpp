/*
PROBLEM:
  The cube, 41063625 (345^3), can be permuted to produce two other cubes: 56623104 (384^3) 
  and 66430125 (4053). In fact, 41063625 is the smallest cube which has exactly three 
  permutations of its digits which are also cube.

  Find the smallest cube for which exactly five permutations of its digits are cube.

SOLUTION:

  ANSWER: 127035954683  (5027  7061  7202  8288  8384)
**/

#include <iostream>
#include <map>
#include <vector>
#include <iterator>


void ulint_to_char_vec(unsigned long int n, std::vector<char> &vec)
{
  vec.clear();
  while (n > 0) {
    vec.push_back('0' + (char)(n % 10));
    n /= 10;
  }
  std::sort(vec.begin(),vec.end());
} 


int main()
{
  const unsigned int num_cubic_perms = 5;

  std::map<std::vector<char>, std::vector<unsigned long int> >  map;
  std::vector<char> char_vec;
  std::vector<unsigned long int> vec;

  unsigned long int n = 5;
  unsigned long int n_cubed;
  unsigned int current_length;
  std::vector<unsigned long int>::iterator it;
  std::map< std::vector<char> , std::vector<unsigned long int> >::iterator mit;
  while (true) {
    n_cubed = n * n * n;
    ulint_to_char_vec(n_cubed, char_vec);
    mit = map.find(char_vec);
    if (mit == map.end()) {
      map[char_vec] = vec;
      map[char_vec].push_back(n); 
    }
    else {
      (mit->second).push_back(n);
      if (mit->second.size() == num_cubic_perms) {
        for (it = (mit->second).begin(); it != (mit->second).end(); it++) {
          std::cout << *it << "\t";
        }
        std::cout << std::endl;
        unsigned long int num = (*((mit->second).begin()));
        unsigned long int answer = num * num * num;
        std::cout << "Answer: " << answer << std::endl;
        goto FOUND;
      }
    }
    n++;
  }
  FOUND:;
  
  return 0;
}