/*
PROBLEM:
  Euler 84
  [Problem 84](https://projecteuler.net/problem=84)

  At the beginning of the game, the CC and CH cards are shuffled. When a player lands on CC or CH they take a card from the top of the respective pile and, after following the instructions, it is returned to the bottom of the pile. There are sixteen cards in each pile, but for the purpose of this problem we are only concerned with cards that order a movement; any instruction not concerned with movement will be ignored and the player will remain on the CC/CH square.

   - Community Chest (2/16 cards):
    1. Advance to GO
    2. Go to JAIL
  
  - Chance (10/16 cards):
    1. Advance to GO
    2. Go to JAIL
    3. Go to C1
    4. Go to E3
    5. Go to H2
    6. Go to R1
    7. Go to next R (railway company)
    8. Go to next R
    9. Go to next U (utility company)
    10. Go back 3 squares.


    00  01  02  03  04  05  06  07  08  09 
    GO  A1  CC1 A2  T1  R1  B1  CH1 B2  B3
 
    10  11  12  13  14  15  16  17  18  19
    JL  C1  U1  C2  C3  R2  D1  CC2 D2  D3
    
    20  21  22  23  24  25  26  27  28  29
    FP  E1  CH2 E2  E3  R3  F1  F2  U2  F3

    30  31  32  33  34  35  36  37  38  39
    GJ  G1  G2  CC3 G3  R4  CH3 H1  T2  H2

  Important squares:
  
      JAIL:   10
      Go2JL:  30

      CC1:    02
      CC2:    17
      CC3:    33

      CH1:    07
      CH2:    22
      CH3:    36


SOLUTION:
  One easy way to solve this problem is to set up the game, and then run Monte Carlo
  simulations.

  There is an interesting question here: Why and how does the number of die faces matter?
  The answer lies in the distribution of squares one can land on in n rolls of a die.  

  ANSWER: Six-digit modal string: 101524
**/


#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <map>
#include <iterator>


typedef unsigned long int ULInt;


class SimplifiedMonopoly
{
public:
  SimplifiedMonopoly()
  {
    this->reset_board();
  }

  void play_n_rounds(ULInt n, ULInt die_size=6)
  {
    this->reset_board();

    ULInt die_1, die_2, chance_card, community_card;
    ULInt num_doubles;
    ULInt sqr = 0;
    while (n > 0) {
      n--;

      // Roll dice:
      die_1 = std::rand() % die_size;
      die_2 = std::rand() % die_size;
      if (die_1 != die_2) {
        num_doubles = 0;
      }
      else {
        num_doubles += 1;
        if (num_doubles == 3) {
          num_doubles = 0;
          sqr = 10;
          board[sqr] += 1;
          continue;
        }
      }

      // Determine the square the player lands on:
      sqr += (die_1 + 1) + (die_2 + 1);
      sqr = sqr % 40;
      if (sqr == 10 || sqr == 30) {
        sqr = 10;
      }
      else if (sqr == 2 || sqr == 17 || sqr == 33) {
        COMUNITY_DECK:;
        community_card = std::rand() % 16;
        if (community_card == 0) {sqr = 0;}
        else if (community_card == 1) {sqr = 10;}
      }
      else if (sqr == 7 || sqr == 22 || sqr == 36) {
        chance_card = std::rand() % 16;
        if (chance_card == 0) {sqr = 0;}
        else if (chance_card == 1) {sqr = 10;}
        else if (chance_card == 2) {sqr = 11;}
        else if (chance_card == 3) {sqr = 24;}
        else if (chance_card == 4) {sqr = 39;}
        else if (chance_card == 5) {sqr =  5;}
        else if (chance_card == 6 || chance_card == 7) {
          if (sqr == 7)       {sqr = 15;}
          else if (sqr == 22) {sqr = 25;}
          else                {sqr =  5;}  // 36
        }
        else if (chance_card == 8) {
          if (sqr == 7)       {sqr = 12;}
          else if (sqr == 22) {sqr = 28;}
          else                {sqr = 12;}  // 36. Next is 12, nearest is 28! 
        }
        else if (chance_card == 9) {
          sqr -= 3;
          if (sqr == 33) {
            goto COMUNITY_DECK;
          }
        }
      }

      board[sqr] += 1;
    }
  }

  std::multimap<double, ULInt> get_results()
  {
    std::multimap<double, ULInt> results;

    double num_rounds = 0.0;
    std::map<ULInt, ULInt>::iterator mit;

    // First count the total number of rounds the game has been played:
    for (mit = board.begin(); mit != board.end(); mit++) {
      num_rounds += (double)mit->second;
    }
    if (num_rounds == 0.0) {num_rounds = 1.0;}  // Avoid division by zero...

    // Compute the probabilities:
    typedef std::pair<double, ULInt> MultiMapPair;
    for (mit = board.begin(); mit != board.end(); mit++) {
      results.insert(MultiMapPair(
        (double)mit->second / num_rounds, mit->first));
    }

    return results;
  }

  void reset_board()
  {
    board.clear();
    for (ULInt idx; idx < 40; idx++) {
      board[idx] = 0; 
    }
  }

private:
  std::map<ULInt, ULInt> board;
};


int main()
{
  const ULInt NUM_TRIALS = 10000000;
  const ULInt NUM_DIE_FACES = 4; //6;
  
  // Set the seed for the RNG engine:
  std::srand(123456789);
  SimplifiedMonopoly game;
  game.play_n_rounds(NUM_TRIALS, NUM_DIE_FACES);

  // Print the square probabilities in ascending order:
  std::multimap<double, ULInt> results = game.get_results();
  std::multimap<double, ULInt>::iterator mit;
  for (mit = results.begin(); mit != results.end(); mit++) {
    std::cout << "\t" << std::setprecision(4) << std::setw(4) 
              << 100.0 * mit->first
              << ": " << std::setfill('0') << std::setw(2) 
              << mit->second << std::endl;
  }
  std::cout << std::endl;


  // Print answer in the six-digit model format:
  mit = results.end();
  mit--;
  std::cout << "Six-digit modal string: "
            << std::setfill('0') << std::setw(2) 
            << mit->second;
  mit--;
  std::cout << std::setfill('0') << std::setw(2) 
            << mit->second;
  mit--;
  std::cout << std::setfill('0') << std::setw(2) 
            << mit->second << std::endl;

  return 0;
}
