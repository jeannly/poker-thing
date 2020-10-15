#include "gamesystem.h"

#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <vector>

namespace game_system {
const char* kCardNamesDefault[52] = {
	"2d","2h","2s","2c","3d","3h","3s","3c","4d","4h","4s","4c",
	"5d","5h","5s","5c","6d","6h","6s","6c","7d","7h","7s","7c",
	"8d","8h","8s","8c","9d","9h","9s","9c","Td","Th","Ts","Tc",
	"Jd","Jh","Js","Jc","Qd","Qh","Qs","Qc","Kd","Kh","Ks","Kc",
	"Ad","Ah","As","Ac"
};

void Game::set_game(int playercount) {

	if (playercount > globals::kMaxPlayers) {
		std::cout << "The maximum number of players is " << globals::kMaxPlayers
		<< ", only " << globals::kMaxPlayers << " hands will be dealt" << std::endl;

		this->number_of_players = globals::kMaxPlayers;
		return;
	}
	if (playercount < 2) {
		std::cout << "The minimum number of players is 2, 2 hands will be dealt" << std::endl;
		this->number_of_players = 2;
		return;
	}
	this->number_of_players = playercount;


}

void Game::NewGame() {
	std::cout << "New game loading..." << std::endl;
	std::cout << "Players: " << this->number_of_players << std::endl;
	//std::cout << ". Blinds: " << std::endl; //TODO: display blinds amount WHEN: adding betting modules

	this->game_deck.Shuffle();

	if (!(this->players.empty())) {
		for (size_t i = 0; i < this->players.size(); i++) {
			if (this->players[i] != nullptr) {
				delete this->players[i];
			}
		}
	}
	this->players.resize(this->number_of_players, nullptr);
	for (int i = 0; i < this->number_of_players; i++) {
		this->players[i] = new PlayerObject;
	}

	this->current_round = kDealing;
	//TODO: reset chip amounts
	this->Round();
}

void Game::Round() {
	//No showdown
	if (this->round_end || this->override) {
		//Normal showdown
		if (!(this->override)) {

			return;
			//Round();
		}
		//Exit game
		if (!(this->round_end)) {
			return;
		}
	//TODO
	//1. Call from chipsystem round_end function. 
	//2. Clear player hands
	//3. Shuffle deck
	//4. Current round = kDealing
	}

	int num_playercards = this->number_of_players * 2;
	switch (this->current_round) {
	
	case kDealing:
	//Shuffle. Assign player cards. Assign community cards. Nothing to be called from chipsystem
		this->game_deck.Shuffle();
		for (int i = 0; i < this->number_of_players; i++) {
			this->players[i]->hand[0] = this->game_deck.cards[2 * i];
			this->players[i]->hand[1] = this->game_deck.cards[2 * i + 1];
		}
		for (int i = 0; i < 5; i++) {
			this->community_cards[i] = this->game_deck.cards[num_playercards + i];
		}
		this->current_round = kPreflop;
		break;

	case kPreflop:
	//TODO: Call from chipsystem
		std::cout << "PREFLOP: " << std::endl;

		this->current_round = kFlop;
		break;
	
	case kFlop:
	//Display first 3 community cards. TODO: Call from chipsystem

		std::cout << "FLOP: " << std::endl;
		for (int i = 0; i < 3; i++) {
			std::cout << kCardNamesDefault[community_cards[i]] << " ";
		}
		std::cout << std::endl;

		this->current_round = kTurn;
		break;

	case kTurn:
	//Display turn card TODO: Call from chipsystem
		std::cout << "TURN: " << std::endl;
		std::cout << kCardNamesDefault[community_cards[3]] << " ";
		std::cout << std::endl;

		this->current_round = kRiver;
		break;

	case kRiver:
	//Display river card TODO: Call from chipsystem
		std::cout << "RIVER: " << std::endl;
		std::cout << kCardNamesDefault[community_cards[4]] << " ";
		std::cout << std::endl;

		this->current_round = kShowdown;
		break;

	case kShowdown:
	//TODO: Call showdown from chipsystem	
		this->round_end = true;
		break;
	}

	//TODO: Recursive once exit flags are made (i.e. betting)
	Round();
}

} //namespace game_system