/*
PROBLEM:
    Surprisingly there are only three numbers that can be written as the sum of fourth powers
     of their digits:

            1634 = 14 + 64 + 34 + 44
            8208 = 84 + 24 + 04 + 84
            9474 = 94 + 44 + 74 + 44

    As 1 = 14 is not a sum it is not included. The sum of these numbers is: 

            1634 + 8208 + 9474 = 19316.

    Find the sum of all the numbers that can be written as the sum of fifth powers of their 
    digits.

SOLUTION:
    Here is the idea: Determine the n-digit largest number than can be the sum of the fifth
    power of it's digits:

            N_max == n * 9^5 = n * 59049 

    This can be solved analytically by taking the log_10 of both sides. Below, I compute it
    in a brute force way: searching for the largest n that the above inequality holds for.

    For the rest, we can either compute all n = 2, 3,... n_max numbers that are the sum of
    the fifth powers of their digits, or do it the less efficient, though easier brute-force
    search.

    Here I opt for the less efficient approach as it is much simpler to code.  

    Answer: 443839
**/


#include <iostream>
#include <vector>


unsigned int pow(unsigned int a, unsigned int n)
{
    if( n == 0 )
        return 1; 
    if( n == 1 )
        return a;
    
    unsigned int temp = a;
    while (n > 1) {
        a *= temp; 
        n--;
    }

    return a;
}


unsigned int sum_digigts_power(unsigned int n, unsigned int p=5)
{
    unsigned int sum = 0;
    std::vector<unsigned int> digits;
    while (n > 0) {
        digits.push_back( n%10 );
        n /= 10;
    }

    std::vector<unsigned int>::iterator it;
    for (it = digits.begin(); it != digits.end(); it++) {
        sum += pow(*it , p);
    }

    return sum;
}


int main()
{
    unsigned int n = 1;
    while (n * pow(9, 5) >= pow(10, n)) n++;
    
    const unsigned int max = n * pow(9, 5);
    std::cout << n << ", Max: " << max << std::endl;
    
    // n=1 does not count...
    n = 2; 
    unsigned int sum=0;
    while (n < max) {
        if (n == sum_digigts_power(n, 5)) { 
            sum += n;
            std::cout << n << std::endl; 
        }
        n++;
    }    
    std::cout << "-------------" << std::endl;
    std::cout << sum << std::endl; 

    return 0;
}
