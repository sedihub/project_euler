/*
PROBLEM:
    What is the largest prime factor of the number 600851475143?

Solution:
    First, we need to use 64-bit unsigned integer type for this 
    problem. We can, however, utilize a trick using the double 
    or 32-bit float type. 

    The largest prime factor of an integer cannot be larger than
    it's square root. We will utilize this property.

    We can further reduce the computation by using a certain moduli
    of a small integer. Here we use 6. The only moduli that we need 
    to consider are 1 and 5.

    We get: 6 x 1142 + 5 = 6857
**/

#include <iostream>
#include <set>

class PrimalityTest
{
public:
    bool IsPrime(unsigned long long n)
    {
        it = prime_numbers.begin();
        while(it != prime_numbers.end() and (*it)*(*it) <= n){
            if(n % (*it) == 0) return false;
            it++;
        }
        prime_numbers.insert(n);
        return true;
    }

    void PrintPrimes()
    {
        std::cout << "Accumulated Prime Numbers:" << std::endl;
        for(it = prime_numbers.begin(); it != prime_numbers.end(); it++)
        {
            std::cout << "\t" << *it << std::endl;
        }
    }

protected:
    std::set<unsigned long long> prime_numbers;
    std::set<unsigned long long>::iterator it;
};

int main()
{
    unsigned long long n = 600851475143;
    unsigned long long p = 1;

    if (n % 2 == 0) p = 2;
    if (n % 3 == 0) p = 3;
    if (n % 5 == 0) p = 5;

    // Add the first three primes that we checked manually 
    PrimalityTest pt;
    pt.IsPrime(2);
    pt.IsPrime(3);
    pt.IsPrime(5);
    
    unsigned long long x = 6;
    while (x * x <= n) {
        if(pt.IsPrime(x + 1)){
            if(n % (x + 1) == 0){p = x + 1;}
        }
        if(pt.IsPrime(x + 5)){
            if(n % (x + 5) == 0){p = x + 5;}
        }
        x += 6;
    }

    // pt.PrintPrimes();

    std::cout << "6 x " << (p / 6) << " + " << (p % 6) << " = " << p << std::endl;
    std::cout << n << " % " << p << " = " << (n % p) << std::endl;

    return 0;
}