#include <getopt.h>
#include <bits/getopt_core.h>
#include <bits/getopt_ext.h>
#include <sys/types.h>
#include <cstdint>
#include <functional>
#include <ios>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>
#include <unordered_map>

#include "golf.hpp"

using namespace std;

int main(int argc, char *argv[]){
  ios_base::sync_with_stdio(false);

  try{
		Golf golf;
		golf.get_options(argc, argv);
		golf.setup();
  }
  catch(runtime_error& err){
    cerr << err.what() << "\n";
    return 1;
  }
  return 0;
}


void Golf::get_options(int argc, char **argv){
  int option_i = 0;
  int option = 0;
  opterr = 0;
  struct option longOpts[] = {{"help", required_argument, nullptr, 'h'}};
  
  while((option = getopt_long(argc, argv, "h:",  longOpts, &option_i)) != -1){
    switch(option){
      case 'h': {
        string arg {optarg};
				char temp = arg[0];
				num_holes = temp - '0';
				break;
      }
      default:
        cerr << "Unknown option" << endl;
        exit(1);
    }
  }
}

void Golf::setup(){
	Deck deck;
	deck.shuffle();
	vector<Card> cards = deck.get_deck();
	for(auto card : cards){
		draw_pile.push(card);
	}
	for(size_t i = 0; i < 12; ++i){
		Card top = draw_pile.top();
		draw_pile.pop();
		if(i % 2 == 0){
			p1_cards.push_back(top);
		}
		else{
			p2_cards.push_back(top);
		}
	}
}

void Golf::calc_points(){
	for(size_t i = 0; i < 3; i++){
		Card temp1 = p1_cards[i];
		Card temp2 = p1_cards[i+3];
		if(temp1.get_rank() != temp2.get_rank()){
			player_1_score += temp1.get_points();
			player_1_score += temp2.get_points();
		}
	}
	for(size_t i = 0; i < 3; i++){
		Card temp1 = p2_cards[i];
		Card temp2 = p2_cards[i+3];
		if(temp1.get_rank() != temp2.get_rank()){
			player_2_score += temp1.get_points();
			player_2_score += temp2.get_points();
		}
	}
}



