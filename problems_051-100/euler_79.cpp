/*
PROBLEM:
  Euler 79
  A common security method used for online banking is to ask the user for three random 
  characters from a passcode. For example, if the passcode was 531278, they may ask for 
  the 2nd, 3rd, and 5th characters; the expected reply would be: 317.

  The text file, keylog.txt, contains fifty successful login attempts.

  Given that the three characters are always asked for in order, analyse the file so as 
  to determine the shortest possible secret passcode of unknown length.


SOLUTION:
  This is a graph-search problem. We first decompose the triples into pairs. These pairs
  are links between nodes. We want to find the shortest path. If there are two instances
  of the same digit, we will have a loop in the graph.

  In the solution below, I have made two assumptions:
    - The directed graph is connected.
    - The directed graph has no cycles.

  In general, these assumptions do not hold. It is, however, not difficult to implement
  them. I will only discuss their implications: If the directed graph contains disjoint
  components, that means we can have multiple shortest possible solutions. The presence 
  of circles indicate that there are two identical digits some distance apart, e.g., the
  case 2*3*745*3*8 where 3 may seem to come before and after 7, 4 and 5. The remedy for
  this is to note that, we have to cut open the cycle.


  ANSWER: 73162890
 **/

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <iterator>
#include <algorithm>


typedef unsigned long int ULInt;
typedef std::vector<ULInt> ULIntVec;
typedef std::set<ULInt> ULIntSet;

struct Node {
  ULInt val;
  std::vector<Node*> inbounds;
  std::vector<Node*> outbounds;
};

int main()
{
  // Read the keylog triples:
  std::ifstream file("./p079_keylog.txt");
  ULInt temp;
  ULIntVec keylogs;
  while (file >> temp) {
    keylogs.push_back(temp);
    // std::cout << "\t" << temp << std::endl;
  }

  // Compile the pairs:
  ULIntSet pairs;
  ULIntSet elements;
  for (ULIntVec::iterator it = keylogs.begin(); it != keylogs.end(); it++) {
    pairs.insert(*it / 10);
    pairs.insert(*it % 100);
    pairs.insert(10 * (*it / 100) + (*it % 10));
    //
    elements.insert(*it % 10);
    elements.insert((*it / 10) % 10);
    elements.insert(*it / 100);
  } 

  // Print the pairs:
  ULInt first_digit = 0;
  for (ULIntSet::iterator it = pairs.begin(); it != pairs.end(); it++) {
    if (*it / 10 != first_digit) {
      std::cout << std::endl;
      first_digit = *it / 10;
      std::cout << "\t" << *it << " ";
    }
    else {
      std::cout << *it << " ";
    }
  }
  std::cout << std::endl;

  // Construct directed graph:
  std::map<ULInt, Node> nodes;
  for (ULIntSet::iterator it = elements.begin(); it != elements.end(); it++) {
    nodes[*it] = Node();
    nodes[*it].val = *it;
  }
  for (ULIntSet::iterator it = pairs.begin(); it != pairs.end(); it++) {
    nodes[*it / 10].outbounds.push_back(&nodes[*it % 10]);
    nodes[*it % 10].inbounds.push_back(&nodes[*it / 10]);
  }


  // Find if the graph is connected:
  // (We assume that it is -- justified a posteriori)

  // Identify the initial node (assuming that there is no circle):
  Node* parent;
  for (ULIntSet::iterator it = elements.begin(); it != elements.end(); it++) {
    if (nodes[*it].inbounds.size() == 0) {
      parent = &nodes[*it];
      break;
    }
  } 

  // Find shortest path that contains all nodes:
  // (We assume that there is no loop in the graph)parent
  std::vector<Node*>::iterator it1, it2;
  std::cout << "Shortest passcode: " << parent->val;
  while (parent != nullptr) {
    std::vector<Node*> not_adjacent;
    for (it1 = parent->outbounds.begin(); it1 != parent->outbounds.end(); it1++) {
      for (it2 = (*it1)->outbounds.begin(); it2 != (*it1)->outbounds.end(); it2++) {
        if (std::find(parent->outbounds.begin(), parent->outbounds.end(), *it2) != parent->outbounds.end()) {
          not_adjacent.push_back(*it2);
        }
      }
    }
    // Find the next node:
    for (it1 = parent->outbounds.begin(); it1 != parent->outbounds.end(); it1++) {
      if (std::find(not_adjacent.begin(), not_adjacent.end(), *it1) == not_adjacent.end()) {
        parent = *it1;
        std::cout << parent->val;
        goto CONT;
      }
    }
    parent = nullptr;
    CONT:;
  }
  std::cout << std::endl;


  return 0;
}
