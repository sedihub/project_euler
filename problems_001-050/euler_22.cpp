/*
PROBLEM:
  Using names.txt (https://projecteuler.net/project/resources/p022_names.txt), a 46K text file
  containing over five-thousand first names, begin by sorting it into alphabetical order. Then
  working out the alphabetical value for each name, multiply this value by its alphabetical 
  position in the list to obtain a name score.

  For example, when the list is sorted into alphabetical order, COLIN, which is worth 3 + 15 + 
  12 + 9 + 14 = 53, is the 938th name in the list. So, COLIN would obtain a score of 938 × 53 = 
  49714.

  What is the total of all the name scores in the file?


SOLUTION:
  Let's do this!

  ANSWER: 871198282

  NOTE: You need to donwload the text file containing the names: 
        https://projecteuler.net/project/resources/p022_names.txt 
**/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>


unsigned int score(std::string str)
{
  unsigned int score = 0;
  for (unsigned int i = 0; i < str.size(); i++)
     score += (unsigned int)(str[i] - 'A' + 1);

  return score;
}


int main() 
{ 
  // Import the list of names
  std::vector<std::string> list;
  std::ifstream file("./p022_names.txt");
  std::string str; 
  while (std::getline(file, str, ',')){
    str = str.substr (1, (str.size() - 2));  // remove `"' 
    list.push_back(str);
    std::cout << "\t" << str << std::endl;
  }

  // Sort the list
  std::sort(list.begin(), list.end());

  // Compute the score
  unsigned long long int total_name_score = 0;
  std::vector<std::string>::iterator it;
  for (it = list.begin(); it != list.end(); it++){
    total_name_score += (unsigned long long int)(
      score(*it) * (std::distance(list.begin(),it) + 1) 
    );
  }

  std::cout << "Total Score: " << total_name_score << std::endl;

  return 0;
}
