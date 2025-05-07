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

		void output();

		void game_loop();

		void flip();

		void switch_card(int action);

		void shuffle(){
			for(size_t i = deck.size() - 1; i >= 1; --i){
				size_t rand_num = rand() % i;
				swap(deck[i], deck[rand_num]);
			}
		}
};
