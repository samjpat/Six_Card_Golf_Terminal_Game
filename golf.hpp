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

#include "deck.hpp"

class Golf{
	private:
		int num_holes;
		int player_1_score = 0;
		int player_2_score = 0;
		int hole = 0;

		stack<Card> discard;
		stack<Card> draw_pile;
		vector<Card> p1_cards;
		vector<Card> p2_cards;

	public:
		void get_options(int argc, char **argv);

		void setup();

		void calc_points();


};
