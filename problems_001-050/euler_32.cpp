/*
PROBLEM:
    We shall say that an n-digit number is pandigital if it makes use of all the digits 1 to n 
    exactly once; for example, the 5-digit number, 15234, is 1 through 5 pandigital.

    The product 7254 is unusual, as the identity, 39 × 186 = 7254, containing multiplicand, 
    multiplier, and product is 1 through 9 pandigital.

    Find the sum of all products whose multiplicand/multiplier/product identity can be written
    as a 1 through 9 pandigital.

    HINT: Some products can be obtained in more than one way so be sure to only include it once
    in your sum.


SOLUTION:
    The brute-force search is certainly an option. We can achieve a much faster solution by taking
    into account some of the constraints of the problem:

     - Assuming that the multiplicand is smaller (they cannot be equal) than the multiplier, the
       only possible number of digits are (since `0` is not in the set of digits):

            [1] x [4] = [4]
            [2] x [3] = [4]
            [3] x [3] = [4] <---- Not possible as 123 * 123 = 15,129

     - Expanding, the multiplicand and the multiplier, we find that certain digits cannot appear
       together. For example, consider the case [1] x [4]:

            d1 * (d2 * 10^3 + d3 * 10^2 + d4 * 10 + d5) = d6 * 10^3 + d7 * 10^2 + d8 * 10 + d9

              (d1 * d2)10^3 + (d1 * d3)10^2 + (d1 * d4)10 + (d1 * d5)
            = d6 * 10^3 + d7 * 10^2 + d8 * 10 + d9

       First, none of d1, d2, d3, d4, and d5 can be 1 or 5. This is because that would imply the
       same digit appearing twice, thus violating the requirement of being pandigital.

       Second, we will have the following set of equations:

            (d1 * d5) % 10 = d9
            ((d1 * d4) + (d1 * d5) / 10) % 10 = d8
            ...

       Third, the set of the  (di * dj) % 10 are limited:

                1   2   3   4   5   6   7   8   9 
            1   -   -   -   -   -   -   -   -   -

            2   -   -   6   8   -   -  14  16  18

            3   -   6   -  12   -  18  21  24  27

            4   -   8  12   -   -   -  28  32  36

            5   -   -   -   -   -   -   -   -   -

            6   -   -  18   -   -   -  42   -  54

            7   -  14  21  28   -  42   -  56  63

            8   -  16  24  32   -   -  56   -  72

            9   -  18  27  36   -  54  63   72  -


        We observe that,

            1[1], 2[4], 3[1], 4[3], 6[4], 7[1], 8[4]
                
        Now, if we start with all possible products we can then try to determine which ones are
        compatible with 1-digit by 4-digit or 2-digit by 3-digit multiplications.


    Answer: 45228 There are only 7 unique products!

    NOTE: You need to compile this with the `--std=c++11` flag because of the initialization of the
    standard containers!
**/


#include <iostream>
#include <map>
#include <vector>
#include <utility>
#include <set>


// Define a constant map for the digit multiplications:
typedef unsigned short int usint;


std::vector< std::vector<usint> > products(std::vector< std::vector<usint> > &previous)
/* Has to be initialized/primes with a non-empty vector -- see main().
**/
{
    if (previous[0].size() == 4 || previous.empty())
        return previous;

    std::vector< std::vector<usint> > new_prods;
    unsigned int idx = 0;

    std::vector< std::vector<usint> >::iterator it;
    for (it = previous.begin(); it != previous.end(); it++) {
        for (usint n = 1; n <= 9; n++) {
            if(std::find(it->begin(), it->end(), n) == it->end()) {
                new_prods.push_back(std::vector<usint>());
                new_prods[idx] = *it;
                new_prods[idx].push_back(n);
                idx++;
            }
        }
    }

    return products(new_prods);
}


usint digits_to_ullint(const std::vector<usint>& digits_vec)
{
    usint decimal_rep = 0;
    usint exponent = 1;
    std::vector<usint>::const_iterator it;
    for (it = digits_vec.begin(); it != digits_vec.end(); it++) {
        decimal_rep += exponent * (*it);
        exponent *= 10;
    }

    return decimal_rep;
}


bool is_pandigital_prod(const std::vector<usint>& prod)
{
    usint n;
    usint num = digits_to_ullint(prod);

    // Check 1-digit x 4-digit case:
    usint temp;
    bool is_solution;
    usint d;
    usint num_digits;
    std::set<usint> temp_digits_set;
    for (n = 1; n <= 9; n++) {
        if (std::find(prod.begin(), prod.end(), n) == prod.end()) {
            if (num % n == 0) {
                temp = num / n; 
                is_solution = true;
                temp_digits_set.clear();
                num_digits = 0;
                while (temp > 0) {
                    d = temp % 10;
                    if (d == 0 || d == n || std::find(prod.begin(), prod.end(), temp % 10) != prod.end()) {
                        is_solution = false;
                        break;
                    }
                    num_digits++;
                    temp_digits_set.insert(d);
                    temp /= 10;
                }
                if (is_solution && temp_digits_set.size() == num_digits && num_digits == 4) {
                    // std::cout << "\t\t" <<  n  << " * " << num / n << " = " << num << std::endl;
                    return true;
                }
            }
        }
    }

    // Check 2-digit x 5-digit case:
    for (usint n1 = 1; n1 <= 9; n1++) {
        if (std::find(prod.begin(), prod.end(), n1) != prod.end()) 
            continue;
        for (usint n0 = 1; n0 <= 9; n0++) {
            if(n0 == n1) 
                continue;
            if (std::find(prod.begin(), prod.end(), n0) != prod.end()) 
                continue;
            n = 10 * n1 + n0;
            if (num % n == 0) {
                temp = num / n; 
                is_solution = true;
                temp_digits_set.clear();
                num_digits = 0;
                while (temp > 0) {
                    d = temp % 10;
                    if (d == 0 || d == n1 || d == n0 || std::find(prod.begin(), prod.end(), temp % 10) != prod.end()) {
                        is_solution = false;
                        break;
                    }
                    num_digits++;
                    temp_digits_set.insert(d);
                    temp /= 10;
                }
                if (is_solution && temp_digits_set.size() == num_digits && num_digits == 3) {
                    // std::cout << "\t\t" <<  n  << " * " << num / n << " = " << num << std::endl;
                    return true;
                }
            }
        }
    }

    return false;
}


int main() 
{
    std::vector< std::vector<usint> > vec = {
        {1}, {2}, {3}, {4}, {6}, {7}, {8},
    };
    vec = products(vec);


    usint count = 0;
    unsigned long long int sum = 0;
    std::vector< std::vector<usint> >::iterator it;
    std::vector<usint>::reverse_iterator rit;
    for (it = vec.begin(); it != vec.end(); it++) {
        // std::cout << "\t";
        // for(rit = it->rbegin(); rit != it->rend(); rit++) {
        //     std::cout << *rit;
        // }
        
        if (is_pandigital_prod(*it)) {
            sum += (unsigned long long int)digits_to_ullint(*it);
            count++;
            // std::cout << " ---> " << digits_to_ullint(*it) << std::endl;
        }
        // else
        //     std::cout << "  X" << std::endl;
    }


    std::cout << "Number of valid unique products: " << count
              << " / " << vec.size() << std::endl;
    std::cout << "Sum of valid unique products: " <<  sum << std::endl;

    return 0;
}