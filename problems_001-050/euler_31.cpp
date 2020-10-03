/*
PROBLEM:
  In the United Kingdom the currency is made up of pound (£) and pence (p). There are eight 
  coins in general circulation:

    1p, 2p, 5p, 10p, 20p, 50p, £1 (100p), and £2 (200p).
  
  It is possible to make £2 in the following way:

  1×£1 + 1×50p + 2×20p + 1×5p + 1×2p + 3×1p

  How many different ways can £2 be made using any number of coins?


SOLUTION: 
  This problem offers a good opportunity to learn more about recursion and why it is
  useful. Specifically, we will see why this saves us coding time and allows to write
  extensible code.

  We can solve this problem in two ways: The first way is to use eight nested loops.
  This, of course, is not elegant. This approach has a few major flaws:
    - It's not easily extensible: If you pose the same problem in terms of Canadian
      coins (nickels, dimes, quarters, loonies and toonies) or US coins (pennies, 
      dimes, nickels and quarters), one would have to add and remove several lines
      the very least.
    - Code is long and not easy to understand or maintain.

  The more elegant way is to leverage recursion: This is computationally the same as
  the previous solution, but is much nicer. Basically, the nested loops become implicit. 

  ANSWER: 73682
**/


#include <iostream>


typedef unsigned int uint;


uint numb_combinations_in_uk_coins(uint amount)
{
  uint count  = 0;
  uint temp1 , temp2 , temp3 , temp4 , temp5 , temp6;
  for( uint p200 = 0 ; p200 <= amount/200 ; p200++ )
  {
    amount -= p200*200;
    for (uint p100 = 0; p100 <= amount/100; p100++) {
      temp1 = amount - p100*100;
      for (uint p50 = 0 ; p50 <= temp1/50 ; p50++) {
        temp2 = temp1 - p50*50;
        for (uint p20 = 0; p20 <= temp2/20; p20++) {
          temp3 = temp2 - p20*20;
          for (uint p10 = 0; p10 <= temp3/10; p10++) {
            temp4 = temp3 - p10*10;
            for (uint p5 = 0; p5 <= temp4/5; p5++) {
              temp5 = temp4 - p5*5;
              for (uint p2 = 0; p2 <= temp5/2; p2++) {
                temp6 = temp5 - p2*2;
                count++; 
              }
            }
          }
        }
      }
    }
    amount = 200;
  }

  return count;
}


uint numb_coin_combinations(uint amount, uint *coins, uint num_coins)
{
  // Since the smallest coin is 1, we don't need to worry about cases where the
  // combination is not possible.
  if (num_coins == 1)
    return 1;
  //
  uint count = 0;
  for (uint n = 0; n <= amount/coins[0]; n++){
    count += numb_coin_combinations(
      (amount - n * coins[0]),
      coins + 1, 
      num_coins - 1);
  }
  return count;
}


int main()
{
  const uint amount = 200;
  const uint num_coins = 8;
  uint descending_value_coins[8] = {200, 100, 50, 20, 10, 5, 2, 1};

  std::cout << "[SOLUTION 1]: Count: " << numb_combinations_in_uk_coins(amount) << std::endl;
  std::cout << "[SOLUTION 2]: Count: " << numb_coin_combinations(amount, descending_value_coins, 8) << std::endl;

  return 0;
}
