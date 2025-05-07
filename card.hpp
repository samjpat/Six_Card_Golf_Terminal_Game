#include <getopt.h>
#include <sys/types.h>
#include <cstdint>
#include <functional>
#include <map>
#include <string>
#include <utility>
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

enum Rank {
	ACE     = 1,
  TWO     = 2,
  THREE   = 3,
  FOUR    = 4,
  FIVE    = 5,
  SIX     = 6,
  SEVEN   = 7,
  EIGHT   = 8,
  NINE    = 9,
  TEN     = 10,
  JACK    = 11,
  QUEEN   = 12,
  KING    = 13,
  
};
  
enum Suit {
  SPADES   = 0,
  HEARTS   = 1,
  CLUBS    = 2,
  DIAMONDS = 3,
};
  
class Card{
  private:
    Rank rank;
    Suit suit;
    int points;
		string symbol;
		
  public:
    Card() : rank(TWO), suit(SPADES), points(2){}

    Card(Rank rank_in, Suit suit_in)
      : rank(rank_in), suit(suit_in){
				if(rank_in == KING){
					points = 0;
				}
				else if(rank_in == JACK || rank_in == QUEEN){
					points = 10;
				}
				else{
					points = rank_in;
				}
				switch(rank){
					case ACE:{
						symbol = 'A';
						break;
					}
					case JACK:{
						symbol = 'J';
						break;
					}
					case QUEEN:{
						symbol = 'Q';
						break;
					}
					case KING:{
						symbol = 'K';
						break;
					}
					default:{
						symbol = std::to_string(points);
					}
				}
			}

		Rank get_rank(){
			return rank;
		}
          
		Suit get_suit(){
			return suit;
		}

		int get_points(){
			return points;
		}

		string get_symbol(){
			return symbol;
		}
};
