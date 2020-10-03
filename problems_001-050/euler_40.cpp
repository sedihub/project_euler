/*
PROBLEM:
  An irrational decimal fraction is created by concatenating the positive integers:

      0.123456789101112131415161718192021...
                   ^

  It can be seen that the 12th digit of the fractional part is 1.

  If d_n represents the nth digit of the fractional part, find the value of the 
  following expression.

      d_1 × d_{10} × d_{100} × d_{1000} × d_{10000} × d_{100000} × d_{1000000}


SOLUTION: 
  If we partition the decimal fraction as follows:

      0.|123456789|101112131415161718192021...99|100101...999|1000...

  Finding the nth digit becomes easy: Use the minimum and maximum partition numbers
  to find out which partition the nth number falls in. Then subtract from n (min -1).
  The `-1` is to move it to the maximum of the previous partition. Now, ceil of this 
  number divided by the number of digits in this partition gives us the mth element of
  this partition (for example, the 2nd of 2-digits is 11, etc.). Finally, we compute
  which digit of this mth d-digit number the nth maps to. This is the digit we need.
  Note that for the last step we need the digit from left not right!
        
  ANSWER: (1)(1)(5)(3)(7)(2)(1) = 210
**/

#include <iostream>
#include <iomanip>
#include <map>


typedef unsigned int uint;


uint num_ndigit_ints(uint n)
/* Returns the number of n-digit numbers.
**/
{
  uint num = 9;
  while (n > 1) {
    num *= 10;
    n--;
  }
  return num;
}


uint nth_digit_of_mth_d_digit_number(
  uint nth, // nth digit
  uint mth, // mth d-digit number
  uint d  // Number of digits
)
{
  // First, find the mth number:
  uint mth_num = 1;
  while (d > 1) {
    mth_num *= 10;
    d--;
  }
  mth_num += mth - 1;

  // Next, find the nth digit:
  while (nth > 1) {
    mth_num /= 10;
    nth--;
  }

  return mth_num % 10;
}


void find_dns(std::map<uint, char> &dn_map)
{
  uint partition_idx_min = 1;
  uint partition_idx_max = 9;
  uint partition_num_digits = 1;
  uint mth, nth;
  std::map<uint, char>::iterator it;
  for (it = dn_map.begin(); it != dn_map.end(); it++) {
    while (it->first > partition_idx_max) {
      partition_idx_min = 1 + partition_idx_max;
      partition_num_digits++;
      partition_idx_max += partition_num_digits * num_ndigit_ints(partition_num_digits);
    }
    mth = it->first - (partition_idx_min - 1);
    if (mth % partition_num_digits != 0){
      nth = partition_num_digits + 1 - (mth % partition_num_digits);
      mth /= partition_num_digits;
      mth += 1;  // integer division is floor, I want ceil.
    }
    else {
      mth /= partition_num_digits;
      nth = 1;
    }
    it->second = '0' + (char)nth_digit_of_mth_d_digit_number(
      nth, mth, partition_num_digits);
  }
}


int main()
{
  std::map<uint, char> dn_map = {
    {1, '-'}, 
    {10, '-'}, 
    {100, '-'}, 
    {1000, '-'}, 
    {10000, '-'}, 
    {100000, '-'},
    {1000000, '-'},
  };

  find_dns(dn_map);

  uint prod = 1;
  std::map<uint, char>::iterator it;
  std::cout << "\t";
  for (it = dn_map.begin(); it != dn_map.end(); it++) {
    std::cout << "(" << it->second << ")";
    prod *= (uint)(it->second - '0');
  }
  std::cout << " = " << prod << std::endl;

  return 0;
}
