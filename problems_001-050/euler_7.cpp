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

    IsPrime<unsigned long long int> is_prime;
    int counter = is_prime.get_number_of_primes();
    unsigned long long int k = 6;
    while (counter < nth_prime) {
        if (is_prime.test(k + 1)) {
            counter++;
        }
        if (is_prime.test(k + 5)) {
            counter++;
        }
        k += 6;
    }

    // is_prime.print_primes();

    if (counter == nth_prime + 2) {
        std::cout << is_prime.get_nth_last_prime(2) << std::endl;
    }
    else if (counter == nth_prime + 1) {
        std::cout << is_prime.get_nth_last_prime(1) << std::endl;
    }
    else if (counter == nth_prime){
        std::cout << is_prime.get_nth_last_prime(0) << std::endl;
    }
   	else {
   		std::cerr << "ERROR..." << std::endl;
   		return 1;
   	}

    return 0;
} 