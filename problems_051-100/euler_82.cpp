/*
PROBLEM:
  Euler 082
  The minimal path sum in the 5 by 5 matrix below, by starting in any cell in the left column and
  finishing in any cell in the right column, and only moving up, down, and right, is indicated in
  red and bold; the sum is equal to 994.

        [Euler_082](https://projecteuler.net/problem=82)
 
  Find the minimal path sum from the left column to the right column in matrix.txt (right click 
  and "Save Link/Target As..."), a 31K text file containing an 80 by 80 matrix.


SOLUTION:
  The aspect that complicates this case compared to the last one (euler_081) is the non-locality
  of the solution: The minimal path sum is not the one that is composed of the shortest steps.

  The way I originally solved this problem was by systematically exploring all path sums: I'd 
  find the minimal path sum matrix from elements of each column to the one after. Then I'd update
  this matrix. The inefficiency of this approach stems from the fact that we will compute all
  possibility including the maximal one(s). 

  This problem can be solved using a modified (constrained) version of Dijkstra's algorithm. The
  reason that this is the most efficient way of solving the problem is that we will avoid any
  unnecessary computation. For this, we can utilize std::multimap, which, when iterated over. We
  will also need a container to keep track of the nodes that we have already visited. There is
  one last situation that we need to take care of: The nodes we will update may have been already 
  reached through a another path. To handle this, we need another std::set that keeps track of
  active nodes. If we encounter an active node, we will update its path sum using min.

  Finally, note that this approach (a path-sum-prioritized search as opposed to the brute-force
  depth-fist search) is agnostic to starting from a specific point or a set of points. Once the
  termination criterion is met (in this case, reaching the last column) it will return the minimal
  path sum. 

  ANSWER: Shortest path sum is: 260324, terminating at (22, 79)
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
  std::ifstream file("./p082_matrix.txt");
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

  // Define a map from path sums to indices and initialize with the first column:
  typedef std::pair<uint, uint> IdxPair;
  typedef std::pair<uint, IdxPair> MapPair;
  std::multimap<uint, IdxPair> paths;
  std::set<IdxPair> visited_nodes;
  std::set<IdxPair> active_nodes;
  for (uint row_idx = 0; row_idx < NUM_ROWS; row_idx++) {
    paths.insert(MapPair(matrix[row_idx][0], IdxPair(row_idx, 0)));
    visited_nodes.insert(IdxPair(row_idx, 0)); // The path starts from the first column!
  }

  // Now let's find the minimal path sum:
  uint current_sum, temp;
  IdxPair current_node, top_node, bottom_node, right_node;
  std::map<uint, IdxPair>::iterator mit;
  while (paths.size() > 0) {
    // Start with the node with the least path sum so far:
    mit = paths.begin();
    current_sum = mit->first;
    current_node = mit->second;
    if (current_node.second == (NUM_COLS - 1)) {
      std::cout << "Shortest path sum is: " << current_sum 
                << ", terminating at (" 
                << current_node.first 
                << ", " 
                << current_node.second 
                << ")" << std::endl;
      break;
    }

    // Pop the current node:
    paths.erase(mit);
    if (active_nodes.find(current_node) != active_nodes.end()) {
      active_nodes.erase(current_node);
    }
    visited_nodes.insert(current_node);

    // Add top node (if has one):
    if (current_node.first > 0) {
      top_node.first = current_node.first - 1;
      top_node.second = current_node.second;
      // If already visited, no need to do anything...
      if (visited_nodes.find(top_node) == visited_nodes.end()) {
        temp = matrix[top_node.first][top_node.second];
        temp += current_sum;
        // If active, we need to take the min of paths leading to it.
        if (active_nodes.find(top_node) != active_nodes.end()) {
          std::map<uint, IdxPair>::iterator it;
          for (it = paths.begin(); it != paths.end(); it++) {
            if (it->second == top_node) { 
              temp = std::min(it->first, temp);
              // With multimap, we have to erase and insert a new pair...
              paths.erase(it);
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
    }

    // Add right node:
    right_node.first = current_node.first;
    right_node.second = current_node.second + 1;
    // If already visited, no need to do anything...
    if (visited_nodes.find(right_node) == visited_nodes.end()) {
      temp = matrix[right_node.first][right_node.second];
      temp += current_sum;
      // If active, we need to take the min of paths leading to it.
      if (active_nodes.find(right_node) != active_nodes.end()) {
        std::map<uint, IdxPair>::iterator it;
        for (it = paths.begin(); it != paths.end(); it++) {
          if (it->second == right_node) { 
            temp = std::min(it->first, temp);
            // With multimap, we have to erase and insert a new pair...
            paths.erase(it);
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

    // Add bottom node (if has one):
    if (current_node.first < NUM_ROWS - 1) {
      bottom_node.first = current_node.first + 1;
      bottom_node.second = current_node.second;
      // If already visited, no need to do anything...
      if (visited_nodes.find(bottom_node) == visited_nodes.end()) {
        temp = matrix[bottom_node.first][bottom_node.second];
        temp += current_sum;
        // If active, we need to take the min of paths leading to it.
        if (active_nodes.find(bottom_node) != active_nodes.end()) {
          std::map<uint, IdxPair>::iterator it;
          for (it = paths.begin(); it != paths.end(); it++) {
            if (it->second == bottom_node) { 
              temp = std::min(it->first, temp);
              // With multimap, we have to erase and insert a new pair...
              paths.erase(it);
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
    }
  }

  // Clean up...
  for (uint row_idx = 0; row_idx < NUM_ROWS; row_idx++) {
    delete[] matrix[row_idx];
  }
  delete[] matrix;

  return 0;
}
