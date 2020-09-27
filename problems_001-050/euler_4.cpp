/*
PROBLEM:
    Find the largest palindrome made from the product of two 3-digit numbers.
    The largest palindrome made from the product of two 2-digit numbers is:
         9009 = 91 × 99.

SOLUTION:
    Brute force solution is to search all three-digit numbers. The complexity 
    of this search is O(N^2).

    Is it possible to improve this?! <--- T.B.D.

    We find:
        913 x 993 = 906609
**/

#include <iostream>   
#include <vector> 


bool IsPalindrome(int m)
{
    char digit = '0';
    std::vector<char> digits;
    while (m != 0) {
        digits.push_back(digit + (m % 10));
        m = m / 10;
    }

    std::vector<char>::reverse_iterator reverse_it = digits.rbegin();
    std::vector<char>::iterator forward_it = digits.begin();
    while (&*reverse_it != &*forward_it){
        if(*(forward_it) != *(reverse_it)) return false;
        if(&*reverse_it == &*(1+forward_it)) break;
        ++forward_it;
        ++reverse_it;
    }

    return true;
}

int main()
{
    int n1_max = 0;
    int n2_max = 0;
    int n1xn2_max;

    int n1xn2 = 0;
    for (int n1 = 100; n1 < 1000; ++n1) {
        for (int n2 = n1; n2 < 1000; ++n2) {
            n1xn2 = n1 * n2;
            if (IsPalindrome(n1xn2)) {
                std::cout << "\t" << n1 << " x " << n2 << " = "\
                          << n1xn2 << std::endl;
                if (n1xn2 > n1xn2_max) {
                    n1_max = n1;
                    n2_max = n2;
                    n1xn2_max = n1xn2;
                }
            }
        }
    }

    std::cout << n1_max << " x " << n2_max << " = "\
              << n1xn2_max << std::endl;

    return 0;
} 