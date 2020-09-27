/*
PROBLEM:
    Given the 1000-digit number,
    73167176531330624919225119674426574742355349194934
    96983520312774506326239578318016984801869478851843
    85861560789112949495459501737958331952853208805511
    12540698747158523863050715693290963295227443043557
    66896648950445244523161731856403098711121722383113
    62229893423380308135336276614282806444486645238749
    30358907296290491560440772390713810515859307960866
    70172427121883998797908792274921901699720888093776
    65727333001053367881220235421809751254540594752243
    52584907711670556013604839586446706324415722155397
    53697817977846174064955149290862569321978468622482
    83972241375657056057490261407972968652414535100474
    82166370484403199890008895243450658541227588666881
    16427171479924442928230863465674813919123162824586
    17866458359124566529476545682848912883142607690042
    24219022671055626321111109370544217506941658960408
    07198403850962455444362981230987879927244284909188
    84580156166097919133875499200524063689912560717606
    05886116467109405077541002256983155200055935729725
    71636269561882670428252483600823257530420752963450

    Find the thirteen adjacent digits in the 1000-digit number that have
    the greatest product. What is the value of this product?

SOLUTION:
    Brute froce solution Run a sliding window of the length 13. A better
    solution can be obtained by noticing that windows containing zero will 
    not result in a maximumn.

    The answer is: 23,514,624,000
**/

#include <iostream>  
#include <string>

unsigned long int  product(std::string str_num)
{
    char c = '0';
    unsigned long int  prod = 1;
    for (int i = 0; i < str_num.length(); ++i) {
        prod *= (unsigned long int )(str_num.at(i) - c);
    }

    return prod;
}

int main()
{
    const unsigned long int window = 13;
    std::string number = "";
    number.append("73167176531330624919225119674426574742355349194934");
    number.append("96983520312774506326239578318016984801869478851843");
    number.append("85861560789112949495459501737958331952853208805511");
    number.append("12540698747158523863050715693290963295227443043557");
    number.append("66896648950445244523161731856403098711121722383113");
    number.append("62229893423380308135336276614282806444486645238749");
    number.append("30358907296290491560440772390713810515859307960866");
    number.append("70172427121883998797908792274921901699720888093776");
    number.append("65727333001053367881220235421809751254540594752243");
    number.append("52584907711670556013604839586446706324415722155397");
    number.append("53697817977846174064955149290862569321978468622482");
    number.append("83972241375657056057490261407972968652414535100474");
    number.append("82166370484403199890008895243450658541227588666881");
    number.append("16427171479924442928230863465674813919123162824586");
    number.append("17866458359124566529476545682848912883142607690042");
    number.append("24219022671055626321111109370544217506941658960408");
    number.append("07198403850962455444362981230987879927244284909188");
    number.append("84580156166097919133875499200524063689912560717606");
    number.append("05886116467109405077541002256983155200055935729725");
    number.append("71636269561882670428252483600823257530420752963450");

    //std::cout << number << std::endl;
    std::string max_substring = "";
    unsigned long int  max_product = 0;
    std::string substring;
    unsigned long int  p;
    for (unsigned int idx = 0; idx <= number.length() - window; ++idx) {
        substring = number.substr(idx, window);
        p = product(substring);
        if (p > max_product) {
            max_product = p;
            max_substring = substring;
        }
        // std::cout << "[" << idx << "]\t" << substring << "\t" << p << std::endl;
    }

    std::cout << "\t\"" << max_substring << "\": " << max_product << std::endl;

    return 0;
} 