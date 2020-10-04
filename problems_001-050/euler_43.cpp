/*
PROBLEM:
  The number, 1406357289, is a 0 to 9 pandigital number because it is made up of each of the digits
  0 to 9 in some order, but it also has a rather interesting sub-string divisibility property.

  Let d1 be the 1st digit, d2 be the 2nd digit, and so on. In this way, we note the following:

        d2d3d4=406 is divisible by 2
        d3d4d5=063 is divisible by 3
        d4d5d6=635 is divisible by 5
        d5d6d7=357 is divisible by 7
        d6d7d8=572 is divisible by 11
        d7d8d9=728 is divisible by 13
        d8d9d10=289 is divisible by 17

  Find the sum of all 0 to 9 pandigital numbers with this property.


SOLUTION: 
  Let's generate them!

  ANSWER: 16695334890
          =    1406357289
            +  1430952867
            +  1460357289
            +  4106357289
            +  4130952867
            +  4160357289
**/

#include <iostream>
#include <algorithm>
#include <vector>


typedef unsigned short int us;


inline bool divisible_by_three(us a, us b, us c)
{
  us temp = a + b + c;
  return (temp % 3 == 0);
}

inline bool divisible_by_n(us a, us b, us c, us n)
{
  us temp = 100 * a + 10 * b + c;
  return (temp % n == 0);
}


void generate_09_pandigitals_w_constraints(
  std::vector< std::vector<us> > &pandigitals, 
  us length=10,
  us step_number=0)
/* Recursively generates pandigitals of all length (max is obviously 9).
**/
{
  if(step_number == length) {
    return;
  }
  else if (step_number == 0){
    pandigitals.clear();
    for (us n = 1; n < length; n++){
      pandigitals.push_back(
        std::vector<us>{n}
      );
    }
    generate_09_pandigitals_w_constraints(pandigitals, length, ++step_number);
  }
  else {
    unsigned int current_step_idx = 0;
    std::vector< std::vector<us> > current_step = {};
    std::vector< std::vector<us> >::iterator it;
    for (it = pandigitals.begin(); it != pandigitals.end(); it++) {
      for (us n = 0; n < length; n++) {
        if (std::find(it->begin(), it->end(), n) != it->end())
          continue;
        if (step_number == 3 && (n % 2) != 0)
          continue;
        else if (step_number == 4 && !divisible_by_three((*it)[2], (*it)[3], n))
          continue;
        else if (step_number == 5 && n != 5 && n != 0)
          continue;
        else if (step_number == 6 && !divisible_by_n((*it)[4], (*it)[5], n, 7))
          continue;
        else if (step_number == 7 && !divisible_by_n((*it)[5], (*it)[6], n, 11))
          continue;
        else if (step_number == 8 && !divisible_by_n((*it)[6], (*it)[7], n, 13))
          continue;
        else if (step_number == 9 && !divisible_by_n((*it)[7], (*it)[8], n, 17))
          continue;
        current_step.push_back(std::vector<us>());
        current_step[current_step_idx] = *it;
        current_step[current_step_idx].push_back(n);
        current_step_idx++;
      }
    }
    pandigitals = current_step;
    generate_09_pandigitals_w_constraints(pandigitals,length,  ++step_number);
  }
}


void print_vector(const std::vector<us> *ptr)
{
  std::vector<us>::const_iterator it; 
  std::cout << "\t";
  for (it = ptr->begin(); it != ptr->end(); it++)
    std::cout << *it;
  std::cout << std::endl; 
}


void print_candidates(
  std::vector< std::vector<us> > &pandigitals)
{
  std::cout << "Size: " << pandigitals.size() << std::endl;

  std::vector< std::vector<us> >::iterator it;
  for (it = pandigitals.begin(); it != pandigitals.end(); it++) {
    print_vector(&*it);
  }
}


std::vector<us> sum_reduce(std::vector< std::vector<us> > &nums)
{
  std::vector<us> sum;
  us carry_over = 0;
  us temp;
  us nth_digit_from_left = nums[0].size();  // traversing vec of num vec in the reverse order:
  std::vector< std::vector<us> >::iterator it;
  while (nth_digit_from_left > 0) {
    temp = 0;
    for (it = nums.begin(); it != nums.end(); it++) {
      temp += (*it)[nth_digit_from_left - 1];
    }
    temp += carry_over;
    sum.push_back(temp % 10);
    carry_over = temp / 10;
    nth_digit_from_left--;
  }
  while (carry_over != 0) {
    sum.push_back(carry_over % 10);
    carry_over /= 10;
  }

  std::reverse(sum.begin(), sum.end());
  return sum;
}


int main()
{
  std::vector< std::vector<us> > pandigitals;
  generate_09_pandigitals_w_constraints(pandigitals);
  print_candidates(pandigitals);

  // Compute and print the sum:
  std::vector<us> sum = sum_reduce(pandigitals);
  std::cout << "\t----------" << std::endl;
  std::cout << "Sum: ";
  print_vector(&sum);

  return 0;
}
