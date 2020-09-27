/*
PROBLEM:
    A unit fraction contains 1 in the numerator. The decimal representation of the unit fractions
    with denominators 2 to 10 are given:

        1/2 =   0.5
        1/3 =   0.(3)
        1/4 =   0.25
        1/5 =   0.2
        1/6 =   0.1(6)
        1/7 =   0.(142857)
        1/8 =   0.125
        1/9 =   0.(1)
        1/10    =   0.1

    Where 0.1(6) means 0.166666..., and has a 1-digit recurring cycle. It can be seen that 1/7 has
    a 6-digit recurring cycle.

    Find the value of d < 1000 for which 1/d contains the longest recurring cycle in its decimal 
    fraction part.
    
SOLUTION:
    The solutino is simple: compute the decimals digit by digit and keep track of the remainder.
    When we encounter the same remainder we have reached a cycle.

    Answer: 1/983 has the cycle length: 982
**/

#include <iostream>
#include <vector>
#include <iterator>


unsigned int length_of_periodic_part(unsigned int m, unsigned int n, bool verbose=false)
{
    std::vector<unsigned int> vec;
    std::vector<unsigned int> decimals;
    unsigned int length = 0;
    m = m % n;
    while (m != 0) {
        m *= 10;
        if (verbose) 
            decimals.push_back(m / n);
        if ((m / n) != 0) 
            m = m % n;
        if ((m != 0) && (std::find(std::begin(vec), std::end(vec), m) != vec.end())) { 
            length = std::distance(std::find(std::begin(vec), std::end(vec), m), vec.end());
            if (verbose) {
                std::cout << "Length of the periodic part: "<< length << std::endl;
                std::cout << "Decimals: .";
                for (std::vector<unsigned int>::iterator it = decimals.begin(); it != decimals.end(); it++)
                    std::cout << *it;
                std::cout << std::endl;
            }
            break; 
        } 
        vec.push_back(m);
    }

    return length;
}


int main()
{
    // // Test on te example:
    // std::cout << "1/2 has the cycle length: " << length_of_periodic_part(1, 2, true) << std::endl;
    // std::cout << "1/6 has the cycle length: " << length_of_periodic_part(1, 6, true) << std::endl;
    // std::cout << "1/7 has the cycle length: " << length_of_periodic_part(1, 7, true) << std::endl;
    // std::cout << "1/17 has the cycle length: " << length_of_periodic_part(1, 17, true) << std::endl;

    unsigned int number;
    unsigned int length = 0;
    unsigned int currentLength;
    for (unsigned int n = 1; n < 1000; n++){
        if ((1000000 % n) == 0) continue;  // A quick and dirty way to weed out some of the finite ones...
        currentLength = length_of_periodic_part(1 , n);
        if (currentLength > length) {
            number = n;
            length = currentLength;
        }
    }
    std::cout << 1 << "/" << number << " has the cycle length: " << length << std::endl;
  
    return 0;
}
