/*
PROBLEM:
  If the numbers 1 to 5 are written out in words: one, two, three, four,
  five, then there are 3 + 3 + 5 + 4 + 4 = 19 letters used in total.

  If all the numbers from 1 to 1000 (one thousand) inclusive were written 
  out in words, how many letters would be used?

  For example:
    342 (three hundred and forty-two) ----> 23 letters 
    115 (one hundred and fifteen) ---> 20 letters
  The use of "and" when writing out numbers is in compliance with British
  usage.


SOLUTION:
  Actually, we can solve this with no programming. Nevertheless, I will code
  this up for fun :)

  ANSWER: 21124


NOTE:
  YOU SHOULD COMPILE THIS WITH C++11 COMPILER (`-std=c++11`)
**/

#include <iostream>
#include <map>

typedef unsigned int uint;

int main()
{
  std::map<uint, uint> num_letters = {
    {0, 4},  // Zero
    {1, 3},  // One
    {2, 3},  // Two
    {3, 5},  // Three
    {4, 4},  // Four
    {5, 4},  // Five
    {6, 3},  // Six
    {7, 5},  // Seven
    {8, 5},  // Eight
    {9, 4},  // Nine
    //
    {10, 3},  // Ten
    {11, 6},  // Eleven
    {12, 6},  // Twelve
    {13, 8},  // Thirteen
    {14, 8},  // Fourteen
    {15, 7},  // Fifteen
    {16, 7},  // Sixteen
    {17, 9},  // Seventeen
    {18, 8},  // Eighteen
    {19, 8},  // Nineteen
    //
    {20, 6},  // Twenty
    {30, 6},  // Thirty
    {40, 5},  // Forty
    {50, 5},  // Fifty
    {60, 5},  // Sixty
    {70, 7},  // Seventy
    {80, 6},  // Eighty
    {90, 6},  // Ninety
    //
    {100, 7},   // Hundred
    {1000, 8},  // Thousand
  };

  uint letter_count = 0;
  uint temp;
  uint n;
  bool show = true;
  for (uint i = 1; i < 1000; ++i){
    n = i;
    if (show) std::cout << "\t" << n << ": ";
    // 100s
    temp = n / 100;
    if (temp != 0) {
      if (n % 100 == 0){ // X00 is X hundred, without the "and"!
        if (show) std::cout << 100*temp << " [" << num_letters[temp] + num_letters[100] << "] ";
        letter_count += num_letters[temp] + num_letters[100];
      }
      else {
        if (show) std::cout << 100*temp << " [" << num_letters[temp] + num_letters[100] + 3 << "] ";
        letter_count += num_letters[temp] + num_letters[100] + 3;
      }
    }
    //
    // 10s
    n = n % 100;
    temp = n / 10;
    if (temp >= 2) {
      letter_count += num_letters[10 * temp];
      if (show) std::cout << 10*temp << " [" << num_letters[10*temp] << "] " << " ";
      if ((n % 10) != 0) {
        if (show) std::cout << n % 10 << " [" << num_letters[n % 10] << "] ";
        letter_count += num_letters[n % 10];
      }
    }
    else if (temp == 1) {
      if (show) std::cout << n << " [" << num_letters[n] << "] ";
      letter_count += num_letters[n];
    }
    else if (temp == 0) {
      if ((n % 10) != 0) {
        if (show) std::cout << n % 10 << " [" << num_letters[n % 10] << "] ";
        letter_count += num_letters[n % 10];
      }
    }
    if (show) std::cout << std::endl;
  }
  letter_count += (num_letters[1] + num_letters[1000]); // The last number, 1000

  std::cout << "Number of letters: " << letter_count << std::endl;

  return 0;
}
