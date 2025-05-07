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
		golf.output();
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
  struct option longOpts[] = {{"holes", required_argument, nullptr, 'h'}};
  
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
	shuffle();
	vector<Card> cards = deck;
	for(auto card : cards){
		draw_pile.push(card);
	}
	for(size_t i = 0; i < 12; ++i){
		Card top = draw_pile.top();
		draw_pile.pop();
		if(i % 2 == 0){
			p_cards.push_back(top);
		}
		else{
			comp_cards.push_back(top);
		}
	}
	int card1;
	int card2;
	cout << "Select 2 cards to flip (1 4): ";
	cin >> card1;
	cin >> card2;
	p_cards[card1-1].showing = true;
	p_cards[card2-1].showing = true;
}


void Golf::game_loop(){
	int action = 0;
	cout << "Select action (1 to draw, 2 to draw from discard, 3 to flip card):";
	cin >> action;
	if(action == 3){
		flip();
	}
	else{
		int action = 0;
		cout << "Select action (0 to discard, 1-6 to place card)";
		cin >> action;
		switch_card(action);
	}
}

void Golf::flip(){
	int action = 0;
	cout << "Select card to flip (1-6)";
	cin >> action;
	p_cards[action-1].showing = true;
}

void Golf::switch_card(int action){
	Card drawn_card = draw_pile.top();
	drawn_card.showing = true;
	draw_pile.pop();
	if(action == 0){
		discard.push(drawn_card);
	}
	else{
		Card temp = p_cards[action-1];
		discard.push(temp);
		p_cards[action-1] = drawn_card;
	}
}



void Golf::calc_points(){
	for(size_t i = 0; i < 3; i++){
		Card temp1 = p_cards[i];
		Card temp2 = p_cards[i+3];
		if(temp1.rank != temp2.rank){
			player_score += temp1.points;
			player_score += temp2.points;
		}
	}
	for(size_t i = 0; i < 3; i++){
		Card temp1 = comp_cards[i];
		Card temp2 = comp_cards[i+3];
		if(temp1.rank != temp2.rank){
			comp_score += temp1.points;
			comp_score += temp2.points;
		}
	}
}


void Golf::output(){
	cout << "Hand: " << hole << "\n";
	cout << "Computer: " << comp_score << "\n";
	cout << "You: " << player_score << "\n";
	cout << "_________________________\n";
	for(size_t i = 0; i < comp_cards.size(); ++i){
		cout << "[";
		if(comp_cards[i].showing){
		 	cout << comp_cards[i].rank;
		}
		else{
			cout << " ";
		}
		cout << "] ";
		if(i == 2){
			cout << "\n";
		}
	}
	cout << "\n";
	cout << "Discard: " << "\n";
	for(size_t i = 0; i < p_cards.size(); ++i){
		cout << "[";
		if(p_cards[i].showing){
		 	cout << p_cards[i].rank;
		}
		else{
			cout << " ";
		}
		cout << "] ";
		if(i == 2){
			cout << "\n";
		}
	}
	cout << "\n";
	cout << "_________________________\n";
}

