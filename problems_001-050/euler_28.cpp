/*
PROBLEM:
    Starting with the number 1 and moving to the right in a clockwise direction a 5 by 5 spiral
    is formed as follows:

            21 22 23 24 25
            20  7  8  9 10
            19  6  1  2 11
            18  5  4  3 12
            17 16 15 14 13

    It can be verified that the sum of the numbers on the diagonals is 101.

    What is the sum of the numbers on the diagonals in a 1001 by 1001 spiral formed in the 
    same way?


SOLUTION:
    For even n values, the diagonals are given by the following formulas:
        
        lr(1) = 1, 
        ll(1) = ul(1) = ur(1) = 0
        
        lr(n) = lr(n - 2) + 3*(n - 3) + n - 1 = lr(n - 2) + 4*n - 10
        ll(n) = lr(n) + (n - 1)
        ul(n) = ll(n) + (n - 1) = lr(n) + 2(n - 1)
        ur(n) = ul(n) + (n - 1) = lr(n) + 3(n - 1)

    At each n, the sum of diagonal corners is given by:

        sum(n) = 4*lr(n) + 6*(n - 1)

    The total sum of diagonals is given by:

        sum = 1 + sum_{k=1}^{(N-1)/2} (4 * lr(2k+1) + 6(2k + 1 - 1))
            = 1 + 4 sum_{k=1}^{(N-1)/2} lr(2k+1) + 12((N-1)/2) * ((N-1)/2 + 1) / 2
            = 1 + 6K(K+1) + 4 sum_{k=1}^{(N-1)/2} lr(2k+1)

    where K = (N - 1)/2. For the last term, we need to simplify lr(n). Let's write it in
    k = (n-1)/2:

        lr(2k+1) = lr(2k-1) + 8k - 6
        lr(2k+1) = lr(1) + sum_{i=1}^{k} (8k - 6)
                 = 1 - 6k + 4k(k + 1) = 4k^2 - 2k + 1
    Thus,

        4 sum_{k=1}^{K} lr(2k+1) = 4 (K - K(K + 1) + 4 sum_{1}^{K} K^2)
                                 = 16 sum_{1}^{K} K^2 - 4K^2
                                 = 8K(K+1)(2K+1)/3 - 4K^2

    Finally, we find the following close expression for the sum of the diagonals:
    
        sum = 1 + 6K^2 + 6K - 4K^2 + 8K(K+1)(2K+1)/3
            = 1 + 2K^2 + 6K + 8K(K+1)(2K+1)/3


    Answer: 669171001
**/


#include <iostream>


int main() {
    unsigned int k = 500;
    unsigned int sum = 1 + 2*k*k + 6*k + 8*(k*(k+1)*(2*k+1))/3;

    std::cout << "Sum: " << sum << std::endl;

    return 0;
}
