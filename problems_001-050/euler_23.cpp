/*
PROBLEM:
    Perfect Number: A perfect number is a number for which the sum of its proper divisors is 
    exactly equal to the number.

    Deficient Number: A number n is called deficient if the sum of its proper divisors is less
    than n and it is called abundant if this sum exceeds n. 

    For example, the sum of the proper divisors of 28 would be 1 + 2 + 4 + 7 + 14 = 28, which 
    means that 28 is a perfect number. 12 is the smallest abundant number, 1 + 2 + 3 + 4 + 6 = 16,
    the smallest number that can be written as the sum of two abundant numbers is 24. By 
    mathematical analysis, it can be shown that all integers greater than 28123 can be written as 
    the sum of two abundant numbers. However, this upper limit cannot be reduced any further by 
    analysis even though it is known that the greatest number that cannot be expressed as the sum
    of two abundant numbers is less than this limit.

    Find the sum of all the positive integers which cannot be written as the sum of two abundant
    numbers.

SOLUTION:
    Let's try to understand this problem a bit more. Given `n` and its prime decomposition,

        n = (p_0 ^ e_0) * (p_1 ^ e_1) * ... * (p_k ^ e_k)

    The sum of the proper divisors of n, d(n) is given by:
    
        d(n) = (1 + p_0 + p_0^2 + ... + p_0^e_0) * ... * (1 + p_k + p_k^2 + ... + p_k^e_k) - n

    n is perfect if d(n) = n, deficient if d(n) < n, and abundant if d(n) > n. Using geometric 
    sum formula, d(n) can be written as:

        d(n) = \frac{p_0^{e_0+1} - 1}{p_0 - 1} * ... * \frac{p_k^{e_k+1} - 1}{p_k - 1} - n 

    Let's check this for 12 and 28: 

        12 = 2^2 * 3 ---> d(12) = (2^3 - 1)/(2 - 1) * (9 - 1)/(3 - 1) - 12 = 7 * 4 - 12 = 16.
        28 = 2^2 * 7 ---> d(28) = (2^3 - 1)/(2 - 1) * (49 - 1)/(7 - 1) - 28 = 7 * 8 - 28 = 28.

    Next, let's see if we can at least develop some intuition for why 28123 is an upper limit.
    It is more convenient to compare, the set of all divisors of n, d(n) + n, against 2*n:

    (p_0^e_0) * ... * (p_k^e_k)    ?   (1 + p_0 + ... + p_0^e_0) * ... * (1 + p_k + ... + p_k^e_k)

    We make a few observations:

     - If n is abundant, so is any multiple of n.
     - If n is perfect, m x n for m > 1 is abundant.
     - For any even number n > 46 there exist at least two abundant numbers that add up to n. The
       proof is by looking at n modulo 12. 12 is an abundant number and using k = n (mode 12)
       there are only 6 possibilities (since we assumed n is an even number):
           k = 0: Trivial.
           k = 2  ---> write n as n =  6*m + 20 
           k = 4  --->            n = 12*m + 40
           k = 6  --->            n = 12*m +  6  
           k = 8  --->            n = 12*m + 20  
           k = 10 --->            n =  6*m + 40 
       Theses are all sums of abundant numbers.
     - All integers greater than 20161 can be expressed as the sum of two abundant numbers.
       The proof is as follows: Write n = 88 * e + 315 * o, where e is even and 2 < o < 90
       is odd. (88 * e) is an abundant number as it is even and greater than 46. We need to
       check 315 * o. 315 = 3^2 * 5 * 7. 
    
    (For more information see https://en.wikipedia.org/wiki/Abundant_number and 
    http://oeis.org/wiki/Abundant_numbers)

    Using these, we can conduct a more efficient search.

    The answer is: 4179871
**/

#include <iostream>
#include <set>
#include <map>


typedef unsigned int uint;

std::map<uint, bool> visited_nums;
bool is_abundant(uint n)
{
    if(visited_nums.find(n) == visited_nums.end()) {
        uint sum = 0;
        for (uint i = 1; i < n; i++) {
            if((n % i) == 0) sum += i;
        }
        visited_nums[n] = (sum > n);
    }
    return visited_nums[n];
}


int main()
{
    const bool print = true;
    uint sum_nonabundant_sums = 0;

    // Check the even numbers less than 47 first:
    bool is_sum_of_abundants;  
    uint n = 2;
    while (n <= 46) {
        is_sum_of_abundants = false;
        for(uint j = 1; j < n ; ++j) {
            if(is_abundant(j) && is_abundant(n - j)){
                is_sum_of_abundants = true;
                break;
            }
        }
        if(! is_sum_of_abundants) {
            sum_nonabundant_sums += n;
            if (print) std::cout << "\t" << n << std::endl;
        }
        n += 2;
    }

    // Check odd numbers:
    n = 1;
    while (n <= 28123){
        is_sum_of_abundants = false;
        for(uint j = 1; j < n ; ++j) {
            if(is_abundant(j) && is_abundant(n - j)){
                is_sum_of_abundants = true;
                break;
            }
        }
        if(! is_sum_of_abundants) {
            sum_nonabundant_sums += n;
            if (print) std::cout << "\t" << n << std::endl;
        }
        n += 2;
    }

    std::cout << "Sum of numbers that cannot be written as the sum of two abundant numbers: " 
              << sum_nonabundant_sums << std::endl;

    return 0;
}
