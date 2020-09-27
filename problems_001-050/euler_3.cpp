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


template <typename T>
class PrimalityTest
{
public:
    PrimalityTest()
    {
        // Add the few primes to "prime" it ;)
        primes.insert(2);
        primes.insert(3);
        primes.insert(5);
    }

    bool is_prime(T n)
    {
        if(n == 1)
            return false;
        if (primes.find(n) != primes.end())
            return true;
        for (it = primes.begin(); it != primes.end(); ++it){
            if (n % (*it) == 0) {
                return false;
            }
            if ((*it) * (*it) > n) {
                primes.insert(n);
                return true;
            }
        }
        //
        // If this number is beyond the range of current primes, get the rest:
        rit = primes.rbegin();
        std::advance(rit, 1);
        T m = (*rit);
        while (m <= n) {
            m++;
            this->is_prime(m);
            if (n % m == 0) {
                return false;
            }
        }
        primes.insert(n);
        return true;
    }

    void PrintPrimes()
    {
        std::cout << "Accumulated Prime Numbers:" << std::endl;
        for (it = primes.begin(); it != primes.end(); it++)
        {
            std::cout << "\t" << *it << std::endl;
        }
    }

protected:
    std::set<T> primes;
    typename std::set<T>::iterator it;
    typename std::set<T>::reverse_iterator rit;
};


int main()
{
    unsigned long long n = 600851475143;
    unsigned long long p = 1;

    if (n % 2 == 0) p = 2;
    if (n % 3 == 0) p = 3;
    if (n % 5 == 0) p = 5;

    // Add the first three primes that we checked manually 
    PrimalityTest<unsigned long long int> pt;
    
    unsigned long long x = 6;
    while (x * x <= n) {
        if(pt.is_prime(x + 1)){
            if(n % (x + 1) == 0){p = x + 1;}
        }
        if(pt.is_prime(x + 5)){
            if(n % (x + 5) == 0){p = x + 5;}
        }
        x += 6;
    }

    // pt.PrintPrimes();

    std::cout << "6 x " << (p / 6) << " + " << (p % 6) << " = " << p << std::endl;
    std::cout << n << " % " << p << " = " << (n % p) << std::endl;

    return 0;
}