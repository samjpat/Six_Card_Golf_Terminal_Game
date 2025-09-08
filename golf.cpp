#include <getopt.h>
#include <bits/getopt_core.h>
#include <bits/getopt_ext.h>
#include <sys/types.h>
#include <ios>
#include <iostream>
#include <string>
#include <vector>

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

// Uses getopt_long to receive the number of holes to be played from command line
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


// Sets up deck for new hole. Shuffles and deals cards and flips starting cards for the player and computer.
void Golf::setup(){                                                            
	shuffle();	
	hole_output();
	vector<Card> cards = deck;
	p_cards.clear();
	comp_cards.clear();
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
	size_t card1 = 7;
	size_t card2 = 7;
	while(card1 == card2 || card1 > 6 || card2 > 6 || card1 == 0 || card2 == 0){
		cout << "Select 2 cards to flip (Ex: 1 4): ";
		cin >> card1;
		cin >> card2;
	}
	p_cards[card1-1].showing = true;
	p_cards[card2-1].showing = true;
	comp_cards[0].showing = true;
	comp_cards[1].showing = true;
	output();
}

// Main game loop, loops until enough holes are played as chosen by player in command line.
void Golf::game_loop(){
	// Ascii art intro graphic
	cout << "   ____   _              _____                 __       _____        __   ___\n";
	cout << "  / __/  (_) __ __      / ___/ ___ _  ____ ___/ /      / ___/ ___   / /  / _/\n";
	cout << " _\\ \\   / /  \\ \\ /     / /__  / _ `/ / __// _  /      / (_ / / _ \\ / /  / _/ \n";
	cout << "/___/  /_/  /_\\_\\      \\___/  \\_,_/ /_/   \\_,_/       \\___/  \\___//_/  /_/   \n";
	cout << "\n";


	while(hole <= num_holes){
		setup();	
		while(num_flipped <= 6){
			player_turn();
			if(output()){
				last_comp_turn();
				break;
			}
			string temp;
			cout << "Enter a 1 to end turn: ";
			cin >> temp;
			cout << endl;
			comp_turn();
			if(output()){
				player_turn();
				break;
			}
		}

		cout << "End of hole " << hole << ":\n";
		for(size_t i = 0; i < comp_cards.size(); ++i){
			cout << "[" << comp_cards[i].rank << "] ";
			if(i == 2){
				cout << "\n";
			}
		}
		cout << "\n" << "\n";
		for(size_t i = 0; i < comp_cards.size(); ++i){
			cout << "[" << p_cards[i].rank << "] ";
			if(i == 2){
				cout << "\n";
			}
		}
		cout << "\n";
		calc_points();
		hole++;
	}


	cout << "Computer: " << comp_score << "\n";
	cout << "You: " << player_score << "\n\n";
	if(player_score < comp_score){
		cout << " __  __                  _      __   _          __\n";
		cout << " \\ \\/ / ___  __ __      | | /| / /  (_)  ___   / /\n";
		cout << "  \\  / / _ \\/ // /      | |/ |/ /  / /  / _ \\ /_/ \n";
		cout << "  /_/  \\___/\\_,_/       |__/|__/  /_/  /_//_/(_)  \n";


	}
	else if(comp_score < player_score){
		cout << " __  __                   __                   __\n";
		cout << " \\ \\/ / ___  __ __       / /  ___   ___ ___   / /\n";
		cout << "  \\  / / _ \\/ // /      / /__/ _ \\ (_-</ -_) /_/ \n";
		cout << "  /_/  \\___/\\_,_/      /____/\\___//___/\\__/ (_)  \n";
	}
	else{
		cout << " __  __                 ______   _           __   __\n";
		cout << " \\ \\/ / ___  __ __     /_  __/  (_) ___  ___/ /  / /\n";
		cout << "  \\  / / _ \\/ // /      / /    / / / -_)/ _  /  /_/ \n";
		cout << "  /_/  \\___/\\_,_/      /_/    /_/  \\__/ \\_,_/  (_)  \n";

	}
}

// Function which simulates the computers turn
void Golf::comp_turn(){
	if(discard_match_check()){
		return;
	}
	int max = -1;
	size_t max_i = 0;
	for(size_t i = 0; i < 6; ++i){
		if((comp_cards[i].points > max) && !is_matched(i)){
			max = comp_cards[i].points;
			max_i = i;
		}
	}
	Card disc = discard.top();
	disc.showing = true;
	if(num_flipped == 5){
		if(score_check() + disc.points <= 12){
			for(size_t i = 0; i < 6; ++i){
				if(!comp_cards[i].showing){
					discard.pop();
					discard.push(comp_cards[i]);
					comp_cards[i] = disc;
					cout << "The computer drew a " << disc.rank << " from the discard pile and placed it in the " << i+1 << " spot\n";
					return;
				}
			}
		}
	}
	if(max != -1 && (max - disc.points) >= 4){
		discard.pop();
		discard.push(comp_cards[max_i]);
		comp_cards[max_i] = disc;

		cout << "The computer drew a " << disc.rank << " from the discard pile and placed it in the " << max_i+1 << " spot\n";

		return;
	}
	else if(num_flipped < 5){
		for(size_t i = 2; i < 6; i++){
			if(!comp_cards[i].showing){
				comp_cards[i].showing = true;

				cout << "The computer flipped the card in position " << i+1 << "\n";

				return;
			}
		}
	}
	else{
		if(drawn_match_check()){
			return;
		}
		Card drawn = draw_pile.top();
		drawn.showing = true;
		if(num_flipped == 5){
			if(score_check() + drawn.points <= 12){
				for(size_t i = 0; i < 6; ++i){
					if(!comp_cards[i].showing){
						draw_pile.pop();
						discard.push(comp_cards[i]);
						comp_cards[i] = drawn;
						cout << "The computer drew a " << drawn.rank << " from the draw pile and placed it in the " << i << " spot\n";
						return;
					}
				}
			}
		}

		if(max != -1 && drawn.points < max){
			discard.push(comp_cards[max_i]);
			comp_cards[max_i] = drawn;

			cout << "The computer drew a " << drawn.rank << " from the draw pile and placed it in the " << max_i+1 << " spot\n";

			return;
		}
		discard.push(drawn);
		cout << "The computer drew a " << drawn.rank << " from the draw pile and discarded it\n";
	
	}
}


void Golf::last_comp_turn(){
	if(discard_match_check()){
		return;
	}
	Card disc = discard.top();
	disc.showing = true;
	int max = -1;
	size_t max_i = 0;
	for(size_t i = 0; i < 6; ++i){
		if((comp_cards[i].points > max) && !is_matched(i)){
			max = comp_cards[i].points;
			max_i = i;
		}
	}

	if(disc.points <= 6 && max >= 8){
		discard.pop();
		discard.push(comp_cards[max_i]);
		comp_cards[max_i] = disc;
		cout << "The computer drew a " << disc.rank << " from the discard pile and placed it in the " << max_i+1 << " spot\n";
		return;
	}
	if(disc.points <= 6){
		for(size_t i = 0; i < 6; ++i){
			if(!comp_cards[i].showing){
				discard.push(comp_cards[i]);
				comp_cards[i] = disc;
				cout << "The computer drew a " << disc.rank << " from the discard pile and placed it in the " << i+1 << " spot\n";
			}
		}
	}
	else if(drawn_match_check()){
		return;
	}

	Card top = draw_pile.top();			
	draw_pile.pop();	

	if(top.points <= 6 && max >= 8){
		discard.push(comp_cards[max_i]);
		comp_cards[max_i] = top;
		cout << "The computer drew a " << top.rank << " from the draw pile and placed it in the " << max_i+1 << " spot\n";
	}
	else{
		for(size_t i = 0; i < 6; ++i){
			if(!comp_cards[i].showing){
				discard.push(comp_cards[i]);
				comp_cards[i] = top;
				cout << "The computer drew a " << top.rank << " from the draw pile and placed it in the " << i << " spot\n";
			}
		}
	}
}


bool Golf::discard_match_check(){
	Card disc = discard.top();
	disc.showing = true;
	for(size_t i = 0; i < 6; ++i){
		if(comp_cards[i].showing){
			if(comp_cards[i].rank == disc.rank && !is_matched(i)){
				discard.pop();
				discard.push(comp_cards[(i+3)%6]);
				comp_cards[(i+3)%6] = disc;
				
				cout << "The computer drew a " << disc.rank << " from the discard pile and placed it in the " << (i+3)%6 +1 << "spot\n";

				return true;
			}
		}
	}
	return false;
}


bool Golf::drawn_match_check(){
	Card top = draw_pile.top();						
	top.showing = true;
	for(size_t i = 0; i < 6; ++i){
		if(comp_cards[i].showing){
			if(comp_cards[i].rank == top.rank && !is_matched(i)){
				discard.push(comp_cards[(i+3)%6]);
				comp_cards[(i+3)%6] = top;
				cout << "The computer drew a " << top.rank << " from the draw pile and placed it in the " << (i+3)%6 +1 << "spot\n";
				draw_pile.pop();
				return true;
			}
			
		}
	}
	return false;
}



void Golf::player_turn(){
	size_t action = 0;
	while(action > 3 || action  == 0){
		cout << "Select action (1 to draw, 2 to draw from discard, 3 to flip card): ";
		cin >> action;
	}
	if(action == 3){
		flip();
	}
	else{
		cout << "You drew a ";
		if(action == 2){
			cout << discard.top().rank << "\n";
			size_t action = 7;
			while(action > 6) {
				cout << "Select action (0 to discard, 1-6 to place card): ";
				cin >> action;
			}
			switch_card(action, "discard");
		}
		else{
			cout << draw_pile.top().rank << "\n";
			size_t action = 7;
			while(action > 6) {
				cout << "Select action (0 to discard, 1-6 to place card): ";
				cin >> action;
			}
			switch_card(action, "draw");
		}			
	}
}


void Golf::flip(){
	size_t action = 7;
	while(action > 6){
		cout << "Select card to flip (1-6): ";
		cin >> action;
	}
	p_cards[action-1].showing = true;
}

void Golf::switch_card(size_t action, string pile){
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

int Golf::comp_showing_points(){
	int total = 0;
	for(size_t i = 0; i < 6; i++){
		Card temp = comp_cards[i];
		if(temp.showing){
			if(!is_matched(i)){
				total += temp.points;
			}
		}
	}
	return total;
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

