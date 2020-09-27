/*
PROBLEM:
    What is the sum of the digits of the number 21000?

SOLUTION:
    First off, we know that no native type is 1000-bit long.
    One possible brute-force solution is to construct a custom
    type or use a dynamic container (std::vector) to represent 
    large numbers.

    The answer is:
        2 ^ 1000 = 10715086071862673209484250490600018105614048117055336074
                   43750388370351051124936122493198378815695858127594672917
                   55314682518714528569231404359845775746985748039345677748
                   24230985421074605062371141877954182153046474983581941267
                   39876755916554394607706291457119647768654216766042983165
                   2624386837205668069376
        Sum of digits: 1366
**/

#include <iostream>
#include <vector>
#include <algorithm>

typedef unsigned short int usi;


void print_vector(std::vector<usi> &vec)
{
    std::vector<usi>::iterator it;
    for (it = vec.begin(); it != vec.end(); ++it)
        std::cout << *it;

    return;
}


std::vector<usi> multiply (std::vector<usi> &a , std::vector<usi> &b)
{
    // Construct a vector to hold the result:
    std::vector<usi> result;
    for (usi n = 1 ; n <= (a.size()+1)*(b.size()+1) ; n++)
        result.push_back(0);
    
    // Carryout the multiplication:
    usi carry_over, temp_value;
    usi aidx, bidx, idx;
    aidx = 0;
    for (std::vector<usi>::reverse_iterator ait = a.rbegin() ; ait != a.rend() ; ++ait) {
        carry_over = 0;
        bidx = 0;
        for (std::vector<usi>::reverse_iterator bit = b.rbegin() ; bit != b.rend() ; ++bit) {
            idx = aidx+bidx;
            temp_value = result[idx] + (*ait) * (*bit) + carry_over; 
            result[idx] = temp_value % 10;
            carry_over = temp_value / 10;
            bidx++;
        } 
        while (carry_over != 0) {
            idx++;
            result[idx] = (carry_over % 10);
            carry_over /= 10;
        }
        aidx++;
    }
    
    // Remove left zeros:
    std::vector<usi>::reverse_iterator rit = result.rbegin();
    idx = 0;
    while (*rit == 0) {
        idx++;
        ++rit;
    }
    result.erase((result.end() - idx), result.end());

    // Reverse the vector:
    std::reverse(result.begin(), result.end());
    
    // // Uncomment to see what is happening...
    // std::cout << std::endl << std::endl;
    // print_vector(a);
    // std::cout << " x ";
    // print_vector(b);
    // std::cout << " = ";
    // print_vector(result);
    // std::cout << std::endl;

    return result;
}


int main()
{
    const usi base = 2;
    const usi exponent = 1000;
    std::vector<usi> vec;
    vec.push_back(base);
  
    std::vector<usi> temp = vec;
  
    for (usi i = 1 ; i < exponent ; i++)
        vec = multiply(vec , temp);
  
    usi sum_digits = 0;
    std::cout << base << " ^ " << exponent << " = ";
    for (std::vector<usi>::iterator it = vec.begin() ; it != vec.end() ; it++)
    {
        std::cout << *it;
        sum_digits += *it;
    }
    std::cout << std::endl;
    std::cout << "Sum of digits: " << sum_digits << std::endl;

    return 0;
}
