/*
PROBLEM:
  Euler 081
  In the 5 by 5 matrix below, the minimal path sum from the top left to the bottom right, by 
  only moving to the right and down, is indicated in bold red and is equal to 2427.

            [see euler_081](https://projecteuler.net/problem=81)

  Find the minimal path sum from the top left to the bottom right by only moving right and down 
  in matrix.txt (right click and "Save Link/Target As..."), a 31K text file containing an 80 by 
  80 matrix.


SOLUTION:
  Look at the m_{2, 2} element of the example 5x5 matrix. If we were to compute the minimal path 
  sum from the top left corner (m_{1, 1}) to this element, by only moving right and down, we'd
  add the first element to its right neighbor and its bottom neighbor. Then the minimal path sum
  to $m_{2, 2}$ would be the minimum of these two. Thus we could iteratively reduce the size of 
  the matrix. Note that, this way we only obtain the minimal path sum. If we where to find them
  path itself, we would have to keep track of the "min" points.

  In this case, the matrix is square. A natural question to ask is whether this approach extends
  to rectangular grids/matrices. Upon a closer look, one can convince themselves that it does.
  This can be seen in the solution below. You can reduce the number of rows or columns to emulate
  this using a sub-matrix instead of the whole 80x80 matrix.u

  ANSWER: Minimal Path Sum: 427337
**/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream> 
#include <iomanip>
#include <cmath>


typedef unsigned int uint;


int main() 
{ 
  // Number of rows and column of the matrix:
  const uint NUM_ROWS = 80;
  const uint NUM_COLS = 80;

  // Create an array to store the matrix:
  uint** matrix = new uint*[NUM_ROWS];
  for (uint row_idx = 0; row_idx < NUM_ROWS; row_idx++) {
    matrix[row_idx] = new uint[NUM_COLS];
  }

  // Load matrix from the text file:
  std::ifstream file("./p081_matrix.txt");
  std::string line; 
  std::stringstream str_strm; 
  uint row_idx, col_idx, temp_int;
  row_idx = 0;
  while (std::getline(file, line) && row_idx < NUM_ROWS) {
    col_idx = 0;
    str_strm.clear();
    str_strm.str(line);
    // std::cout << line << std::endl;
    while (str_strm >> temp_int && col_idx < NUM_COLS) {
      // std::cout << std::setw(5) << temp_int << " ";
      matrix[row_idx][col_idx] = temp_int;
      col_idx++;
      if (str_strm.peek() == ',') {
        str_strm.ignore();  // Ignore ','...
      }
    } 
    // std::cout << std::endl;
    row_idx++;
  }

  // First, take we need to handle the first row and the first column:
  for (uint row_idx = 1; row_idx < NUM_ROWS; row_idx++) {
    matrix[row_idx][0] += matrix[row_idx - 1][0];
  }
  for (uint col_idx = 1; col_idx < NUM_COLS; col_idx++) {
    matrix[0][col_idx] += matrix[0][col_idx - 1];
  }

  // Now, we can move on to the rest of the matrix:
  for (uint row_idx = 1; row_idx < NUM_ROWS; row_idx++) {
    for (uint col_idx = 1; col_idx < NUM_COLS; col_idx++) {
      matrix[row_idx][col_idx] += std::min(
        matrix[row_idx - 1][col_idx], 
        matrix[row_idx][col_idx - 1]);
    }
  }

  // for (uint m = 1; m < NUM_ROWS; m++) {
  //   matrix[m][0] += matrix[m-1][0];
  //   for (uint r = 1; r < m; r++) {
  //     matrix[m][r] += std::min(
  //       matrix[m][r - 1], 
  //       matrix[m - 1][r]);
  //   }
    
  //   matrix[0][m] += matrix[0][m - 1];
  //   for (uint c = 1; c < m; c++) {
  //     matrix[c][m] += std::min(
  //       matrix[c - 1][m], 
  //       matrix[c][m - 1]);
  //   }
    
  //   matrix[m][m] += std::min(
  //     matrix[m][m - 1], 
  //     matrix[m-1][m]);
  // }

  std::cout << "Minimal Path Sum: " 
            << matrix[NUM_ROWS - 1][NUM_COLS - 1] 
            << std::endl;


  // Clean up...
  for (uint row_idx = 0; row_idx < NUM_ROWS; row_idx++) {
    delete[] matrix[row_idx];
  }
  delete[] matrix;

  return 0;
}
