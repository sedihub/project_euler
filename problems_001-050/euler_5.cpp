/*
PROBLEM:
    What is the smallest positive number that is evenly divisible 
    by all of the numbers from 1 to 20?

SOLUTION:
    The product of all pure largest primes powers smaller than 20!
        (2^4) * (3^2) * 5 * 7 * 11 * 13 * 17 * 19 = 232,792,560
**/

#include <iostream>  

int main()
{
    std::cout << 16 * 9 * 5 * 7 * 11 * 13 * 17 * 19 << std::endl;

    return 0;
} 