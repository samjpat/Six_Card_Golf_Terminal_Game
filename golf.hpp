#include <getopt.h>
#include <sys/types.h>
#include <cstdint>
#include <functional>
#include <map>
#include <stack>
#include <string>
#include <utility>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <algorithm>
#include <random>

using namespace std;

struct Card{
	string rank;
	int points;
	bool showing;
};

class Golf{
	private:
		int num_holes = 0;
		int player_score = 0;
		int comp_score = 0;
		int hole = 1;
		vector<Card> deck;
		stack<Card> discard;
		stack<Card> draw_pile;
		vector<Card> p_cards;
		vector<Card> comp_cards;
		int comp_show = 2;
		int player_show = 2;
		int num_flipped = 2;
		//multimap<string, size_t> comp_map;


	public:
		Golf():deck({Card{"A", 1, false}, Card{"A", 1, false}, Card{"A", 1, false}, Card{"A", 1, false}, 
								 Card{"2", 2, false}, Card{"2", 2, false}, Card{"2", 2, false}, Card{"2", 2, false},
								 Card{"3", 3, false}, Card{"3", 3, false}, Card{"3", 3, false}, Card{"3", 3, false}, 
								 Card{"4", 4, false}, Card{"4", 4, false}, Card{"4", 4, false}, Card{"4", 4, false},
								 Card{"5", 5, false}, Card{"5", 5, false}, Card{"5", 5, false}, Card{"5", 5, false}, 
								 Card{"6", 6, false}, Card{"6", 6, false}, Card{"6", 6, false}, Card{"6", 6, false},
								 Card{"7", 7, false}, Card{"7", 7, false}, Card{"7", 7, false}, Card{"7", 7, false}, 
								 Card{"8", 8, false}, Card{"8", 8, false}, Card{"8", 8, false}, Card{"8", 8, false},
								 Card{"9", 9, false}, Card{"9", 9, false}, Card{"9", 9, false}, Card{"9", 9, false},
								 Card{"10", 10, false}, Card{"10", 10, false}, Card{"10", 10, false}, Card{"10", 10, false}, 
								 Card{"J", 10, false}, Card{"J", 10, false}, Card{"J", 10, false}, Card{"J", 10, false},
								 Card{"Q", 10, false}, Card{"Q", 10, false}, Card{"Q", 10, false}, Card{"Q", 10, false}, 
								 Card{"K", 0, false}, Card{"K", 0, false}, Card{"K", 0, false}, Card{"K", 0, false}}){}

		void get_options(int argc, char **argv);

		void setup();

		void calc_points();

		int comp_showing_points();

		bool output();

		void game_loop();

		void flip();

		void switch_card(int action, string pile);

		void comp_turn();

		void player_turn();

		void hole_output();

		void shuffle(){
			random_device rd;
			mt19937 gen(rd());
			std::shuffle(deck.begin(), deck.end(), gen);
		}

		bool is_matched(size_t i){
			return comp_cards[(i+3)%6].showing && comp_cards[(i+3)%6].rank == comp_cards[i].rank;
		}
};
