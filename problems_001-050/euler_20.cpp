/*
PROBLEM:
  Find the sum of the digits in the number 100!  


SOLUTION:
  Let's do this!
  

  ANSWER: 648
    100! = 93326215443944152681699238856266700490715968264381621468592963895217599
           99322991560894146397615651828625369792082722375825118521091686400000000
           0000000000000000
    Sum of digits: 648
**/

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>


typedef unsigned short int usi;


void print_vector(std::vector<usi> &vec)
{
  std::vector<usi>::iterator it;
  for (it = vec.begin(); it != vec.end(); ++it)
    std::cout << *it;

  return;
}


std::vector<usi> multiply (std::vector<usi> &a , std::vector<usi> &b)
{
  // Construct a vector to hold the result:
  std::vector<usi> result;
  for (usi n = 1 ; n <= (a.size()) + (b.size()) + 1 ; n++)
    result.push_back(0);
  
  // Carryout the multiplication:
  usi carry_over, temp_value;
  usi a_idx, b_idx, idx;
  a_idx = 0;
  for (std::vector<usi>::reverse_iterator ait = a.rbegin() ; ait != a.rend() ; ++ait) {
    carry_over = 0;
    b_idx = 0;
    for (std::vector<usi>::reverse_iterator bit = b.rbegin() ; bit != b.rend() ; ++bit) {
      idx = a_idx + b_idx;
      temp_value = result[idx] + (*ait) * (*bit) + carry_over; 
      result[idx] = temp_value % 10;
      carry_over = temp_value / 10;
      b_idx++;
    } 
    while (carry_over != 0) {
      idx++;
      result[idx] = (carry_over % 10);
      carry_over /= 10;
    }
    a_idx++;
  }
  
  // Remove left zeros:
  std::vector<usi>::reverse_iterator rit = result.rbegin();
  idx = 0;
  while (*rit == 0) {
    idx++;
    ++rit;
  }
  result.erase((result.end() - idx), result.end());

  // Reverse the vector:
  std::reverse(result.begin(), result.end());
  
  // // Uncomment to see what is happening...
  // print_vector(a);
  // std::cout << " x ";
  // print_vector(b);
  // std::cout << " = ";
  // print_vector(result);
  // std::cout << std::endl << std::endl;

  return result;
}


int main()
{
  const usi n = 100;
  std::vector<usi> vec;
  vec.push_back(1);

  std::vector<usi> temp_vec;
  usi temp;
  for (usi i = 1 ; i <= n ; ++i) {
    temp = i;
    temp_vec.clear();
    while (temp != 0){
      temp_vec.push_back(temp % 10);
      temp /= 10;
    }
    std::reverse(temp_vec.begin(), temp_vec.end());
    vec = multiply(temp_vec, vec);
  }
  
  usi sum_digits = 0;
  std::cout << n << "! = ";
  for (std::vector<usi>::iterator it = vec.begin() ; it != vec.end() ; it++)
  {
    std::cout << *it;
    sum_digits += *it;
  }
  std::cout << std::endl;
  std::cout << "Sum of digits: " << sum_digits << std::endl;
  
  return 0;
}
