/*
PROBLEM:
    Find the sum of all the primes below two million.

SOLUTION:
    The answer is: 142913828922
**/

#include <iostream>  
#include <set>

template <typename T>
class IsPrime
{
public:
    IsPrime(){
        primes.insert(2);
        primes.insert(3);
        primes.insert(5);
    }

    bool test(T n)
    {
        for (it = primes.begin(); it != primes.end(); ++it){
            if(n % (*it) == 0) return false;
            if((*it) * (*it) > n) break;
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
    IsPrime<unsigned long long int> is_prime;
    unsigned long long int k = 6;
    while (k + 5 < upper_limit) {
        is_prime.test(k+1);
        is_prime.test(k+5);
        k += 6;
    }
    if(k+1 < upper_limit) is_prime.test(k+1);


    std::cout << "Sum of primes under " << upper_limit << ": " << is_prime.get_sum() << std::endl;

    return 0;
}