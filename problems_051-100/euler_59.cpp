/*
PROBLEM:
  Each character on a computer is assigned a unique code and the preferred standard is ASCII
  (American Standard Code for Information Interchange). For example, uppercase A = 65, asterisk
  (*) = 42, and lowercase k = 107.

  A modern encryption method is to take a text file, convert the bytes to ASCII, then XOR each
  byte with a given value, taken from a secret key. The advantage with the XOR function is that
  using the same encryption key on the cipher text, restores the plain text; for example, 65 XOR
  42 = 107, then 107 XOR 42 = 65.

  For unbreakable encryption, the key is the same length as the plain text message, and the key
  is made up of random bytes. The user would keep the encrypted message and the encryption key
  in different locations, and without both "halves", it is impossible to decrypt the message.

  Unfortunately, this method is impractical for most users, so the modified method is to use a
  password as a key. If the password is shorter than the message, which is likely, the key is
  repeated cyclically throughout the message. The balance for this method is using a sufficiently
  long password key for security, but short enough to be memorable.

  Your task has been made easy, as the encryption key consists of three lower case characters. 
  Using [p059_cipher.txt](https://projecteuler.net/project/resources/p059_cipher.txt) (right 
  click and 'Save Link/Target As...'), a file containing the encrypted ASCII codes, and the 
  knowledge that the plain text must contain common English words, decrypt the message and find
  the sum of the ASCII values in the original text.


SOLUTION:
  The idea is to go over each character in the cipher XOR it with another character and requiring
  that the result is a an acceptable character of the natural language.

  ANSWER: 107359, the key is "god".
**/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream> 
#include <vector>

inline bool valid_character(char c)
{
  if (c >= 'a' && c <= 'z' ) return true;
  else if (c >= 'A' && c <= 'Z') return true;
  else if (c >= '0' && c <= '9') return true;
  else if (c == ' ' || c == '.' || c == ','  || c == ':' || 
           c == ';' || c == '\n' || c == '!' || c == '-' || 
           c == '"' || c == '\'' || c == '(' || c == ')' || 
           c == '`' || c == '?' ) return true;
  else return false;
}


int main() 
{ std::vector<char> cipher_vec;
  std::ifstream file("./p059_cipher.txt");
  std::string s; 
  std::stringstream ss;
  unsigned int n;
  while (std::getline(file, s, ',')){
    ss.clear();
    ss.str(s);
    ss >> n;
    cipher_vec.push_back((char)n);
    // // To make sure that I've parsed the cipher correctly:
    // std::cout << (int)cipher_vec.back() << ",";  
  }

  // Find the keys:
  const unsigned int key_length = 3;
  char key[3];
  char c;
  bool not_found;
  unsigned int vec_idx;
  for (unsigned int idx = 0; idx < key_length; idx++) {
    c = 'a';
    NEXT_KEY_CHAR:;
    while (c <= 'z') {
      vec_idx = idx;
      while (vec_idx < cipher_vec.size()) {
        if (!valid_character(c ^ cipher_vec[vec_idx])) {
          c++;
          goto NEXT_KEY_CHAR;
        }
        vec_idx += key_length;
      }
      break; // We have found a key!
    } 
    if (c == '{') std::cerr << "Something went wrong..." << std::endl;
    key[idx] = c;
  }

  // Decipher the message:
  unsigned long int sum_char_vals = 0;
  for (vec_idx = 0; vec_idx < cipher_vec.size(); vec_idx++) {
    cipher_vec[vec_idx] = cipher_vec[vec_idx] ^ key[(vec_idx % 3)]; 
    std::cout << cipher_vec[vec_idx];
    sum_char_vals += (unsigned long int)cipher_vec[vec_idx];
  }
  std::cout << std::endl;
  std::cout << "Sum: " << sum_char_vals << std::endl;
  std::cout << key[0] << ", " << key[1] << ", " << key[2] << std::endl;

  return 0;
}
