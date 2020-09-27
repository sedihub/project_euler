/*
PROBLEM:
    Find the maximum total sum from top to bottom of the triangle below:

            75
            95 64
            17 47 82
            18 35 87 10
            20 04 82 47 65
            19 01 23 75 03 34
            88 02 77 73 07 63 67
            99 65 04 28 06 16 70 92
            41 41 26 56 83 40 80 70 33
            41 48 72 33 47 32 37 16 94 29
            53 71 44 65 25 43 91 52 97 51 14
            70 11 33 28 77 73 17 78 39 68 17 57
            91 71 52 38 17 14 91 43 58 50 27 29 48
            63 66 04 68 89 53 67 30 73 16 69 87 40 31
            04 62 98 27 23 09 70 98 73 93 38 53 60 04 23

SOLUTION:
    Start from the bottom and propagete up:

                a1  a2  a3
              b1  b2  b3  b4

    Basically, the idea is that if we are at a1, the maximal path is going to
    include b[argmax(b1, b2)]. We are effectively doing dynamic programming.

    The answer is: 1074 
**/

#include <iostream>  
#include <vector>
#include <iomanip>  // needed for std::setw(...)
#include <algorithm>  // for std::max

typedef unsigned short int usint;

int main()
{
    const usint pyramid_height = 14;
    std::vector< std::vector<usint> > pyramid = {
        {75},
        {95, 64},
        {17, 47, 82},
        {18, 35, 87, 10},
        {20,  4, 82, 47, 65},
        {19,  1, 23, 75,  3, 34},
        {88,  2, 77, 73,  7, 63, 67},
        {99, 65,  4, 28,  6, 16, 70, 92},
        {41, 41, 26, 56, 83, 40, 80, 70, 33},
        {41, 48, 72, 33, 47, 32, 37, 16, 94, 29},
        {53, 71, 44, 65, 25, 43, 91, 52, 97, 51, 14},
        {70, 11, 33, 28, 77, 73, 17, 78, 39, 68, 17, 57},
        {91, 71, 52, 38, 17, 14, 91, 43, 58, 50, 27, 29, 48},
        {63, 66, 04, 68, 89, 53, 67, 30, 73, 16, 69, 87, 40, 31},
        { 4, 62, 98, 27, 23,  9, 70, 98, 73, 93, 38, 53, 60,  4, 23},
    };

    // Traverse the pyramid in reverse (from base to the top):
    std::vector< std::vector<usint> >::reverse_iterator rev_row_it;
    for (rev_row_it = pyramid.rbegin(); rev_row_it != pyramid.rend() - 1; ++rev_row_it) {
        for (usint idx = 0; idx < (rev_row_it + 1)->size(); ++idx) {
            (*(rev_row_it + 1))[idx] += std::max(
                (*rev_row_it)[idx], (*rev_row_it)[idx+1]);
        }
    }

    // Show the result:
    std::vector< std::vector<usint> >::iterator row_it;
    std::vector<usint>::iterator column_it;
    for (row_it = pyramid.begin(); row_it != pyramid.end(); ++row_it){
        for (column_it = row_it->begin(); column_it != row_it->end(); ++column_it) {
            std::cout << std::setw(2) << *column_it << " ";
        }
        std::cout << std::endl;
    }

    return 0;
} 