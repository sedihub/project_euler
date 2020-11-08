/*
PROBLEM:
  By starting at the top of the triangle below and moving to adjacent numbers on the row below,
  the maximum total from top to bottom is 23.

           3
          7 4
         2 4 6
        8 5 9 3

  That is, 3 + 7 + 4 + 9 = 23.

  Find the maximum total from top to bottom in triangle.txt a 15K text file containing a triangle 
  with one-hundred rows.


SOLUTION:
  See the solution of problem 18.

  ANSWER: 7273
**/

#include <iostream>
#include <sstream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>

int main()
{
  // // Create a 2D array;
  unsigned int num_triangle_rows = 100;
  unsigned int** triangle = new unsigned int*[100];
  for (unsigned int i = 0; i < 100; i++){
    triangle[i] = new unsigned int[i+1];
  }

  std::ifstream file("./p067_triangle.txt");
  std::string   str; 
  std::stringstream ss;
  unsigned int r,c;
  r = 0;
  while (std::getline(file, str))
  {
    //std::cout << str << std::endl;
    ss.clear();
    ss.str(str);
    c = 0;
    while( c <= r && !(ss.fail()) )
    {
      ss >> triangle[r][c];
      c++;
    }
    r++;
  }

  // // Print Results
  // for (unsigned int i = 0; i < num_triangle_rows; i++) {
  //   for (unsigned int j = 0; j <= i; j++) {
  //     std::cout << triangle[i][j] << " ";
  //   }
  //   std::cout << std::endl;
  // }

  // Compute Maximum sum path:
  for (unsigned int i = (num_triangle_rows - 1); i > 0; i--) {
    for (unsigned int j = 0; j <= (i - 1); j++) {
      triangle[i - 1][j] += std::max(triangle[i][j], triangle[i][j + 1]);
    }
  }

  std::cout << "------------------" << std::endl;
  std::cout << "Max path sum: " << triangle[0][0] << std::endl;

  // Clean up:
  for( unsigned int i = 0 ; i < 100 ; i++ )
  {
    delete[] triangle[i];
  }
  delete[] triangle;

  return 0;
}
