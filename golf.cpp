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
		golf.game_loop();
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
	hole_output();
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
	discard.push(draw_pile.top());
	draw_pile.pop();
	int card1;
	int card2;
	cout << "Select 2 cards to flip (1 4): ";
	cin >> card1;
	cin >> card2;
	p_cards[card1-1].showing = true;
	p_cards[card2-1].showing = true;
	comp_cards[0].showing = true;
	comp_cards[1].showing = true;
	output();
}


void Golf::game_loop(){
	while(hole <= num_holes){	
		setup();	
		while(num_flipped <= 6){
			player_turn();
			if(output()){
				comp_turn();
				break;
			}
			comp_turn();
			if(output()){
				player_turn();
				break;
			}
		}
		calc_points();
		hole++;
	}
}


void Golf::comp_turn(){
	Card disc = discard.top();
	disc.showing = true;
	int max = -1;
	size_t max_i = 0;
	for(size_t i = 0; i < 6; ++i){
		if(comp_cards[i].showing){
			if(comp_cards[i].rank == disc.rank){
				if(!comp_cards[(i+3)%6].showing || comp_cards[(i+3)%6].rank != comp_cards[i].rank){
					discard.pop();
					discard.push(comp_cards[(i+3)%6]);
					comp_cards[(i+3)%6] = disc;
					return;
				}
			}
			if((comp_cards[i].points > max) && (comp_cards[(i+3)%6].showing && comp_cards[(i+3)%6].rank != comp_cards[i].rank)){
				max = comp_cards[i].points;
				max_i = i;
			}
		}
	}
	if(max != -1 && (max - disc.points) >= 4){
		discard.pop();
		discard.push(comp_cards[max_i]);
		comp_cards[max_i] = disc;
		return;
	}
	else if(num_flipped < 5){
		for(size_t i = 2; i < 6; i++){
			if(!comp_cards[i].showing){
				comp_cards[i].showing = true;
				return;
			}
		}
	}
	else{
		Card top = draw_pile.top();						
		top.showing = true;
		draw_pile.pop();
		for(size_t i = 0; i < 6; ++i){
			if(comp_cards[i].showing){
				if(comp_cards[i].rank == top.rank){
					if(comp_cards[(i+3)%6].showing && comp_cards[(i+3)%6].rank != comp_cards[i].rank){
						discard.push(comp_cards[(i+3)%6]);
						comp_cards[(i+3)%6] = disc;
						return;
					}
				}
				else if(max != -1 && top.points < max){
					discard.push(comp_cards[max_i]);
					comp_cards[max_i] = top;
				}
				else{
					discard.push(top);
				}
			}
		}
	}
}

void Golf::player_turn(){
	int action = 0;
	cout << "Select action (1 to draw, 2 to draw from discard, 3 to flip card): ";
	cin >> action;
	if(action == 3){
		flip();
	}
	else{
		cout << "You drew a ";
		if(action == 2){
			cout << discard.top().rank << "\n";
			int action = 0;
			cout << "Select action (0 to discard, 1-6 to place card): ";
			cin >> action;
			switch_card(action, "discard");
		}
		else{
			cout << draw_pile.top().rank << "\n";
			int action = 0;
			cout << "Select action (0 to discard, 1-6 to place card): ";
			cin >> action;
			switch_card(action, "draw");
		}			
	}
}


void Golf::flip(){
	int action = 0;
	cout << "Select card to flip (1-6): ";
	cin >> action;
	p_cards[action-1].showing = true;
}

void Golf::switch_card(int action, string pile){
	Card drawn_card;
	if(pile == "draw"){
		drawn_card = draw_pile.top();
		draw_pile.pop();
	}
	else{
		drawn_card = discard.top();
		discard.pop();
	}
	drawn_card.showing = true;
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

void Golf::hole_output(){
	cout << "Hand: " << hole << "\n";
	cout << "Computer: " << comp_score << "\n";
	cout << "You: " << player_score << "\n";
}

bool Golf::output(){
	int player_count = 0;
	int comp_count = 0;
	cout << "_________________________\n";
	for(size_t i = 0; i < comp_cards.size(); ++i){
		cout << "[";
		if(comp_cards[i].showing){
		 	cout << comp_cards[i].rank;
			comp_count++;
		}
		else{
			cout << " ";
		}
		cout << "] ";
		if(i == 2){
			cout << "\n";
		}
	}
	num_flipped = comp_count;
	cout << "\n";
	cout << "Discard: " << discard.top().rank << "\n";
	for(size_t i = 0; i < p_cards.size(); ++i){
		cout << "[";
		if(p_cards[i].showing){
		 	cout << p_cards[i].rank;
			player_count++;
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
	return comp_count == 6 || player_count == 6;
}

