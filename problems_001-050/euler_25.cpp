/*
PROBLEM:
  The Fibonacci sequence is defined by the recurrence relation:

    F_n = F_{n-1} + F_{n-2}
    F_1 = F_1 = 2

  What is the index of the first term in the Fibonacci sequence to contain 1000 digits?


SOLUTION:
  We need an arbitrary-precision summation. For this, I will use a class and overload the
  `+` operator; 
  
  ANSWER: 
    F_{4782} = 
    1070066266382758936764980584457396885083683896632151665013235203375314520604694040621
    8891475824897926578046948881775919574843364666725699595129960304612627480924821861440
    6943305123477444275027378175308757939166619214925918675955396642283714894311307469950
    3439547001985432609723067290192870526447243726117715821825548491120525013201478612965
    9313817922355596574520395061375514678375432291196021299340482607061753977068470682028
    9548690266618543512452190036948064135744747091170761976694569107009802439343961747410
    3736912503231365532164773697023167755051595173518460579954919410967778373229665796581
    6465139034881542563101842241902598460880001101862555502454939371136516570394476295847
    1454852342595042858242530608354443542821261100899286379504800689433030977321783486454
    3113205765659868456288616808718693835297350643986297640660000723562917905207051164077
    6148124918858309459405666883391093509444565763576661516193177537928916615813271596168
    77487983821820492520348473874384736771934512787029218636250627816 

    (1000 digits)

  There is a more elegant solution that requires knowing the following property:

    f_n = round( \phi^n / \sqrt(5) )

  (https://mathworld.wolfram.com/FibonacciNumber.html).
**/

#include <iostream>
#include <vector>
#include <iterator>
#include <iomanip>


class LargeUInt
{
public:
  LargeUInt () {}

  LargeUInt(unsigned int n)
  {
    while (n > 0) {
      num.push_back('0' + (char)(n % 10));
      n /= 10;
    }
  }

  LargeUInt(const LargeUInt& n)
  {
    num.clear();
    if (n.num.empty()) {
      return;
    }
    std::vector<char>::const_reverse_iterator crit;
    for (crit = n.num.rbegin(); crit != n.num.rend(); crit++)
      this->num.push_back(*crit);
  }

  unsigned int num_digits()
  {
    return num.size();
  }

  friend std::ostream& operator << (std::ostream&, const LargeUInt&);
  friend LargeUInt operator + (const LargeUInt&, const LargeUInt&);

private:
  std::vector<char> num;
  std::vector<char>::reverse_iterator rit;

};


std::ostream& operator << (std::ostream& os, const LargeUInt& n)
{
  std::vector<char>::const_reverse_iterator crit;
  for (crit = n.num.rbegin(); crit != n.num.rend(); crit++){
    os << *crit;
  }
  return os;
}


LargeUInt operator + (const LargeUInt& a, const LargeUInt& b) 
{
  std::vector<char>::const_iterator a_it = a.num.begin();
  std::vector<char>::const_iterator b_it = b.num.begin();
  LargeUInt result;
  unsigned int carry_over = 0;
  unsigned int temp;
  while (a_it != a.num.end() && b_it != b.num.end()) {
    temp = (unsigned int)(*a_it - '0') + (unsigned int)(*b_it - '0') + carry_over; 
    result.num.push_back('0' + (char)(temp % 10));
    carry_over = temp / 10;
    a_it++;
    b_it++;
  }
  while (a_it != a.num.end()) {
    temp = (unsigned int)(*a_it - '0') + carry_over;
    result.num.push_back('0' + (char)(temp % 10));
    carry_over = temp / 10;
    a_it++;
  }
  while (b_it != b.num.end()) {
    temp = (unsigned int)(*b_it - '0') + carry_over;
    result.num.push_back('0' + (char)(temp % 10));
    carry_over = temp / 10;
    b_it++;
  }
  while (carry_over != 0) {
    result.num.push_back('0' + (char)(carry_over % 10));
    carry_over /= 10;
  }

  return result;
}


int main()
{
  const unsigned int target_num_digits = 1000;

  LargeUInt f_nm1(1);
  LargeUInt f_nm2(1);
  unsigned int idx = 2;
  LargeUInt f_n;

  while (f_n.num_digits() < target_num_digits) {
    f_n = f_nm1 + f_nm2;
    f_nm2 = f_nm1;
    f_nm1 = f_n;
    idx++;
    std::cout << "\t" << std::setw(4) << idx << ": " << f_n << std::endl;
  }

  std::cout << "F_{" << idx << "} = " << f_n 
            << "\t(" << f_n.num_digits() << " digits)" << std::endl;

  return 0;
}
