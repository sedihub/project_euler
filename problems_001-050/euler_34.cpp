/*
PROBLEM:
    145 is a curious number, as 1! + 4! + 5! = 1 + 24 + 120 = 145.

    Find the sum of all numbers which are equal to the sum of the factorial of their digits.

    Note: As 1! = 1 and 2! = 2 are not sums they are not included.


SOLUTION:
    Brute force search is quite slow and inefficient. I have included it for comparison. 

    A better solution would be to create the numbers from digits. We first need to find the 
    largest number of digits that such a number can have:

        9999...9[n] > n * 9!
        
        9\frac{10^{n+1} - 1}{10 - 1} > n 9!
        
        10^{n+1} - 1 > n * 9!    --->  n < 10^{n+1}/9!

    To generate candidates, we start with various sums of factorials and check which ones 
    correspond to a number of the same digits. If not, we move on to the next. Now, all we
    need is various two, three, four,... n-digit candidates: For this, we can use `char`
    and use white space to generate digits of all lengths in ascending order as the order
    of digits does not matter. To avoid duplicates, we need to require that white spaces
    are not added after a valid (0-9) digit.

    Finally, note that we will see cases such as 

        {'0', '0' , '0', '1'} 

    when generating candidates. Such sequences are to be understood as `1000`. The only
    redundant case is {'0', '0', '0', '0', '0', '0'}, which is inconsequential (one extra
    sequence to check, which is not a solution. I ignore single digit cases when checking 
    solution l.192 in `check_is_solution(...)`.


    ANSWER: 40730
**/


#include <iostream>
#include <vector>
#include <map>
#include <algorithm>


typedef unsigned int uint;


uint pow(uint a, uint n)
{
    if (n == 0) return 1;
    else if (n == 1) return a;
    else {
        uint p = a;
        while (n > 1) {
            p *= a;
            n--;
        } 
        return p;
    }
}


uint factorial(uint n)
{
    uint f = 1;
    while (n > 1){
        f *= n;
        n--; 
    }
    return f;
}

namespace solution1 {
    uint brute_force(
        const uint &num_digits, 
        std::map<uint, uint> &digit_factorials,
        bool verbose=false)
    {
        uint sum = 0;
        
        // Find the numbers:
        uint temp;
        uint sum_digit_factorial;
        for (uint n = 3; n <= (num_digits * digit_factorials[9]); n++) {
            sum_digit_factorial = 0;
            temp = n;
            while (temp > 0) {
                sum_digit_factorial += digit_factorials[temp % 10];
                temp /= 10;
            }
            if (n == sum_digit_factorial) {
                if (verbose) std::cout << "\t" << n << std::endl;
                sum += n;
            }
        }
        
        return sum;
    }
}


namespace solution2 {
    std::vector< std::vector <char> > n_digit_subsets(
        std::vector< std::vector<char> > &previous, uint num_remaining_elements)
    {
        if (num_remaining_elements == 0)
            return previous;

        std::vector< std::vector<char> >::iterator it;
        std::vector< std::vector <char> > new_combs;
        uint idx = 0;
        uint last_digit;
        for (it = previous.begin(); it != previous.end(); it++) {
            if (it->back() == ' ') {
                new_combs.push_back(std::vector<char>());
                new_combs[idx] = *it;
                new_combs[idx].push_back(' ');
                idx++;
            }
            if (it->back() == ' ') 
                last_digit = 0;
            else 
                last_digit = (uint)(it->back() - '0');
            //
            for (uint n = last_digit; n <= 9; n++) {
                new_combs.push_back(std::vector<char>());
                new_combs[idx] = *it;
                new_combs[idx].push_back((char)n + '0');
                idx++;
            }
        }

        num_remaining_elements--;
        return n_digit_subsets(new_combs, num_remaining_elements);
    }


    template<typename T>
    bool compare(std::vector<T>& v1, std::vector<T>& v2)
    {
        std::sort(v1.begin(), v1.end());
        std::sort(v2.begin(), v2.end());
        return v1 == v2;
    }


    uint char_to_uint(char &c)
    {
        return (uint)(c - '0');
    }


    char uint_to_char(uint &n)
    {
        return (char)n + '0';
    }


    uint vec_of_digits_to_num(
        std::vector<char> &candidate,
        std::map<uint, uint> &digit_factorials)
    {
        uint num = 0;
        std::vector<char>::iterator it;
        for (it = candidate.begin(); it != candidate.end(); it++)
            if (*it != ' ') {
                num += digit_factorials[char_to_uint(*it)];
            }

        return num;
    }


    bool check_is_solution(
        std::vector<char> &candidate, 
        std::map<uint, uint> &digit_factorials)
    /* This may modify `candidate`...
    **/
    {
        uint num = 0;
        uint num_candidate_digits = 0;
        std::vector<char>::iterator it;
        for (it = candidate.begin(); it != candidate.end(); it++)
            if (*it != ' ') {
                num_candidate_digits++;
                num += digit_factorials[char_to_uint(*it)];
            }

        if(num_candidate_digits <= 1)
            return false;

        std::vector<char> decimal_rep;
        uint digit;
        while (num > 0) {
            digit = num % 10;
            if(std::find(candidate.begin(), candidate.end(), uint_to_char(digit)) == candidate.end())
                return false;
            decimal_rep.push_back(uint_to_char(digit));
            num /= 10;
        }

        if(num_candidate_digits != decimal_rep.size())
            return false;

        std::sort(decimal_rep.begin(), decimal_rep.end());
        std::vector<char>::iterator it2 = decimal_rep.begin();
        it = candidate.begin();
        while(*it == ' ') 
            it++;

        while (it2 != decimal_rep.end()) {
            if(*it != *it2) {
                return false;
            }
            it2++;
            it++;
        }

        return true;
    }
}


int main()
{
    uint sum_solutions = 0;

    // Form a hash table of factorials:
    std::map<uint, uint> digit_factorials;
    for (uint n = 0; n <= 9; n++) 
        digit_factorials[n] = factorial(n);

    // Determine the largest number of digits possible:
    uint num_digits = 1;
    while (num_digits * digit_factorials[9] > pow(10, num_digits)) {
        num_digits++; 
    }
    num_digits--;  // If it is larger than this, then there is no solution. 
    std::cout << "Number of digits: " << num_digits << std::endl;


    // SOLUTION 1: Brute force solution:
    // sum_solutions = solution1::brute_force(num_digits, digit_factorials, true);
    // std::cout << "Sum of solutions: " << sum_solutions << std::endl;


    // SOLUTION 2: Compile candidates and check:
    std::vector< std::vector <char> > combs = {
        {' '}, {'0'}, {'1'}, {'2'}, {'3'}, {'4'}, {'5'}, {'6'}, {'7'}, {'8'}, {'9'}
    };
    combs = solution2::n_digit_subsets(combs, num_digits - 1);
    std::vector< std::vector<char> >::iterator it;
    std::cout << "Number of candidates: " << combs.size() << std::endl;
    for (it = combs.begin(); it != combs.end(); it++) {
        if (solution2::check_is_solution(*it, digit_factorials)) {
            std::cout << "\t";
            for (std::vector<char>::iterator it2 = it->begin(); it2 != it->end(); it2++)
                std::cout << *it2;
            std::cout << " ---> " << solution2::vec_of_digits_to_num(*it, digit_factorials);
            std::cout << std::endl;
            sum_solutions += solution2::vec_of_digits_to_num(*it, digit_factorials); 
        }
    }
    std::cout << "Sum of solutions: " << sum_solutions << std::endl;

    return 0;
}
