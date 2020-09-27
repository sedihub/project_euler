/*
PROBLEM:
    Euler discovered the remarkable quadratic_formula formula:

            n^2 + n + 41

    It turns out that the formula will produce 40 primes for the consecutive integer values 
    0 <= n <= 39. However, when n = 40 or 41, n^2 + n + 41 is divisible by 41.

    The incredible formula n^2 - 79*n + 1601 was discovered, which produces 80 primes for the 
    consecutive values 0<= n <= 79. The product of the coefficients, −79 and 1601, is −126479.

    Considering quadratic_formulas of the form:

            n^2 + a*n + b,  where |a| < 1000 and |b| < 1000

    Find the product of the coefficients,  and , for the quadratic_formula expression that 
    produces the maximum number of primes for consecutive values of , starting with 0.
    

SOLUTION:
    Brute-force solution potentially augmented by:
     - b sets the limit: b^2  a * b + b is not prime. I won't utilize this, though.
     - If a is odd, b cannot be even.
     - a cannot be even.

    Answer: -59231
            {a = -61, b = 971}: 0 <= n <= 71
**/


#include <iostream>
#include <map>
#include <iterator>
#include <algorithm>
#include <utility>


bool is_prime(int n)
{
    if (n < 23){
        if(n == 2 || n == 3 || n == 5 || n == 7  || n == 11 || n == 13 || n == 17 || n == 19){
            return true;
        }
        return false;
    }
    else if( n%2  == 0 ) return false;
    else if( n%3  == 0 ) return false;
    else if( n%5  == 0 ) return false;
    else if( n%7  == 0 ) return false;
    else if( n%11 == 0 ) return false;
    else if( n%13 == 0 ) return false;
    else if( n%17 == 0 ) return false;
    else if( n%19 == 0 ) return false;
    for (unsigned int i = 11; (2*i + 1)*(2*i + 1) <= n; i++){
        if(n % (2*i + 1) == 0) return false;
    }
    return true;
}


inline int quadratic_formula(const int &a, const int &b, const int &x)
{
    return (x*x + a*x + b);
}


int main()
{
    int a,b;
    int n;
    int temp;

    std::map< std::pair<int,int> , int > theMap;
    std::pair<int,int>  coefs;

    for (int a = -999; a < 1000; a++) {
        if (a % 2 == 0) continue;
        for (int b = -1000; b < 1001; b++) {
            if (b % 2 == 0) continue;
            n = 0;
            temp = quadratic_formula( a , b , n );
            while (is_prime(temp)) {
                n++;
                temp = quadratic_formula( a , b , n );
            }
            coefs.first  = a;
            coefs.second = b;
            if (n > 1) theMap[ coefs ] = (n-1+1);
        }
    }

    temp = 0;
    std::map< std::pair<int,int> , int >::iterator longestElementIt = theMap.end();
    std::map< std::pair<int,int> , int >::iterator mit;
    for (mit = theMap.begin(); mit != theMap.end(); mit++){
        if (temp < mit->second){
            temp             = mit->second;
            longestElementIt = mit;
        }
        if(mit->second+1 > 40){
            std::cout << "\t{a = " << (mit->first).first << ", b = " << (mit->first).second << "}: " 
                      << mit->second << std::endl;
        }
    }
    std::cout << std::endl;

    std::cout << "ANSWER: {a = " << (longestElementIt->first).first << ", b = " 
              << (longestElementIt->first).second << "}: " << longestElementIt->second << std::endl;

    return 0;
}
