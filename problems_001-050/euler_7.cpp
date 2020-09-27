/*
PROBLEM:
    What is the 10001st prime number?

SOLUTION:
    We are going to find 10001st prime number!
    The answer is: 104743
**/

#include <iostream>  
#include <set>

template <typename T>
class PrimalityTest
{
public:
    PrimalityTest()
    {
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
    const int nth_prime = 10001;

    PrimalityTest<unsigned long long int> pt;
    int counter = pt.get_number_of_primes();
    unsigned long long int k = 6;
    while (counter < nth_prime) {
        if (pt.is_prime(k + 1)) {
            counter++;
        }
        if (pt.is_prime(k + 5)) {
            counter++;
        }
        k += 6;
    }

    // pt.print_primes();

    if (counter == nth_prime + 2) {
        std::cout << pt.get_nth_last_prime(2) << std::endl;
    }
    else if (counter == nth_prime + 1) {
        std::cout << pt.get_nth_last_prime(1) << std::endl;
    }
    else if (counter == nth_prime){
        std::cout << pt.get_nth_last_prime(0) << std::endl;
    }
   	else {
   		std::cerr << "ERROR..." << std::endl;
   		return 1;
   	}

    return 0;
} 