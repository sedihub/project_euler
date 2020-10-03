/*
PROBLEM:
  Take the number 192 and multiply it by each of 1, 2, and 3:

          192 × 1 = 192
          192 × 2 = 384
          192 × 3 = 576

  By concatenating each product we get the 1 to 9 pandigital, 192384576. We will call 192384576 
  the concatenated product of 192 and (1,2,3)

  The same can be achieved by starting with 9 and multiplying by 1, 2, 3, 4, and 5, giving the 
  pandigital, 918273645, which is the concatenated product of 9 and (1,2,3,4,5).

  What is the largest 1 to 9 pandigital 9-digit number that can be formed as the concatenated 
  product of an integer with (1,2, ... , n) where n > 1?


SOLUTION:
  This problem can be solved using brute force. It is perhaps possible to shrink the search space
  a bit more, but given that the brute-force solution is already quite fast (~110 ms) I skip that. 

  ANSWER: 932718654 corresponding to 9327

**/


#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>


typedef unsigned int uint;


namespace solution1 {
  bool is_pandigital(std::vector<uint> prod)
  {
    if(prod.size() != 9)
      return false;

    std::sort(prod.begin(), prod.end());
    for (uint i = 0; i < 9; i++) {
      if(prod[i] != (i + 1)) 
        return false;
    }

    return true;
  }


  void append_to_vec(uint num, std::vector<uint> &vec)
  {
    uint digit_count = 0;
    while (num > 0) {
      vec.push_back(num % 10);
      num /= 10;
      digit_count++;
    }
    std::reverse(vec.end() - digit_count, vec.end());
  }


  bool pandigital_product(uint num, std::vector<uint> &prod_vec)
  /* If can form a pandigital product, will return true and assigns it to `prod_vec`
  **/
  {
    uint n = 1;
    prod_vec.clear();
    while (prod_vec.size() < 9) {
      append_to_vec(n * num, prod_vec);
      n++;
    }

    return is_pandigital(prod_vec);
  }


  std::vector<uint> largest_pandigital_product(uint &num)
  /* Will use the built-in lexicographic order for std::vec;
  **/
  {
    std::vector<uint> largest_pandigital, pandigital;
    for (uint base = 1; base < 100000; base++) {
      if (pandigital_product(base, pandigital)){
        if (pandigital > largest_pandigital) {
          largest_pandigital = pandigital;
          num = base;
        }
      }
    }
    return largest_pandigital;
  }
}

 
int main()
{
  uint base;
  std::vector<uint> max_pandigital = solution1::largest_pandigital_product(base);
  std::cout << "Largest pandigital product: [" << base << "]: ";
  for (std::vector<uint>::iterator it = max_pandigital.begin(); it != max_pandigital.end(); it++) {
    std::cout << *it;
  }
  std::cout << std::endl;

  return 0;
}
