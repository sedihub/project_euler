/* Euler 68
 6,5,3; 10,3,1; 9,1,4; 8,4,2; 7,2,5
 **/

#include <iostream>
#include <vector>


typedef unsigned int uint;
typedef std::vector<uint> uvec;


// std::vector<uvec> generate_ordered_permutations(
//   std::vector<uvec> prev, uint level, const uint &length, const uint &max)
// {
//   if (level > length) {
//     return prev;
//   }

//   std::vector<uvec> expanded;
//   uvec temp_vec;
//   std::vector<uvec>::iterator it;
//   for (it = prev.begin(); it != prev.end(); it++) {
//     for (uint n = it->back()+1; n <= (max - length + level); n++) {
//       temp_vec = uvec(*it);
//       temp_vec.push_back(n);
//       expanded.push_back(temp_vec);
//     }
//   }
//   return generate_ordered_permutations(expanded, level+1, length, max);
// }


std::vector<uvec> generate_nontrivial_permutations(
  std::vector<uvec> prev, uint level, const uint &length, const uint &max)
{
  if (level > length) {
    return prev;
  }

  std::vector<uvec> expanded;
  uvec temp_vec;
  std::vector<uvec>::iterator vit;
  for (vit = prev.begin(); vit != prev.end(); vit++) {
    for (uint n = 1; n <= max; n++) {
      if (std::find(vit->begin(), vit->end(), n) != vit->end()) {
        continue;
      }
      if (n < (*vit)[0]) {
        continue; 
      }
      temp_vec = uvec(*vit);
      temp_vec.push_back(n);
      expanded.push_back(temp_vec);
    }
  }
  return generate_nontrivial_permutations(expanded, level+1, length, max);
}


bool is_an_ngon_solution(const uint &n_gon, const uvec &outer_nodes, uint arm_sum, uvec &inner_nodes)
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

  uvec::iterator it;
  for (it = inner_nodes.begin(); it != inner_nodes.end(); it++) {
    if (*it < 1 || *it > 2 * n_gon) {
      return false;
    }
    if (std::find(outer_nodes.begin(), outer_nodes.end(), *it) != outer_nodes.end()) {
      return false;
    }
  }

  return true;
}


int main()
{
  const uint n_gon = 5; // This is the only parameter to change:

  const uint max_num = 2 * n_gon;
  const uint sum_one_to_max = n_gon * (max_num + 1);

  std::vector<uvec> perms;
  for (uint n = 1; n <= max_num; n++) {
    perms.push_back(uvec({n}));
  }
  perms = generate_nontrivial_permutations(perms, 2, n_gon, max_num);
  std::vector<uvec>::iterator vit;
  uint sum, arm_sum;
  for (vit = perms.begin(); vit != perms.end(); vit++) {
    sum = 0; 
    std::cout<< "\t";
    for (uvec::iterator it = vit->begin(); it != vit->end(); it++) {
      sum += *it;
      std::cout << *it << " ";
    }
    if ((2 * sum_one_to_max - sum) % n_gon == 0) {
      arm_sum = (2 * sum_one_to_max - sum) / n_gon;
      std::cout << " ---> [" << arm_sum;
      uvec inner_nodes(n_gon);
      if (is_an_ngon_solution(n_gon, *vit, arm_sum, inner_nodes)) {
        std::cout << "]   " ;
        for (uint idx = 0; idx < n_gon - 1; idx++) {
          std::cout << (*vit)[idx] << "," << inner_nodes[idx] << "," << inner_nodes[idx+1] << "; "; 
        }
        std::cout << (*vit)[n_gon - 1] << "," << inner_nodes[n_gon - 1] << "," << inner_nodes[0];
        std::cout << std::endl;
      }
      else {
        std::cout << "]" << std::endl;
      }
    }
    else {
      std::cout << "\r"; // Earse the line...
    }
  }

  // Since the base sequences are generated in lexicographical order, the last solution is the answer!

  return 0;
}
