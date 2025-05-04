#include <getopt.h>
#include <sys/types.h>
#include <array>
#include <cstdint>
#include <functional>
#include <map>
#include <string>
#include <utility>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <cstdlib>

using namespace std;
#include "card.hpp"


class Deck{
	private:
		static const int pack_size = 52;
		vector<Card> cards;
		int next;

	public:
		Deck():cards({Card(ACE, SPADES), Card(TWO, SPADES),
									Card(THREE, SPADES), Card(FOUR, SPADES),
									Card(FIVE, SPADES), Card(SIX, SPADES),
									Card(SEVEN, SPADES), Card(EIGHT, SPADES),
									Card(NINE, SPADES), Card(TEN, SPADES),
									Card(JACK, SPADES), Card(QUEEN, SPADES),
									Card(KING, SPADES),
									Card(ACE, DIAMONDS), Card(TWO, DIAMONDS),
									Card(THREE, DIAMONDS), Card(FOUR, DIAMONDS),
									Card(FIVE, DIAMONDS), Card(SIX, DIAMONDS),
									Card(SEVEN, DIAMONDS), Card(EIGHT, DIAMONDS),
									Card(NINE, DIAMONDS), Card(TEN, DIAMONDS),
									Card(JACK, DIAMONDS), Card(QUEEN, DIAMONDS),
									Card(KING, DIAMONDS),
									Card(ACE, CLUBS), Card(TWO, CLUBS),
									Card(THREE, CLUBS), Card(FOUR, CLUBS),
									Card(FIVE, CLUBS), Card(SIX, CLUBS),
									Card(SEVEN, CLUBS), Card(EIGHT, CLUBS),
									Card(NINE, CLUBS), Card(TEN, CLUBS),
									Card(JACK, CLUBS), Card(QUEEN, CLUBS),
									Card(KING, CLUBS),
									Card(ACE, HEARTS), Card(TWO, HEARTS),
									Card(THREE, HEARTS), Card(FOUR, HEARTS),
									Card(FIVE, HEARTS), Card(SIX, HEARTS),
									Card(SEVEN, HEARTS), Card(EIGHT, HEARTS),
									Card(NINE, HEARTS), Card(TEN, HEARTS),
									Card(JACK, HEARTS), Card(QUEEN, HEARTS),
									Card(KING, HEARTS)}), next(0){
		}

		void shuffle(){
			for(size_t i = pack_size - 1; i >= 1; --i){
				size_t rand_num = rand() % i;
				swap(cards[i], cards[rand_num]);
			}
		}

		vector<Card> get_deck(){
			return cards;
		}

};
