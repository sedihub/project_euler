/*
PROBLEM:
  The series, 1^1 + 2^2 + 3^3 + ... + 10^10 = 10405071317.

  Find the last ten digits of the series, 1^1 + 2^2 + 3^3 + ... + 1000^1000.


SOLUTION:
  Let's do it. This is a question of moduli. I can probably do this a bit more efficiently.
  Instead, I will do it using my custom arbitrary-precision integer decimal representation
  using std::vector.

  ANSWER: 9 1 1 0 8 4 6 7 0 0
**/

#include "iostream"
#include "cmath"
#include "vector"
#include "iterator"


typedef std::vector<unsigned int> uint_vec_type;
typedef std::vector<unsigned int>::iterator uint_vec_iterator_type;
typedef std::vector<unsigned int>::const_iterator uint_const_vec_iterator_type;


template<typename T> void print_vector(const std::vector<T> &vec, bool reverse=false)
{
  std::cout << "\t";
  if (reverse) {
    typename std::vector<T>::const_reverse_iterator rit;
    for (rit = vec.rbegin(); rit != vec.rend(); rit++)
      std::cout << *rit << " ";
  }
  else {
    typename std::vector<T>::const_iterator it;
    for (it = vec.begin(); it != vec.end(); it++)
      std::cout << *it << " ";
  }
  std::cout << std::endl;
}



void num_to_digits_vect(unsigned long int n, uint_vec_type &vec)
{
  vec.clear();
  while (n > 0) {
    vec.push_back(n % 10);
    n /= 10;
  }
}



uint_vec_type multiply(const uint_vec_type &a, const uint_vec_type &b)
{
  uint_vec_type res;
  for (unsigned int i = 0 ; i < a.size() + b.size() + 2; i++ )
    res.push_back(0);

  unsigned int carry_over = 0;
  unsigned int idx;
  for (uint_const_vec_iterator_type ait = a.begin(); ait != a.end(); ait++) {
    for (uint_const_vec_iterator_type bit = b.begin(); bit != b.end(); bit++){
      idx = std::distance(a.begin(),ait) + std::distance(b.begin(),bit);
      res[idx] += carry_over + (unsigned int)(*ait) * (unsigned int)(*bit);
      carry_over = res[idx] / 10;
      res[idx] = res[idx] % 10; 
    }
    while (carry_over > 0) {  
      idx++;
      res[idx] += carry_over;
      carry_over = res[idx] / 10;
      res[idx] = res[idx] % 10; 
    }
  }

  uint_vec_iterator_type resIt = res.end() - 1;
  while (*resIt == 0) {
    res.erase(resIt);
    resIt = res.end()-1;
  }

  return res; 
}


uint_vec_type sum_vecs(const uint_vec_type &a, const uint_vec_type &b)
{
  uint_vec_type res;
  unsigned int carry_over = 0;

  uint_const_vec_iterator_type ait = a.begin();
  uint_const_vec_iterator_type bit = b.begin();
  while (ait != a.end() && bit != b.end()) {
    carry_over += (*ait) + (*bit);
    res.push_back(carry_over % 10);
    carry_over /= 10;
    ait++;
    bit++;
  }
  while (ait != a.end()) {
    carry_over += (*ait);
    res.push_back(carry_over % 10);
    carry_over /= 10;
    ait++;
  }
  while (bit != b.end()) {
    carry_over += (*bit);
    res.push_back(carry_over % 10);
    carry_over /= 10;
    bit++;
  }

  uint_vec_iterator_type resIt = res.end()-1;
  while (*resIt == 0) {
    res.erase(resIt);
    resIt = res.end() - 1;
  }

  return res; 
}


int main()
{
  uint_vec_type num;
  uint_vec_type pow;
  uint_vec_type sum;

  unsigned int p;
  for (unsigned int n = 1 ; n <= 1000; n++){
    if (n % 10 == 0 && n >= 10) 
      continue;
    num_to_digits_vect(n, num);
    p = 1;
    pow.clear();
    pow.push_back(1);
    while (p <= n) {
      pow = multiply(pow, num);
      p++;
      if (pow.size() > 10){ 
        pow.erase(pow.begin()+10 , pow.end()); // Only keep the last 10 digits.
      }
    }
    std::cout << n << std::endl;
    sum = sum_vecs(sum, pow);
  }
  std::cout << "Sum of the last ten digits: ";
  print_vector<unsigned int>(sum, true);

  return 0;
}
