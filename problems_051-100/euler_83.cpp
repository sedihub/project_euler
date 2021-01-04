/*
PROBLEM:
  Euler 083
  In the 5 by 5 matrix below, the minimal path sum from the top left to the bottom right, by
  moving left, right, up, and down, is indicated in bold red and is equal to 2297.

 
Find the minimal path sum from the top left to the bottom right by moving left, right, up, 
and down in matrix.txt (right click and "Save Link/Target As..."), a 31K text file containing
an 80 by 80 matrix.


SOLUTION:
  The way I originally solved this problem was rather interesting, but not very efficient. At 
  the time, I was not familiar with Dijkstra's and A-star algorithms. I will first outline my
  original solution, then explain why A-star is not a suitable algorithm in this case. The
  solution I present is nearly identical to the one in I used in problem 82, with some trivial
  modifications. The rest of the descriptions below is concerned with the way I originally 
  solved this problem that some might find mathematically tantalizing in spite of some of its 
  shortcomings.

  My original solution was a divide-an-concur approach. Here is the idea: split the grid along
  a column, say column c. Consider the symmetric matrix, M, of shortest distances between nodes 
  on the column itself, the vector, V, of the shortest distance from the starting node to the 
  entries of the preceding column, (c - 1). Next, we want to update this pair and advance to 
  the next column, (c + 1). Note that the shortest path in matrix M includes path in the left
  half of the grid.

  Updating the vector is the one that's most straightforward:

      V_{row_idx} = min\{
          V_{row_idx} + node_{row_idx, c}, M^{(c)}_{row_idx, l} + V_{l}
      \}

  As we can see, once the matrix, M, is found updating the vector of path sums is easy. So, all
  that remains to complete the solution is to describe how the matrix M is updated. Note that
  the Matrix has to be updated first: We have the matrix M^{(c - 1)} and want to constrict 
  M^{(c)}:

      M^{(c)}_{r_1, r_2} = min\{
          N_{r_1, r_2}, N_{r_1, l} + M^{(c-1)}_{l, r_2}, 
          N_{r_1, l} + M^{(c-1)}_{l, i} + N_{i, r_2}, ...
      \}
  where N_{r_1, r_2} is a helper matrix of distances between nodes (r_1, c) and (r_2, c) on 
  the column, i.e., simply the inclusive sum of the nodes in on the column in the range 
  (r_1, r_2) of rows. 

  An approximation that I made in the original solution was to truncate the arguments under min 
  to a few terms. Mathematically, the expression for updating the matrix M appears to be the 
  expansion of the closed form.

  Finally, I would like to note that this approach is, in fact, the same approach as in Feynman 
  path integrals.

  ANSWER: 425185
**/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream> 
#include <iomanip>
#include <cmath>
#include <map>
#include <set>
#include <utility>


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
  std::ifstream file("p083_matrix.txt");
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
      // std::cout << std::setw(4) << temp_int << " ";
      matrix[row_idx][col_idx] = temp_int;
      col_idx++;
      if (str_strm.peek() == ',') {
        str_strm.ignore();  // Ignore ','...
      }
    } 
    // std::cout << std::endl;
    row_idx++;
  }

  // Define various containers (active, visited, paths)
  typedef std::pair<uint, uint> IdxPair;
  typedef std::pair<uint, IdxPair> MapPair;
  std::multimap<uint, IdxPair> paths;
  std::set<IdxPair> visited_nodes;
  std::set<IdxPair> active_nodes;

  // Initialize:
  paths.insert(MapPair(matrix[0][0], IdxPair(0, 0)));
  visited_nodes.insert(IdxPair(0, 0)); 
  active_nodes.insert(IdxPair(0, 0)); 

  // Next, let's find the minimal path sum:
  uint current_sum, temp;
  IdxPair current_node, top_node, bottom_node, right_node, left_node;
  const IdxPair TERMINAL_NODE = IdxPair(NUM_ROWS - 1, NUM_COLS - 1);
  std::map<uint, IdxPair>::iterator mit;
  while (paths.size() > 0) {
    // Start with the node with the least path sum so far:
    current_sum = paths.begin()->first;
    current_node = paths.begin()->second;
    // std::cout << "("  << current_node.first
    //           << ", " << current_node.second 
    //           << ") " << current_sum << std::endl;

    // Pop the current node:
    paths.erase(paths.begin());
    active_nodes.erase(current_node);
    visited_nodes.insert(current_node);

    // Top Node:
    if (current_node.first > 0) {
      top_node.first = current_node.first - 1;
      top_node.second = current_node.second;
      // If already visited, no need to do anything...
      if (visited_nodes.find(top_node) == visited_nodes.end()) {
        temp = matrix[top_node.first][top_node.second];
        temp += current_sum;
        // If active, we need to take the min of paths leading to it.
        if (active_nodes.find(top_node) != active_nodes.end()) {
          for (mit = paths.begin(); mit != paths.end(); mit++) {
            if (mit->second == top_node) { 
              temp = std::min(mit->first, temp);
              paths.erase(mit);
              paths.insert(MapPair(temp, top_node));
              break; 
            }
          }
        }
        else {
          paths.insert(MapPair(temp, top_node));
          active_nodes.insert(top_node);
        }
      } 
      // No need to check termination criterion -- cannot be the second last node!
    }

    // Right node:
    if (current_node.second < NUM_COLS - 1) {
      right_node.first = current_node.first;
      right_node.second = current_node.second + 1;
      // If already visited, no need to do anything...
      if (visited_nodes.find(right_node) == visited_nodes.end()) {
        temp = matrix[right_node.first][right_node.second];
        temp += current_sum;
        // If active, we need to take the min of paths leading to it.
        if (active_nodes.find(right_node) != active_nodes.end()) {
          for (mit = paths.begin(); mit != paths.end(); mit++) {
            if (mit->second == right_node) { 
              temp = std::min(mit->first, temp);
              paths.erase(mit);
              paths.insert(MapPair(temp, right_node));
              break; 
            }
          }
        }
        else {
          paths.insert(MapPair(temp, right_node));
          active_nodes.insert(right_node);
        }
      }   
      if (right_node == TERMINAL_NODE) {
        std::cout << "Minimal path sum: " << temp << std::endl;
        break;
      }
    }

    // Bottom node:
    if (current_node.first < NUM_ROWS - 1) {
      bottom_node.first = current_node.first + 1;
      bottom_node.second = current_node.second;
      // If already visited, no need to do anything...
      if (visited_nodes.find(bottom_node) == visited_nodes.end()) {
        temp = matrix[bottom_node.first][bottom_node.second];
        temp += current_sum;
        // If active, we need to take the min of paths leading to it.
        if (active_nodes.find(bottom_node) != active_nodes.end()) {
          for (mit = paths.begin(); mit != paths.end(); mit++) {
            if (mit->second == bottom_node) { 
              temp = std::min(mit->first, temp);
              paths.erase(mit);
              paths.insert(MapPair(temp, bottom_node));
              break; 
            }
          }
        }
        else {
          paths.insert(MapPair(temp, bottom_node));
          active_nodes.insert(bottom_node);
        }
      }  
      if (bottom_node == TERMINAL_NODE) {
        std::cout << "Minimal path sum: " << temp << std::endl;
        break;
      }
    }

    // Left node:
    if (current_node.second > 0) {
      left_node.first = current_node.first;
      left_node.second = current_node.second - 1;
      // If already visited, no need to do anything...
      if (visited_nodes.find(left_node) == visited_nodes.end()) {
        temp = matrix[left_node.first][left_node.second];
        temp += current_sum;
        // If active, we need to take the min of paths leading to it.
        if (active_nodes.find(left_node) != active_nodes.end()) {
          for (mit = paths.begin(); mit != paths.end(); mit++) {
            if (mit->second == left_node) { 
              temp = std::min(mit->first, temp);
              paths.erase(mit);
              paths.insert(MapPair(temp, left_node));
              break; 
            }
          }
        }
        else {
          paths.insert(MapPair(temp, left_node));
          active_nodes.insert(left_node);
        }
      }
      // No need to check termination criterion -- cannot be the second last node!
    }
    // for (mit = paths.begin(); mit != paths.end(); mit++) {
    //   std::cout << "\t(" << mit->second.first << ", " << mit->second.second
    //             << ") "  << mit->first << std::endl; 
    // }
    // std::cout << std::endl;
  }
  // std::cout << "Active Nodes:  " << active_nodes.size() << std::endl;
  // std::cout << "Visited Nodes: " << visited_nodes.size() << std::endl;
  // std::cout << "Paths:         " << paths.size() << std::endl;


  // Clean up...
  for (uint row_idx = 0; row_idx < NUM_ROWS; row_idx++) {
    delete[] matrix[row_idx];
  }
  delete[] matrix;

  return 0;
}
