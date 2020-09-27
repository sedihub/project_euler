/*
PROBLEM:
    Find the sum of all the primes below two million.

SOLUTION:
    The answer is: 142913828922
**/

#include <iostream>  
#include <set>

template <typename T>
class PrimalityTest
{
public:
    PrimalityTest(){
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

    void print_primes(){
        for (it = primes.begin(); it != primes.end(); ++it) {
            std::cout << "\t" << *it << std::endl;
        }

    }

    int get_number_of_primes(){
        return primes.size();
    }

    T get_sum()
    {
        T sum = 0;
        for (it = primes.begin(); it != primes.end(); ++it) {
            sum += *it;
        }
        return sum;
    }

    T get_nth_last_prime(unsigned int n=0)
    {
        rit = primes.rbegin();
        std::advance(rit, n);
        return *rit;
    }

protected:
    std::set<T> primes;
    typename std::set<T>::iterator it;
    typename std::set<T>::reverse_iterator rit;
};


int main()
{
    unsigned long long upper_limit = 2000000;
    PrimalityTest<unsigned long long int> pt;
    unsigned long long int k = 6;
    while (k + 5 < upper_limit) {
        pt.is_prime(k+1);
        pt.is_prime(k+5);
        k += 6;
    }
    if(k+1 < upper_limit) pt.is_prime(k+1);


    std::cout << "Sum of primes under " << upper_limit << ": " << pt.get_sum() << std::endl;

    return 0;
}