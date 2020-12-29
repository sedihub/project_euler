/*
PROBLEM:
  [Problem 68](https://projecteuler.net/problem=68)

SOLUTION:
  The solution below reveals why we cannot have magic n-gons with an even n. 
  We break the n-gon into n outer nodes and n inner nodes. The arms will have the arm_sum.
  Since we use the natural numbers {1, 2,... ,2n} to construct the n-gon, we will have the
  following equations:

        \sum_{i=1}^{2n}(2I_{i} + O_{i}) = n arm_sum
                                       = 2 (2n) (2n + 1) /2 - \sum_{i=1}^{2n} O_{i}
  
  Now, given an descending set of n numbers in the range {1, 2, ..., 2n}, we can check if
  these provide a suitable candidate for the outer nodes. If they do, we then try to infer
  the inner nodes by solving an n-by-n matrix of the form:

        m_{i, j} = \delta_{i, j} + \delta_{i, j+1}    (n+1 = 1)

  Such matrices are only invertible for odd n's! This is why we cannot have magic n-gons 
  with even n's.

  Note: This can be made much faster by generating candidates and in descending order and 
  checking them as we go (a depth-first search of sorts)!

  ANSWER: 6 5 3 10 3 1 9 1 4 8 4 2 7 2 5
**/

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>


typedef unsigned int uint;
typedef std::vector<uint> UintVec;


// std::vector<UintVec> generate_ordered_permutations(
//   std::vector<UintVec> prev, uint level, const uint &length, const uint &max)
// {
//   if (level > length) {
//     return prev;
//   }

//   std::vector<UintVec> expanded;
//   UintVec temp_vec;
//   std::vector<UintVec>::iterator it;
//   for (it = prev.begin(); it != prev.end(); it++) {
//     for (uint n = it->back()+1; n <= (max - length + level); n++) {
//       temp_vec = UintVec(*it);
//       temp_vec.push_back(n);
//       expanded.push_back(temp_vec);
//     }
//   }
//   return generate_ordered_permutations(expanded, level+1, length, max);
// }


std::vector<UintVec> generate_nontrivial_permutations(
  std::vector<UintVec> prev, uint level, const uint &length, const uint &max)
{
  if (level > length) {
    return prev;
  }

  std::vector<UintVec> expanded;
  UintVec temp_vec;
  std::vector<UintVec>::iterator vit;
  for (vit = prev.begin(); vit != prev.end(); vit++) {
    for (uint n = 1; n <= max; n++) {
      if (std::find(vit->begin(), vit->end(), n) != vit->end()) {
        continue;
      }
      if (n < (*vit)[0]) {
        continue; 
      }
      temp_vec = UintVec(*vit);
      temp_vec.push_back(n);
      expanded.push_back(temp_vec);
    }
  }
  return generate_nontrivial_permutations(expanded, level+1, length, max);
}


bool is_an_ngon_solution(const uint &n_gon, const UintVec &outer_nodes, uint arm_sum, UintVec &inner_nodes)
{
  if (n_gon == 3) {
    inner_nodes[0] = (arm_sum - outer_nodes[0] + outer_nodes[1] - outer_nodes[2]) / 2;
    inner_nodes[1] = (arm_sum - outer_nodes[0] - outer_nodes[1] + outer_nodes[2]) / 2;
    inner_nodes[2] = (arm_sum + outer_nodes[0] - outer_nodes[1] - outer_nodes[2]) / 2;
  }
  else if (n_gon == 5) {
    inner_nodes[0] = \
    (arm_sum - outer_nodes[0] + outer_nodes[1] - outer_nodes[2] + outer_nodes[3] - outer_nodes[4]) / 2;
    inner_nodes[1] = \
    (arm_sum - outer_nodes[0] - outer_nodes[1] + outer_nodes[2] - outer_nodes[3] + outer_nodes[4]) / 2;
    inner_nodes[2] = \
    (arm_sum + outer_nodes[0] - outer_nodes[1] - outer_nodes[2] + outer_nodes[3] - outer_nodes[4]) / 2;
    inner_nodes[3] = \
    (arm_sum - outer_nodes[0] + outer_nodes[1] - outer_nodes[2] - outer_nodes[3] + outer_nodes[4]) / 2;
    inner_nodes[4] = \
    (arm_sum + outer_nodes[0] - outer_nodes[1] + outer_nodes[2] - outer_nodes[3] - outer_nodes[4]) / 2;
  }
  else {
    std::cout << "ERROR: \"" << n_gon << "\" is neither 3 nor 5!" << std::endl;
    throw;
  }

  // No duplicates in the inner set:
  if (std::unique(inner_nodes.begin(), inner_nodes.end()) != inner_nodes.end()) {
    return false;
  }

  UintVec::iterator it;
  for (it = inner_nodes.begin(); it != inner_nodes.end(); it++) {
    // inner set is in the expected range:
    if (*it < 1 || *it > 2 * n_gon) {
      return false;
    }
    // No overlap with the outer set:
    if (std::find(outer_nodes.begin(), outer_nodes.end(), *it) != outer_nodes.end()) {
      return false;
    }
  }

  return true;
}


int main()
{
  const uint n_gon = 5; // This is the only parameter to change:
  const bool verbose = false;
  const uint max_num = 2 * n_gon;
  const uint sum_one_to_max = n_gon * (max_num + 1);

  UintVec solution;  

  std::vector<UintVec> perms;
  for (uint n = 1; n <= max_num; n++) {
    perms.push_back(UintVec({n}));
  }
  perms = generate_nontrivial_permutations(perms, 2, n_gon, max_num);
  std::vector<UintVec>::iterator vit;
  uint sum, arm_sum;
  for (vit = perms.begin(); vit != perms.end(); vit++) {
    sum = 0; 
    if (verbose) { std::cout<< "\t"; }
    for (UintVec::iterator it = vit->begin(); it != vit->end(); it++) {
      sum += *it;
      if (verbose) { std::cout << *it << " "; }
    }
    if ((2 * sum_one_to_max - sum) % n_gon == 0) {
      arm_sum = (2 * sum_one_to_max - sum) / n_gon;
      if (verbose) { std::cout << " ---> [" << arm_sum; }
      UintVec inner_nodes(n_gon);
      if (is_an_ngon_solution(n_gon, *vit, arm_sum, inner_nodes)) {
        solution.clear();
        if (verbose) { std::cout << "]   " ; }
        for (uint idx = 0; idx < n_gon - 1; idx++) {
          solution.push_back((*vit)[idx]);
          solution.push_back(inner_nodes[idx]);
          solution.push_back(inner_nodes[idx + 1]);
          if (verbose) { 
            std::cout << (*vit)[idx] << "," 
                      << inner_nodes[idx] << "," 
                      << inner_nodes[idx+1] << "; "; 
          }
        }
        solution.push_back((*vit)[n_gon - 1]);
        solution.push_back(inner_nodes[n_gon - 1]);
        solution.push_back(inner_nodes[0]);
        if (verbose) { 
          std::cout << (*vit)[n_gon - 1] << "," 
                    << inner_nodes[n_gon - 1] << "," 
                    << inner_nodes[0] << std::endl;
        }
      }
      else {
        if (verbose) { std::cout << "]" << std::endl; }
      }
    }
    else {
      std::cout << "\r"; // Erase the line...
    }
  }

  // Since the base sequences are generated in lexicographical order, 
  // the last solution is the answer!
  std::cout << "Solution: ";
  for (uint idx = 0; idx < solution.size(); idx++) {
    std::cout << solution[idx] << " ";
  }
  std::cout << std::endl;

  return 0;
}
