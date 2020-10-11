/*
PROBLEM:
  In the card game poker, a hand consists of five cards and are ranked, from lowest to highest, in
  the following way:

        High Card: Highest value card.
        One Pair: Two cards of the same value.
        Two Pairs: Two different pairs.
        Three of a Kind: Three cards of the same value.
        Straight: All cards are consecutive values.
        Flush: All cards of the same suit.
        Full House: Three of a kind and a pair.
        Four of a Kind: Four cards of the same value.
        Straight Flush: All cards are consecutive values of same suit.
        Royal Flush: Ten, Jack, Queen, King, Ace, in same suit.

  The cards are valued in the order:
  2, 3, 4, 5, 6, 7, 8, 9, 10, Jack, Queen, King, Ace.

  If two players have the same ranked hands then the rank made up of the highest value wins; for 
  example, a pair of eights beats a pair of fives (see example 1 below). But if two ranks tie, 
  for example, both players have a pair of queens, then highest cards in each hand are compared
  (see example 4 below); if the highest cards tie then the next highest cards are compared, 
  and so on.

  Consider the following five hands dealt to two players:

    Hand       Player 1           Player 2         Winner
      1     5H 5C 6S 7S KD     2C 3S 8S 8D TD     Player 2
      2     5D 8C 9S JS AC     2C 5C 7D 8S QH     Player 1
      3     2D 9C AS AH AC     3D 6D 7D TD QD     Player 2
      4     4D 6S 9H QH QC     3D 6D 7H QD QS     Player 1
      5     2H 2D 4C 4D 4S     3C 3D 3S 9S 9D     Player 1

  The file, poker.txt, contains one-thousand random hands dealt to two players. Each line of the
  file contains ten cards (separated by a single space): the first five are Player 1's cards and
  the last five are Player 2's cards. You can assume that all hands are valid (no invalid 
  characters or repeated cards), each player's hand is in no specific order, and in each hand 
  there is a clear winner.

  How many hands does Player 1 win?


SOLUTION:
  Let's do this! We need a class for hand and an overloaded comparison operator. I will use one
  more calss for the ease of comparing hands.

  For hand type, I use a numerical ordering:

         1  <-->  High Card
         2  <-->  One Pair
         3  <-->  Two Pairs
         4  <-->  Three of a Kind
         5  <-->  Straight
         6  <-->  Flush
         7  <-->  Full House
         8  <-->  Four of a Kind
         9  <-->  Straight Flush
        10  <-->  Royal Flush

  ANSWER: 
**/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>
#include <assert.h>


class PokerHand{
public:
  PokerHand() {}

  PokerHand(
    std::string c1, 
    std::string c2, 
    std::string c3, 
    std::string c4, 
    std::string c5)
  {
    // Sort by card value:
    c1_val = c1[0];
    c1_suit = c1[1];
    //
    c2_val = c2[0];
    c2_suit = c2[1];
    //
    c3_val = c3[0];
    c3_suit = c3[1];
    //
    c4_val = c4[0];
    c4_suit = c4[1];
    //
    c5_val = c5[0];
    c5_suit = c5[1];
    
    // Determine hand rank:
    determine_hand_rank()
  }

  void determine_hand_rank()
  {

    hand_rank = 0;
  }

  friend class Game;
  friend bool operator> (const PokerHand &h1, const PokerHand &h2);
  friend bool operator< (const PokerHand &h1, const PokerHand &h2); 

private:
  char c1_val;
  char c2_val;
  char c3_val;
  char c4_val;
  char c5_val;
  //
  char c1_suit;
  char c2_suit;
  char c3_suit;
  char c4_suit;
  char c5_suit;
  // 
  unsigned int hand_rank;
};


bool operator> (const PokerHand &h1, const PokerHand &h2)
{
  return false;
}


bool operator< (const PokerHand &h1, const PokerHand &h2)
{
  return h2 > h1;
}


class Game{
public:
  Game(std::vector<std::string> hands){
    assert(hands.size() == 10);
    hand1 = PokerHand(hands[0], hands[1], hands[2], hands[3], hands[4]);
    hand2 = PokerHand(hands[5], hands[6], hands[7], hands[8], hands[9]);
  }

  void print()
  {
    std::cout << "\t";
    std::cout << hand1.c1_val << hand1.c1_suit << " ";
    std::cout << hand1.c2_val << hand1.c2_suit << " ";
    std::cout << hand1.c3_val << hand1.c3_suit << " ";
    std::cout << hand1.c4_val << hand1.c4_suit << " ";
    std::cout << hand1.c5_val << hand1.c5_suit << " ";
    std::cout << "  <>   ";
    std::cout << hand2.c1_val << hand2.c1_suit << " ";
    std::cout << hand2.c2_val << hand2.c2_suit << " ";
    std::cout << hand2.c3_val << hand2.c3_suit << " ";
    std::cout << hand2.c4_val << hand2.c4_suit << " ";
    std::cout << hand2.c5_val << hand2.c5_suit << " ";
    std::cout << std::endl;
  }

  bool first_player_wins()
  {
    return hand1 > hand2;
  }

private:
  PokerHand hand1;
  PokerHand hand2;
};


int main()
{
  // Import the list of names
  std::vector<std::string> hand_cards;
  std::ifstream file("./p054_poker.txt");
  std::string line, word;
  std::istringstream iss;
  while (getline(file, line)) {
    iss.clear();
    iss.str(line);
    hand_cards.clear();
    while (iss >> word) {
      hand_cards.push_back(word);
    }
    Game game(hand_cards);
    game.print();
  }
  return 0;
}
