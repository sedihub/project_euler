/*
PROBLEM:
  The primes 3, 7, 109, and 673, are quite remarkable. By taking any two primes and concatenating
  them in any order the result will always be prime. For example, taking 7 and 109, both 7109 and
  1097 are prime. The sum of these four primes, 792, represents the lowest sum for a set of four
  primes with this property.

  Find the lowest sum for a set of five primes for which any two primes concatenate to produce 
  another prime.

SOLUTION:
  First we note that all the five primes should be either of the form (3k + 1) or (3k + 2) or else
  their concatonation will be divisible by 3. 3 itself can be in both groups.

  Second, 2 and 5 cannot be in any of the two groups.

  Finally and perhaps most important of all, we only need to keep track of fully-connected (a.k.a.
  dense) clusters.

  Note: I yet to convince my self that this way of searching will yield the lowest-sum set of
  primes...

  ANSWER: 26033 = sum(5701, 13, 5197, 6733, 8389)
**/

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

typedef unsigned long int ulint;


bool is_prime(ulint n)
{
  if (n == 2) return true;
  else if (n == 3) return true;
  else if (n == 5) return true;
  else if (n % 2 == 0) return false;
  else if (n % 3 == 0) return false;
  else if (n % 5 == 0) return false;

  ulint k = 6;
  while (k * k <= n) {
    if (n % (k + 1) == 0) return false;
    if (n % (k + 5) == 0) return false;
    k += 6;
  }
  return true;
}


unsigned long int concatenate(ulint n1, ulint n2)
{
  ulint temp = n2;
  while (temp > 0) {
    n1 *= 10;
    temp /= 10;
  }
  n2 += n1;
  return n2;
}


bool are_concatenate_prima_pair(ulint n1, ulint n2)
{
  if (!is_prime(concatenate(n1, n2))) return false;
  if (!is_prime(concatenate(n2, n1))) return false;
  return true;
}


class Node
{
public:
  Node(ulint val)
  {
    node_val = val;
  }

  void add_neighbor(Node *n_ptr)
  {
    this->neighbors.insert(n_ptr);
    n_ptr->neighbors.insert(this);
  }

  void print_neighbors()
  {
    std::set<Node*>::iterator it;
    std::cout << "[" << node_val << "]: ";
    for (it = neighbors.begin(); it != neighbors.end(); it++)
      std::cout << (*it)->node_val << " ";
    std::cout << std::endl;
  }

  friend class Graph;

private:
  ulint node_val;
  std::set<Node*> neighbors;
};


class Graph
{
public:
  Graph(ulint cluster_size) 
  {
    target_cluster_size = cluster_size;
    clusters.clear();
  }

  ~Graph() 
  {
    std::vector<Node*>::iterator node_it;
    for (node_it = nodes.begin(); node_it != nodes.end(); node_it++) {
      delete *node_it;
    }
  }

  void initialize(ulint val)
  {
    nodes.push_back(new Node(val));
  }

  bool insert_and_check_cluster_size(ulint val)
  {
    Node* node_ptr = new Node(val);

    // Update current nodes' adjacency:
    std::vector<Node*>::iterator node_it;
    for (node_it = nodes.begin(); node_it != nodes.end(); node_it++) {
      if (are_concatenate_prima_pair(node_ptr->node_val, (*node_it)->node_val)) {
        // std::cout << "\t" << node_ptr->node_val << " <--> " << (*node_it)->node_val << std::endl;
        (*node_it)->add_neighbor(node_ptr);
      }
    }

    // Update and check clusters:
    if(update_clusters_and_checks(node_ptr)) {
      return true;
    }

    // Find new clusters:
    std::map<Node*, bool> visited;  // To avoide "double checking"!
    for (node_it = nodes.begin(); node_it != nodes.end(); node_it++) {
      if (visited.find(*node_it) != visited.end()) {
        continue;
      }
      else if ((*node_it)->neighbors.find(node_ptr) == (*node_it)->neighbors.end()) {
        visited[*node_it] = true;
        continue;
      }
      else {
        visited[*node_it] = true;
        std::set<Node*>::iterator neighbors_it;
        for (neighbors_it = (*node_it)->neighbors.begin(); 
             neighbors_it != (*node_it)->neighbors.end(); 
             neighbors_it++) {
          if (*neighbors_it == *node_it) {
            continue;
          }
          else if (visited.find(*neighbors_it) != visited.end()) {
            continue;
          }
          else if ((*neighbors_it)->neighbors.find(node_ptr) != (*neighbors_it)->neighbors.end()) {
            // std::cout << "{" << node_ptr->node_val << "}, ";
            // std::cout << "{" << (*node_it)->node_val << "}, ";
            // std::cout << "{" << (*neighbors_it)->node_val << "}" << std::endl;
            clusters.push_back(std::vector<Node*>{node_ptr, *node_it, *neighbors_it});
          }
        }
      }
    }

    // Add the new node:
    nodes.push_back(node_ptr);

    // Finally, update the old clusters:
    return false;
  }

  ulint size()
  {
    return nodes.size();
  }

  void print_nodes()
  {
    std::vector<Node*>::iterator node_it;
    for (node_it = nodes.begin(); node_it != nodes.end(); node_it++) {
      (*node_it)->print_neighbors();
    }
  }

protected:
  bool update_clusters_and_checks(Node* n_ptr)
  {
    std::vector<Node*>::iterator node_it;
    std::vector< std::vector<Node*> >::iterator cluster_it;
    bool fully_connected;
    for (cluster_it = clusters.begin(); cluster_it != clusters.end(); cluster_it++) {
      // std::cout << "[" << n_ptr->node_val << "] -> "; print_cluster(*cluster_it);
      for (node_it = cluster_it->begin(); node_it != cluster_it->end(); node_it++) {
        if ((*node_it)->neighbors.find(n_ptr) == (*node_it)->neighbors.end()) {
          // (*node_it)->print_neighbors();
          fully_connected = false;
          break;
        }
        fully_connected = true;
      }
      if (fully_connected) {
        cluster_it->push_back(n_ptr);
        if (cluster_it->size() == target_cluster_size) {
          print_cluster(*cluster_it);
          return true;
        }
      }
    }
    return false;
  }

  void print_cluster(const std::vector<Node*> &nodes)
  {
    // std::cout << nodes.size() << std::endl;
    std::vector<Node*>::const_iterator it;
    for (it = nodes.begin(); it != nodes.end(); it++)
      std::cout << (*it)->node_val << " ";
    std::cout << std::endl;
  }

private:
  ulint target_cluster_size;
  std::vector<Node*> nodes;
  std::vector< std::vector<Node*> > clusters; // Connected pairs are not considered clusters!
};


int main()
{
  const ulint group_size = 5;

  Graph graph_1(group_size);
  Graph graph_2(group_size);

  graph_1.initialize(3);
  graph_2.initialize(3);


  ulint n = 6;
  while (true) {
    if (is_prime(n + 1)) {
      if(graph_1.insert_and_check_cluster_size(n + 1)) {
        break;
      }
    }

    if (is_prime(n + 5)) {
      if(graph_2.insert_and_check_cluster_size(n + 5)) {
        break;
      }
    }

    n += 6; 
  }

  return 0;
}
