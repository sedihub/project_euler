/*
PROBLEM:
  The nth term of the sequence of triangle numbers is given by, tn = ½n(n+1); so the first ten 
  triangle numbers are:

          1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...

  By converting each letter in a word to a number corresponding to its alphabetical position and
  adding these values we form a word value. For example, the word value for SKY is 19 + 11 + 25 = 
  55 = t10. If the word value is a triangle number then we shall call the word a triangle word.

  Using words.txt (right click and 'Save Link/Target As...'), a 16K text file containing nearly 
  two-thousand common English words, how many are triangle words?


SOLUTION:
  Parse the names, compile ord scores, and check triangularity. I am using `sqrt` function. This
  is probably not the most efficient way.

  ANSWER: 162
**/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <iomanip>
#include <math.h>


unsigned int sum_char_values(std::string str)
{
  unsigned int sum = 0;
  for (unsigned int i = 0 ; i < str.size(); i++) {
    sum += (unsigned int)(str[i] - 'A' + 1);
  }
  return sum; 
}


inline bool is_whole_number( double x )
{
  if (floor(x) == x) 
    return true;
  else
    return false;
}


bool is_triangle(unsigned int &n)
{
  double y = n;
  double x = 0.5 * (sqrt(1 + 8 * y) - 1);

  if (x > 0 && is_whole_number(x))
    return true;
  else
    return false;
}



int main() 
{ 
  // // See if it works correctly on the example:
  // std::cout << "SKY" << " --> " << sum_char_values("SKY") << " --> " 
  //           << is_triangle(sum_char_values("SKY")) << std::endl;

  std::vector<std::string> list;
  std::ifstream file("./p042_words.txt");
  std::string str; 
  while (std::getline(file, str, ',')) {
    str = str.substr (1, (str.size() - 2));  // remove `"' 
    list.push_back(str);
    // std::cout << "\t" << str << std::endl;
  }

  unsigned int count=0;
  unsigned int val;
  std::vector<std::string>::iterator it;
  for (it = list.begin(); it != list.end(); it++) {
    val = sum_char_values(*it);
  	if (is_triangle(val)) { 
      count++;
      std::cout << "\t" << std::setw(16) << *it << "\t" << val << std::endl; 
    }
  }

  std::cout << "---------------------" << std::endl;
  std::cout << count << std::endl;
  return 0;
}
