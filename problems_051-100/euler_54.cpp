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

  ANSWER: 376
**/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <iterator>
#include <assert.h>


struct Card {
  char symb_val;
  char val;
  char suit;
};

std::ostream& operator << (std::ostream &o, const Card &card)
{
  return (o << card.symb_val << card.suit);
}


class PokerHand{
public:
  PokerHand() {}

  PokerHand(
    std::string cs1, 
    std::string cs2, 
    std::string cs3, 
    std::string cs4, 
    std::string cs5)
  {
    // Sort by card value:
    c[0].symb_val = cs1[0];
    c[0].suit = cs1[1];
    c[0].val = convert_char_val(cs1[0]);
    //
    c[1].symb_val = cs2[0];
    c[1].suit = cs2[1];
    c[1].val = convert_char_val(cs2[0]);
    //
    c[2].symb_val = cs3[0];
    c[2].suit = cs3[1];
    c[2].val = convert_char_val(cs3[0]);
    //
    c[3].symb_val = cs4[0];
    c[3].suit = cs4[1];
    c[3].val = convert_char_val(cs4[0]);
    //
    c[4].symb_val = cs5[0];
    c[4].suit = cs5[1];
    c[4].val = convert_char_val(cs5[0]);

    // Bubble sort the cards:
    bool no_swaps = true;
    Card temp;
    while (no_swaps) {
      no_swaps = false;
      for (int idx = 0; idx < 4; idx++) {
        if (c[idx].val > c[idx + 1].val) {
          temp = c[idx + 1];
          c[idx + 1] = c[idx];
          c[idx] = temp;
          no_swaps = true;
        }
      }
    }
    
    // Determine hand rank:
    determine_hand_rank();
  }

  char convert_char_val(char symb_val)
  {
    if (symb_val >= '2' && symb_val <= '9') {
      return symb_val;
    }
    else if (symb_val == 'T') {
      symb_val = '9';
      symb_val += 1;
    }
    else if (symb_val == 'J') {
      symb_val = '9';
      symb_val += 2;
    }
    else if (symb_val == 'Q') {
      symb_val = '9';
      symb_val += 3;
    }
    else if (symb_val == 'K') {
      symb_val = '9';
      symb_val += 4;
    }
    else if (symb_val == 'A') {
      symb_val = '9';
      symb_val += 5;
    }
    else {
      std::cerr << "ERROR: " << symb_val << " is not valid!" << std::endl;
    }
    return symb_val;
  }

  void determine_hand_rank()
  /* Hand Ranking:
   *      1  <-->  High Card
   *      2  <-->  One Pair
   *      3  <-->  Two Pairs
   *      4  <-->  Three of a Kind
   *      5  <-->  Straight
   *      6  <-->  Flush
   *      7  <-->  Full House
   *      8  <-->  Four of a Kind
   *      9  <-->  Straight Flush
   *     10  <-->  Royal Flush 
   **/
  {
    std::map<char, int>::iterator it;
    std::map<char, int> vals;
    for (int idx = 0; idx < 5; idx++) {
      if (vals.find(c[idx].val) == vals.end()) vals[c[idx].val] = 1;
      else vals[c[idx].val] += 1;
    }

    // Royal Flush, Straight Flush and Flush
    if (c[0].suit == c[1].suit && 
        c[1].suit == c[2].suit && 
        c[2].suit == c[3].suit && 
        c[3].suit == c[4].suit) {
      if (c[1].val == c[0].val + 1 &&
          c[2].val == c[0].val + 2 &&
          c[3].val == c[0].val + 3 &&
          c[4].val == c[0].val + 4) {
        hand_rank_card = c[4].val;
        if (c[0].symb_val == 'T') hand_rank = 10;
        else hand_rank = 9;
      }
      else {
        hand_rank_card = c[4].val;
        hand_rank = 6;
      }
    }
    // Four of a kind
    else if (vals.size() == 2 && (vals[c[0].val] == 4 || vals[c[0].val] == 1)) {
      if (vals.begin()->second == 4) hand_rank_card = vals.begin()->first;
      else hand_rank_card = vals.rbegin()->first;
      hand_rank = 8;
    } 
    // Full house
    else if (vals.size() == 2) {
      for (it = vals.begin(); it != vals.end(); it++) {
        if (it->second == 3) {
          hand_rank_card = it->first;
          break;
        }
      }
      hand_rank = 7;
    }
    // Straight 
    else if (c[1].val == c[0].val + 1 &&
             c[2].val == c[0].val + 2 &&
             c[3].val == c[0].val + 3 &&
             c[4].val == c[0].val + 4) {
      hand_rank_card = c[4].val;
      hand_rank = 5;
    }
    // Three of a kind
    else if (vals[c[0].val] == 3) {
      hand_rank_card = c[0].val;
      hand_rank = 4;
    }  
    else if (vals[c[1].val] == 3) {
      hand_rank_card = c[1].val;
      hand_rank = 4;
    }  
    else if (vals[c[2].val] == 3) {
      hand_rank_card = c[2].val;
      hand_rank = 4;
    }  
    // Two Pair
    else if (vals.size() == 3) {
      if (vals[c[4].val] == 2) hand_rank_card = c[4].val;
      else hand_rank_card = c[3].val;
      hand_rank = 3;
    }
    // One Pair
    else if (vals.size() == 4) {
      for (it = vals.begin(); it != vals.end(); it++) {
        if (it->second == 2) {
          hand_rank_card = it->first;
          break;
        }
      }
      hand_rank = 2;
    }
    // High card
    else {
      hand_rank_card = c[4].val;
      hand_rank = 1;
    }
  }

  friend class Game;
  friend bool operator> (const PokerHand &h1, const PokerHand &h2);
  friend bool operator< (const PokerHand &h1, const PokerHand &h2); 

private:
  Card c[5];
  // 
  unsigned int hand_rank;
  char hand_rank_card;
};


bool operator> (const PokerHand &h1, const PokerHand &h2)
{
  if (h1.hand_rank > h2.hand_rank) return true;
  else if(h1.hand_rank < h2.hand_rank) return false;
  else {
    if(h1.hand_rank_card > h2.hand_rank_card) return true;
    else if (h1.hand_rank_card < h2.hand_rank_card) return false;
    else {
      unsigned int idx = 4;
      while (h1.c[idx].val == h2.c[idx].val && idx != 0) idx -= 1;
      return h1.c[idx].val >= h2.c[idx].val;
    }
  }
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

  void print(bool winner=true, bool hand_type=true)
  {
    std::cout << "\t";
    std::cout << hand1.c[0] << " ";
    std::cout << hand1.c[1] << " ";
    std::cout << hand1.c[2] << " ";
    std::cout << hand1.c[3] << " ";
    std::cout << hand1.c[4] << " ";
    if (hand_type) {
      std::cout << "[" << hand1.hand_rank << ", " 
                << (int)(hand1.hand_rank_card - '0') << "] ";
    }
    std::cout << "  <>   ";
    std::cout << hand2.c[0] << " ";
    std::cout << hand2.c[1] << " ";
    std::cout << hand2.c[2] << " ";
    std::cout << hand2.c[3] << " ";
    std::cout << hand2.c[4] << " ";
    if (hand_type) {
      std::cout << "[" << hand2.hand_rank << ", " 
                << (int)(hand2.hand_rank_card - '0') << "] ";
    }
    if (winner) {
        if (first_player_wins()) std::cout << "\t1";
        else std::cout << "\t2";
    }   
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
  unsigned int player1_win_count = 0;
  while (getline(file, line)) {
    iss.clear();
    iss.str(line);
    hand_cards.clear();
    // std::cout << std::endl;
    while (iss >> word) {
      hand_cards.push_back(word);
      // std::cout << word << " ";
    }
    // std::cout << std::endl;
    Game game(hand_cards);
    game.print();
    if (game.first_player_wins()) player1_win_count += 1;
  }
  std::cout << "Player 1 wines " << player1_win_count << " times!" << std::endl;
  return 0;
}
